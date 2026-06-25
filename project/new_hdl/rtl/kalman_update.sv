// kalman_update.sv — Kalman filter update kernel, Option B
// H = [1, 0, 0] (scalar measurement), R = 5.0 (F64)
// FSM: IDLE → INNOV → S_COMP → NR0 → NR1 → NR2 → K_COMP → X_CORR → P_UPD → WAIT_P → DONE
// Internally instantiates gemm_systolic for the IKH*P covariance update.

module kalman_update (
    input  logic        clk,
    input  logic        rst_n,
    input  logic        start,
    input  logic [63:0] z,              // scalar measurement
    input  logic [63:0] x_in  [0:2],   // prior state 3×1
    input  logic [63:0] P_in  [0:8],   // prior covariance 3×3
    output logic [63:0] x_out [0:2],   // corrected state
    output logic [63:0] P_out [0:8],   // corrected covariance
    output logic        done,
    output logic        busy
);

    // R constant = 5.0 in IEEE-754 F64
    localparam logic [63:0] R_CONST = 64'h4014_0000_0000_0000;
    // 2.0 in F64
    localparam logic [63:0] F64_TWO = 64'h4000_0000_0000_0000;
    // 1.0 in F64
    localparam logic [63:0] F64_ONE = 64'h3FF0_0000_0000_0000;

    // FSM states
    typedef enum logic [3:0] {
        IDLE   = 4'd0,
        INNOV  = 4'd1,   // y_tilde = z - x_in[0]; S_pre = P_in[0] + R
        S_COMP = 4'd2,   // S = S_pre (latch)
        NR0    = 4'd3,   // Newton-Raphson iteration 0: x = x0*(2 - S*x0)
        NR1    = 4'd4,   // NR iteration 1
        NR2    = 4'd5,   // NR iteration 2
        K_COMP = 4'd6,   // K[i] = P_in[i*3] * S_inv
        X_CORR = 4'd7,   // x_out[i] = x_in[i] + K[i]*y_tilde
        P_UPD  = 4'd8,   // Build IKH, fire gemm_systolic(IKH, P_in)
        WAIT_P = 4'd9,   // Wait for gemm_systolic to finish
        DONE_S = 4'd10
    } state_t;

    state_t state, state_nxt;

    // Registered intermediate values
    logic [63:0] z_reg, y_tilde, S_reg, S_inv;
    logic [63:0] x_reg  [0:2];
    logic [63:0] P_reg  [0:8];
    logic [63:0] K_reg  [0:2];
    logic [63:0] IKH    [0:8];  // (I - K*H) matrix, 3×3

    // NR intermediate
    logic [63:0] nr_x;   // current reciprocal estimate

    // gemm_systolic signals
    logic        gs_start, gs_done, gs_busy;
    logic [63:0] gs_A [0:8], gs_B [0:8], gs_C [0:8];

    gemm_systolic u_gemm (
        .clk   (clk),
        .rst_n (rst_n),
        .start (gs_start),
        .A     (gs_A),
        .B     (gs_B),
        .C     (gs_C),
        .done  (gs_done),
        .busy  (gs_busy)
    );

    // Combinational helpers for Newton-Raphson
    // x_new = x * (2.0 - S * x)
    logic [63:0] sx, two_minus_sx, nr_x_new;
    f64_mul u_nr_mul1 (.a(S_reg), .b(nr_x),        .result(sx));
    f64_add u_nr_sub  (.a(F64_TWO), .b({~sx[63], sx[62:0]}), .result(two_minus_sx));  // 2.0 + (-sx)
    f64_mul u_nr_mul2 (.a(nr_x), .b(two_minus_sx), .result(nr_x_new));

    // K[i] = P_reg[i*3] * S_inv  (3 parallel muls)
    logic [63:0] k_comb [0:2];
    f64_mul u_k0 (.a(P_reg[0]), .b(S_inv), .result(k_comb[0]));
    f64_mul u_k1 (.a(P_reg[3]), .b(S_inv), .result(k_comb[1]));
    f64_mul u_k2 (.a(P_reg[6]), .b(S_inv), .result(k_comb[2]));

    // x_out[i] = x_reg[i] + K[i]*y_tilde  (3 parallel)
    logic [63:0] ky0, ky1, ky2;
    logic [63:0] xout0, xout1, xout2;
    f64_mul u_ky0 (.a(K_reg[0]), .b(y_tilde), .result(ky0));
    f64_mul u_ky1 (.a(K_reg[1]), .b(y_tilde), .result(ky1));
    f64_mul u_ky2 (.a(K_reg[2]), .b(y_tilde), .result(ky2));
    f64_add u_xo0 (.a(x_reg[0]), .b(ky0), .result(xout0));
    f64_add u_xo1 (.a(x_reg[1]), .b(ky1), .result(xout1));
    f64_add u_xo2 (.a(x_reg[2]), .b(ky2), .result(xout2));

    // IKH[0,0] = 1 - K[0]: compute combinationally from K_reg[0]
    logic [63:0] one_minus_k0;
    f64_add u_1mk0 (.a(F64_ONE), .b(f64_neg(K_reg[0])), .result(one_minus_k0));

    // FSM next-state
    always_comb begin
        state_nxt = state;
        case (state)
            IDLE:   if (start)    state_nxt = INNOV;
            INNOV:                state_nxt = S_COMP;
            S_COMP:               state_nxt = NR0;
            NR0:                  state_nxt = NR1;
            NR1:                  state_nxt = NR2;
            NR2:                  state_nxt = K_COMP;
            K_COMP:               state_nxt = X_CORR;
            X_CORR:               state_nxt = P_UPD;
            P_UPD:                state_nxt = WAIT_P;
            WAIT_P: if (gs_done)  state_nxt = DONE_S;
            DONE_S:               state_nxt = IDLE;
            default:              state_nxt = IDLE;
        endcase
    end

    // Negate helper: flip sign bit
    function automatic logic [63:0] f64_neg (input logic [63:0] x);
        f64_neg = {~x[63], x[62:0]};
    endfunction

    // Newton-Raphson seed: bit-trick approximation of 1/S
    // seed = 0x7FDE600000000000 - S_bits (integer subtraction on bit pattern)
    function automatic logic [63:0] nr_seed (input logic [63:0] s);
        nr_seed = 64'h7FDE_6000_0000_0000 - s;
    endfunction

    // FSM datapath
    integer ii;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            state   <= IDLE;
            gs_start <= 1'b0;
            for (ii = 0; ii < 9; ii++) begin
                gs_A[ii] <= 64'h0;
                gs_B[ii] <= 64'h0;
                IKH[ii]  <= 64'h0;
                P_reg[ii] <= 64'h0;
            end
            for (ii = 0; ii < 3; ii++) begin
                x_reg[ii]  <= 64'h0;
                K_reg[ii]  <= 64'h0;
                x_out[ii]  <= 64'h0;
            end
            for (ii = 0; ii < 9; ii++) P_out[ii] <= 64'h0;
            z_reg   <= 64'h0;
            S_inv   <= 64'h0;
            nr_x    <= 64'h0;
        end else begin
            state    <= state_nxt;
            gs_start <= 1'b0;

            case (state)
                INNOV: begin
                    z_reg    <= z;
                    for (ii = 0; ii < 3; ii++) x_reg[ii] <= x_in[ii];
                    for (ii = 0; ii < 9; ii++) P_reg[ii] <= P_in[ii];
                    // y_tilde = z - x_in[0]  (combinational on next cycle)
                    // S_pre = P_in[0] + R     (similarly)
                    // We compute them in S_COMP using registered values
                end

                S_COMP: begin
                    // y_tilde = z_reg - x_reg[0]  = z_reg + (-x_reg[0])
                    // Use f64_add with negated x_reg[0]
                    // (Inline the computation to avoid extra always_comb blocks)
                    // We'll drive these through dedicated instances below
                    nr_x <= nr_seed(P_reg[0]);  // seed for S = P_in[0]+R; use P_reg[0] as proxy
                    // y_tilde and S_reg set via comb below
                end

                NR0: begin
                    nr_x <= nr_x_new;
                    S_inv <= nr_x_new;
                end

                NR1: begin
                    nr_x <= nr_x_new;
                    S_inv <= nr_x_new;
                end

                NR2: begin
                    S_inv <= nr_x_new;
                end

                K_COMP: begin
                    K_reg[0] <= k_comb[0];
                    K_reg[1] <= k_comb[1];
                    K_reg[2] <= k_comb[2];
                end

                X_CORR: begin
                    x_out[0] <= xout0;
                    x_out[1] <= xout1;
                    x_out[2] <= xout2;
                    // Build complete IKH = I - K*H; H=[1,0,0]
                    // Row 0: [1-K[0],  0,       0      ]
                    // Row 1: [-K[1],   1,       0      ]
                    // Row 2: [-K[2],   0,       1      ]
                    IKH[0] <= one_minus_k0;      // 1 - K[0]
                    IKH[1] <= 64'h0;
                    IKH[2] <= 64'h0;
                    IKH[3] <= f64_neg(K_reg[1]); // -K[1]
                    IKH[4] <= F64_ONE;
                    IKH[5] <= 64'h0;
                    IKH[6] <= f64_neg(K_reg[2]); // -K[2]
                    IKH[7] <= 64'h0;
                    IKH[8] <= F64_ONE;
                end

                P_UPD: begin
                    // Load IKH (built in X_CORR) and P into gemm_systolic; fire start
                    for (ii = 0; ii < 9; ii++) begin
                        gs_A[ii] <= IKH[ii];
                        gs_B[ii] <= P_reg[ii];
                    end
                    gs_start <= 1'b1;
                end

                WAIT_P: begin
                    gs_start <= 1'b0;
                    // gs_done fires while gemm is in FINISH; gs_C holds old C until
                    // the next cycle (NBA update). Latch P_out in DONE_S instead.
                end

                DONE_S: begin
                    // One cycle after FINISH: gs_C now holds the updated gemm result
                    for (ii = 0; ii < 9; ii++) P_out[ii] <= gs_C[ii];
                end

                default: ;
            endcase
        end
    end

    // Combinational y_tilde and S_reg (registered on S_COMP exit)
    // These use dedicated module instances driven from registered values
    logic [63:0] y_tilde_comb, S_comb;
    f64_add u_ytilde (.a(z_reg),   .b(f64_neg(x_reg[0])), .result(y_tilde_comb));
    f64_add u_scomb  (.a(P_reg[0]),.b(R_CONST),            .result(S_comb));

    // Latch y_tilde and S_reg in S_COMP (one cycle after INNOV so that z_reg,
    // x_reg, and P_reg have settled from their NBA updates in INNOV).
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            y_tilde <= 64'h0;
            S_reg   <= 64'h0;
        end else if (state == S_COMP) begin
            y_tilde <= y_tilde_comb;
            S_reg   <= S_comb;
        end
    end

    // Outputs
    assign done = (state == DONE_S);
    assign busy = (state != IDLE) && (state != DONE_S);

endmodule
