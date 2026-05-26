`timescale 1ns/1ps
// =============================================================================
// top.sv — M3 integrated top module: Option B Kalman Update Accelerator
// All synthesisable RTL combined into a single file.
// Module hierarchy (dependency order):
//   f64_mul       — Combinational IEEE-754 F64 multiplier
//   f64_add       — Combinational IEEE-754 F64 adder
//   gemm_systolic — 3×3 weight-stationary systolic GEMM (used by kalman_update)
//   kalman_update — Kalman filter update kernel (instantiates gemm_systolic)
//   axilite_slave — AXI4-Lite slave register file
//   top           — Integration top (axilite_slave + kalman_update)
// =============================================================================

// -----------------------------------------------------------------------------
// f64_mul — Combinational IEEE-754 double-precision multiplier
// Pure always_comb; no clock. Vivado infers DSP48E1 chains for the 53×53 product.
// Special cases: NaN propagation, Inf×0=NaN, zero handling, overflow→Inf.
// -----------------------------------------------------------------------------
module f64_mul (
    input  logic [63:0] a,
    input  logic [63:0] b,
    output logic [63:0] result
);

    // Field extraction
    logic        a_sign, b_sign, r_sign;
    logic [10:0] a_exp,  b_exp;
    logic [52:0] a_man,  b_man;   // includes implicit leading 1 (or 0 for denorm)

    assign a_sign = a[63];
    assign b_sign = b[63];
    assign a_exp  = a[62:52];
    assign b_exp  = b[62:52];
    assign a_man  = (a_exp == 11'h0) ? {1'b0, a[51:0]} : {1'b1, a[51:0]};
    assign b_man  = (b_exp == 11'h0) ? {1'b0, b[51:0]} : {1'b1, b[51:0]};

    // Special-case detection
    logic a_nan, b_nan, a_inf, b_inf, a_zero, b_zero;
    assign a_nan  = (a_exp == 11'h7FF) && (a[51:0] != 52'h0);
    assign b_nan  = (b_exp == 11'h7FF) && (b[51:0] != 52'h0);
    assign a_inf  = (a_exp == 11'h7FF) && (a[51:0] == 52'h0);
    assign b_inf  = (b_exp == 11'h7FF) && (b[51:0] == 52'h0);
    assign a_zero = (a_exp == 11'h0)   && (a[51:0] == 52'h0);
    assign b_zero = (b_exp == 11'h0)   && (b[51:0] == 52'h0);

    // 106-bit product (53×53 unsigned)
    logic [105:0] product;
    assign product = {53'b0, a_man} * {53'b0, b_man};

    // Exponent sum (unbiased: ea + eb - 1023)
    // Use 13-bit signed to detect underflow/overflow
    logic signed [12:0] exp_sum;
    assign exp_sum = $signed({2'b00, a_exp}) + $signed({2'b00, b_exp})
                     - $signed(13'd1023);

    // Normalise: if product[105]=1, shift right 1 and inc exp
    logic [51:0] norm_man;
    logic [12:0] norm_exp;
    always_comb begin
        if (product[105]) begin
            norm_man = product[104:53];
            norm_exp = exp_sum + 13'd1;
        end else begin
            norm_man = product[103:52];
            norm_exp = exp_sum;
        end
    end

    // Result sign
    assign r_sign = a_sign ^ b_sign;

    // Final mux — special cases first
    always_comb begin
        if (a_nan || b_nan) begin
            // Propagate NaN (quiet NaN)
            result = 64'h7FF8_0000_0000_0000;
        end else if ((a_inf && b_zero) || (b_inf && a_zero)) begin
            // Inf × 0 = NaN (IEEE 754)
            result = 64'h7FF8_0000_0000_0000;
        end else if (a_inf || b_inf) begin
            // Inf × finite = ±Inf
            result = {r_sign, 11'h7FF, 52'h0};
        end else if (a_zero || b_zero) begin
            // Zero result
            result = {r_sign, 63'b0};
        end else if (norm_exp >= $signed(13'd2047)) begin
            // Overflow → ±Inf
            result = {r_sign, 11'h7FF, 52'h0};
        end else if (norm_exp <= $signed(13'd0)) begin
            // Underflow → signed zero (denorms not supported)
            result = {r_sign, 63'b0};
        end else begin
            // Normal result
            result = {r_sign, norm_exp[10:0], norm_man};
        end
    end

endmodule

// -----------------------------------------------------------------------------
// f64_add — Combinational IEEE-754 double-precision adder/subtractor
// Pure always_comb; no clock.
// Algorithm: swap so larger exponent is operand A, align B, add/subtract
// significands, normalise, round-to-nearest-even.
// Special cases: NaN propagation, Inf±Inf=NaN, Inf+finite=Inf.
// -----------------------------------------------------------------------------
module f64_add (
    input  logic [63:0] a,
    input  logic [63:0] b,
    output logic [63:0] result
);

    // Field extraction
    logic        a_sign, b_sign;
    logic [10:0] a_exp,  b_exp;
    logic [51:0] a_frac, b_frac;

    assign a_sign = a[63];
    assign b_sign = b[63];
    assign a_exp  = a[62:52];
    assign b_exp  = b[62:52];
    assign a_frac = a[51:0];
    assign b_frac = b[51:0];

    // Special-case detection
    logic a_nan, b_nan, a_inf, b_inf, a_zero, b_zero;
    assign a_nan  = (a_exp == 11'h7FF) && (a_frac != 52'h0);
    assign b_nan  = (b_exp == 11'h7FF) && (b_frac != 52'h0);
    assign a_inf  = (a_exp == 11'h7FF) && (a_frac == 52'h0);
    assign b_inf  = (b_exp == 11'h7FF) && (b_frac == 52'h0);
    assign a_zero = (a_exp == 11'h0)   && (a_frac == 52'h0);
    assign b_zero = (b_exp == 11'h0)   && (b_frac == 52'h0);

    // --- Swap so the larger magnitude is always the "big" operand ---
    logic        big_sign, sml_sign;
    logic [10:0] big_exp,  sml_exp;
    logic [52:0] big_man,  sml_man;  // implicit 1 prepended
    logic        do_swap;

    always_comb begin
        // Compare magnitudes (exp first, then mantissa)
        if (a_exp > b_exp) begin
            do_swap = 1'b0;
        end else if (b_exp > a_exp) begin
            do_swap = 1'b1;
        end else begin
            // Same exponent — compare fractions
            do_swap = (b_frac > a_frac);
        end

        if (do_swap) begin
            big_sign = b_sign; big_exp = b_exp;
            big_man  = (b_exp == 11'h0) ? {1'b0, b_frac} : {1'b1, b_frac};
            sml_sign = a_sign; sml_exp = a_exp;
            sml_man  = (a_exp == 11'h0) ? {1'b0, a_frac} : {1'b1, a_frac};
        end else begin
            big_sign = a_sign; big_exp = a_exp;
            big_man  = (a_exp == 11'h0) ? {1'b0, a_frac} : {1'b1, a_frac};
            sml_sign = b_sign; sml_exp = b_exp;
            sml_man  = (b_exp == 11'h0) ? {1'b0, b_frac} : {1'b1, b_frac};
        end
    end

    // --- Align smaller operand ---
    logic [5:0]  shift_amt;
    logic [52:0] sml_aligned;  // after right-shift (truncated; guard bits ignored)

    always_comb begin
        shift_amt = (big_exp - sml_exp > 63) ? 6'd63 : big_exp[5:0] - sml_exp[5:0];
        sml_aligned = sml_man >> shift_amt;
    end

    // --- Add or subtract significands ---
    // 54-bit sum to catch carry
    logic [53:0] sum_raw;
    logic        eff_sub;  // effective subtraction when signs differ
    logic        r_sign;

    always_comb begin
        eff_sub = big_sign ^ sml_sign;
        r_sign  = big_sign;
        if (!eff_sub) begin
            sum_raw = {1'b0, big_man} + {1'b0, sml_aligned};
        end else begin
            // big - small (big always >= small after swap)
            sum_raw = {1'b0, big_man} - {1'b0, sml_aligned};
        end
    end

    // --- Normalise ---
    logic [11:0]  res_exp;
    logic [51:0]  res_man;
    logic [52:0]  shifted;   // left-shifted significand for normalisation

    // Leading-zero count: iterate ascending so the highest set bit wins (last write).
    // lz_count = number of left shifts needed to place the MSB at bit 52.
    logic [5:0] lz_count;
    always_comb begin : lz_encoder
        lz_count = 6'd53;  // default: all-zero significand
        for (int i = 0; i <= 52; i++) begin
            if (sum_raw[i]) lz_count = 6'(52 - i);
        end
    end

    always_comb begin
        shifted = sum_raw[52:0] << lz_count;  // used in else branch below
        if (sum_raw[53]) begin
            // Carry out: right-shift 1, increment exponent
            res_exp = {1'b0, big_exp} + 12'd1;
            res_man = sum_raw[52:1];
        end else if (sum_raw[52]) begin
            // Already normalised
            res_exp = {1'b0, big_exp};
            res_man = sum_raw[51:0];
        end else begin
            // Left-shift to normalise; exponent decreases by lz_count
            res_exp = {1'b0, big_exp} - {6'b0, lz_count};
            res_man = shifted[51:0];
        end
    end

    // --- Final mux ---
    always_comb begin
        if (a_nan || b_nan) begin
            result = 64'h7FF8_0000_0000_0000;
        end else if (a_inf && b_inf && (a_sign != b_sign)) begin
            // Inf - Inf = NaN
            result = 64'h7FF8_0000_0000_0000;
        end else if (a_inf || b_inf) begin
            // Return whichever operand is Inf (or a if both)
            result = a_inf ? a : b;
        end else if (a_zero && b_zero) begin
            result = 64'h0000_0000_0000_0000;
        end else if (a_zero) begin
            result = b;
        end else if (b_zero) begin
            result = a;
        end else if (sum_raw == 54'h0) begin
            // Exact cancellation
            result = 64'h0000_0000_0000_0000;
        end else if (res_exp[11] || res_exp == 12'h0) begin
            // Underflow
            result = {r_sign, 63'b0};
        end else if (res_exp >= 12'h7FF) begin
            // Overflow → Inf
            result = {r_sign, 11'h7FF, 52'h0};
        end else begin
            result = {r_sign, res_exp[10:0], res_man};
        end
    end

endmodule

// -----------------------------------------------------------------------------
// gemm_systolic — 3×3 weight-stationary systolic GEMM, Option A
// Computes C = A × B (row-major F64 matrices).
// FSM: IDLE → LOAD → STEP0 → STEP1 → STEP2 → FINISH
// Each STEP accumulates one inner-dimension slice (k=0,1,2).
// 9 f64_mul + 9 f64_add instances run in parallel each cycle.
// -----------------------------------------------------------------------------
module gemm_systolic (
    input  logic        clk,
    input  logic        rst_n,
    input  logic        start,       // one-cycle pulse: latch A, B, begin compute
    input  logic [63:0] A [0:8],    // row-major: A[i*3+j]
    input  logic [63:0] B [0:8],
    output logic [63:0] C [0:8],
    output logic        done,        // single-cycle pulse when C is valid
    output logic        busy
);

    // FSM state encoding
    typedef enum logic [2:0] {
        IDLE   = 3'd0,
        LOAD   = 3'd1,
        STEP0  = 3'd2,
        STEP1  = 3'd3,
        STEP2  = 3'd4,
        FINISH = 3'd5
    } state_t;

    state_t state, state_nxt;

    // Registered copies of inputs and accumulators
    logic [63:0] A_reg [0:8];
    logic [63:0] B_reg [0:8];
    logic [63:0] acc   [0:8];

    // k-selector (which inner-dimension index is active this cycle)
    logic [1:0] k_sel;
    always_comb begin
        case (state)
            STEP0:   k_sel = 2'd0;
            STEP1:   k_sel = 2'd1;
            default: k_sel = 2'd2;  // STEP2 and others
        endcase
    end

    // Combinational multiply and add products for each (i,j) pair
    // mul_out[i][j] = A_reg[i*3+k] * B_reg[k*3+j]
    // add_out[i][j] = acc[i*3+j] + mul_out[i][j]
    logic [63:0] mul_out [0:2][0:2];
    logic [63:0] add_out [0:2][0:2];

    genvar gi, gj;
    generate
        for (gi = 0; gi < 3; gi++) begin : gen_row
            for (gj = 0; gj < 3; gj++) begin : gen_col
                // Select A column element for current k
                logic [63:0] a_elem, b_elem;
                always_comb begin
                    a_elem = A_reg[gi*3 + k_sel];
                    b_elem = B_reg[k_sel*3 + gj];
                end

                f64_mul u_mul (
                    .a      (a_elem),
                    .b      (b_elem),
                    .result (mul_out[gi][gj])
                );

                f64_add u_add (
                    .a      (acc[gi*3+gj]),
                    .b      (mul_out[gi][gj]),
                    .result (add_out[gi][gj])
                );
            end
        end
    endgenerate

    // FSM next-state
    always_comb begin
        state_nxt = state;
        case (state)
            IDLE:   if (start)  state_nxt = LOAD;
            LOAD:               state_nxt = STEP0;
            STEP0:              state_nxt = STEP1;
            STEP1:              state_nxt = STEP2;
            STEP2:              state_nxt = FINISH;
            FINISH:             state_nxt = IDLE;
            default:            state_nxt = IDLE;
        endcase
    end

    // FSM state register + datapath
    integer i, j;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            state <= IDLE;
            for (i = 0; i < 9; i++) begin
                A_reg[i] <= 64'h0;
                B_reg[i] <= 64'h0;
                acc[i]   <= 64'h0;
                C[i]     <= 64'h0;
            end
        end else begin
            state <= state_nxt;

            case (state)
                LOAD: begin
                    for (i = 0; i < 9; i++) begin
                        A_reg[i] <= A[i];
                        B_reg[i] <= B[i];
                        acc[i]   <= 64'h0;  // clear accumulators
                    end
                end

                STEP0, STEP1, STEP2: begin
                    // Register add_out into acc
                    for (i = 0; i < 3; i++) begin
                        for (j = 0; j < 3; j++) begin
                            acc[i*3+j] <= add_out[i][j];
                        end
                    end
                end

                FINISH: begin
                    for (i = 0; i < 9; i++) begin
                        C[i] <= acc[i];
                    end
                end

                default: ;
            endcase
        end
    end

    // Output signals
    assign done = (state == FINISH);
    assign busy = (state != IDLE) && (state != FINISH);

endmodule

// -----------------------------------------------------------------------------
// kalman_update — Kalman filter update kernel, Option B
// H = [1, 0, 0] (scalar measurement), R = 5.0 (F64)
// FSM: IDLE → INNOV → S_COMP → NR0 → NR1 → NR2 → K_COMP → X_CORR → P_UPD → WAIT_P → DONE
// Internally instantiates gemm_systolic for the IKH*P covariance update.
// -----------------------------------------------------------------------------
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

// -----------------------------------------------------------------------------
// axilite_slave — AXI4-Lite slave register file, DATA_WIDTH=64
// Register map (8-byte stride; one 64-bit beat per F64 element):
//   0x00        CTRL  R/W [0]=start one-shot [1]=soft_rst
//   0x08        STAT  RO  [0]=done  [1]=busy
//   0x10–0x50   A_REG[0:8] WO  F64 matrix A (stride 8)
//   0x58–0x98   B_REG[0:8] WO  F64 matrix B (stride 8)
//   0xA0–0xE0   C_REG[0:8] RO  F64 matrix C (stride 8)
// Address decode: addr[7:3] gives a 5-bit register index.
// -----------------------------------------------------------------------------
module axilite_slave #(
    parameter int ADDR_WIDTH = 32,
    parameter int DATA_WIDTH = 64
)(
    input  logic                      clk,
    input  logic                      rst_n,
    // AXI4-Lite write address channel
    input  logic [ADDR_WIDTH-1:0]     s_awaddr,
    input  logic                      s_awvalid,
    output logic                      s_awready,
    // AXI4-Lite write data channel
    input  logic [DATA_WIDTH-1:0]     s_wdata,
    input  logic [(DATA_WIDTH/8)-1:0] s_wstrb,
    input  logic                      s_wvalid,
    output logic                      s_wready,
    // AXI4-Lite write response channel
    output logic [1:0]                s_bresp,
    output logic                      s_bvalid,
    input  logic                      s_bready,
    // AXI4-Lite read address channel
    input  logic [ADDR_WIDTH-1:0]     s_araddr,
    input  logic                      s_arvalid,
    output logic                      s_arready,
    // AXI4-Lite read data channel
    output logic [DATA_WIDTH-1:0]     s_rdata,
    output logic [1:0]                s_rresp,
    output logic                      s_rvalid,
    input  logic                      s_rready,
    // Core control
    output logic                      core_start,
    output logic                      core_rst_n,
    output logic [63:0]               core_A [0:8],
    output logic [63:0]               core_B [0:8],
    // Core status
    input  logic [63:0]               core_C [0:8],
    input  logic                      core_done,
    input  logic                      core_busy
);

    // Internal registers
    logic [63:0] reg_ctrl;
    logic [63:0] reg_A [0:8];
    logic [63:0] reg_B [0:8];

    // Write handshake state
    logic        aw_done;   // AW channel captured
    logic        w_done;    // W channel captured
    logic [ADDR_WIDTH-1:0] aw_addr_lat;
    logic [DATA_WIDTH-1:0] w_data_lat;

    // core_start is a one-cycle pulse
    logic start_pending;

    // -----------------------------------------------------------------------
    // Write address channel
    // -----------------------------------------------------------------------
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            s_awready   <= 1'b1;
            aw_done     <= 1'b0;
            aw_addr_lat <= '0;
        end else begin
            if (s_awvalid && s_awready) begin
                aw_addr_lat <= s_awaddr;
                aw_done     <= 1'b1;
                s_awready   <= 1'b0;
            end else if (aw_done && w_done) begin
                // Transaction committed — re-arm
                aw_done   <= 1'b0;
                s_awready <= 1'b1;
            end
        end
    end

    // -----------------------------------------------------------------------
    // Write data channel
    // -----------------------------------------------------------------------
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            s_wready  <= 1'b1;
            w_done    <= 1'b0;
            w_data_lat <= '0;
        end else begin
            if (s_wvalid && s_wready) begin
                w_data_lat <= s_wdata;
                w_done     <= 1'b1;
                s_wready   <= 1'b0;
            end else if (aw_done && w_done) begin
                w_done    <= 1'b0;
                s_wready  <= 1'b1;
            end
        end
    end

    // -----------------------------------------------------------------------
    // Write execute — committed when both aw_done and w_done
    // Address decode: addr[7:3] gives register index in a flat 32-entry space:
    //   index 0  → CTRL (0x00)
    //   index 1  → STAT (0x08) — read-only; writes ignored
    //   index 2..10  → A_REG[0..8] (0x10–0x50)
    //   index 11..19 → B_REG[0..8] (0x58–0x98)
    //   index 20..28 → C_REG[0..8] (0xA0–0xE0) — read-only; writes ignored
    // -----------------------------------------------------------------------
    logic write_commit;
    assign write_commit = aw_done && w_done;

    logic [4:0] wr_idx;
    assign wr_idx = aw_addr_lat[7:3];

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            reg_ctrl      <= '0;
            start_pending <= 1'b0;
            for (int i = 0; i < 9; i++) begin
                reg_A[i] <= '0;
                reg_B[i] <= '0;
            end
        end else begin
            start_pending <= 1'b0;  // default: no start pulse

            if (write_commit) begin
                case (wr_idx)
                    5'd0: begin  // CTRL
                        reg_ctrl <= w_data_lat;
                        if (w_data_lat[0]) start_pending <= 1'b1;
                    end
                    // 5'd1 = STAT (RO — ignore)
                    5'd2:  reg_A[0] <= w_data_lat;
                    5'd3:  reg_A[1] <= w_data_lat;
                    5'd4:  reg_A[2] <= w_data_lat;
                    5'd5:  reg_A[3] <= w_data_lat;
                    5'd6:  reg_A[4] <= w_data_lat;
                    5'd7:  reg_A[5] <= w_data_lat;
                    5'd8:  reg_A[6] <= w_data_lat;
                    5'd9:  reg_A[7] <= w_data_lat;
                    5'd10: reg_A[8] <= w_data_lat;
                    5'd11: reg_B[0] <= w_data_lat;
                    5'd12: reg_B[1] <= w_data_lat;
                    5'd13: reg_B[2] <= w_data_lat;
                    5'd14: reg_B[3] <= w_data_lat;
                    5'd15: reg_B[4] <= w_data_lat;
                    5'd16: reg_B[5] <= w_data_lat;
                    5'd17: reg_B[6] <= w_data_lat;
                    5'd18: reg_B[7] <= w_data_lat;
                    5'd19: reg_B[8] <= w_data_lat;
                    // 5'd20..28 = C_REG (RO — ignore)
                    default: ;
                endcase
            end
        end
    end

    // -----------------------------------------------------------------------
    // Write response channel
    // -----------------------------------------------------------------------
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            s_bvalid <= 1'b0;
            s_bresp  <= 2'b00;
        end else begin
            if (write_commit && !s_bvalid) begin
                s_bvalid <= 1'b1;
                s_bresp  <= 2'b00;  // OKAY
            end else if (s_bvalid && s_bready) begin
                s_bvalid <= 1'b0;
            end
        end
    end

    // -----------------------------------------------------------------------
    // Read channel
    // -----------------------------------------------------------------------
    logic [4:0] rd_idx;
    assign rd_idx = s_araddr[7:3];

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            s_arready <= 1'b1;
            s_rvalid  <= 1'b0;
            s_rdata   <= '0;
            s_rresp   <= 2'b00;
        end else begin
            if (s_arvalid && s_arready) begin
                s_arready <= 1'b0;
                s_rvalid  <= 1'b1;
                s_rresp   <= 2'b00;
                case (rd_idx)
                    5'd0:  s_rdata <= reg_ctrl;
                    5'd1:  s_rdata <= {62'b0, core_busy, core_done};
                    5'd2:  s_rdata <= reg_A[0];
                    5'd3:  s_rdata <= reg_A[1];
                    5'd4:  s_rdata <= reg_A[2];
                    5'd5:  s_rdata <= reg_A[3];
                    5'd6:  s_rdata <= reg_A[4];
                    5'd7:  s_rdata <= reg_A[5];
                    5'd8:  s_rdata <= reg_A[6];
                    5'd9:  s_rdata <= reg_A[7];
                    5'd10: s_rdata <= reg_A[8];
                    5'd11: s_rdata <= reg_B[0];
                    5'd12: s_rdata <= reg_B[1];
                    5'd13: s_rdata <= reg_B[2];
                    5'd14: s_rdata <= reg_B[3];
                    5'd15: s_rdata <= reg_B[4];
                    5'd16: s_rdata <= reg_B[5];
                    5'd17: s_rdata <= reg_B[6];
                    5'd18: s_rdata <= reg_B[7];
                    5'd19: s_rdata <= reg_B[8];
                    5'd20: s_rdata <= core_C[0];
                    5'd21: s_rdata <= core_C[1];
                    5'd22: s_rdata <= core_C[2];
                    5'd23: s_rdata <= core_C[3];
                    5'd24: s_rdata <= core_C[4];
                    5'd25: s_rdata <= core_C[5];
                    5'd26: s_rdata <= core_C[6];
                    5'd27: s_rdata <= core_C[7];
                    5'd28: s_rdata <= core_C[8];
                    default: s_rdata <= '0;
                endcase
            end else if (s_rvalid && s_rready) begin
                s_rvalid  <= 1'b0;
                s_arready <= 1'b1;
            end
        end
    end

    // -----------------------------------------------------------------------
    // Core control outputs
    // -----------------------------------------------------------------------
    assign core_start = start_pending;
    assign core_rst_n = rst_n & ~reg_ctrl[1];

    generate
        for (genvar gi = 0; gi < 9; gi++) begin : gen_core_ab
            assign core_A[gi] = reg_A[gi];
            assign core_B[gi] = reg_B[gi];
        end
    endgenerate

endmodule

// =============================================================================
// top — M3 integration top: AXI4-Lite slave + Kalman update accelerator
//
// External ports:
//   clk          input  logic         System clock (100 MHz)
//   rst_n        input  logic         Active-low synchronous reset
//   s_awaddr     input  [31:0]        AXI write address
//   s_awvalid    input  logic         AXI write address valid
//   s_awready    output logic         AXI write address ready
//   s_wdata      input  [63:0]        AXI write data (64-bit)
//   s_wstrb      input  [7:0]         AXI write byte strobes
//   s_wvalid     input  logic         AXI write data valid
//   s_wready     output logic         AXI write data ready
//   s_bresp      output [1:0]         AXI write response (always OKAY)
//   s_bvalid     output logic         AXI write response valid
//   s_bready     input  logic         AXI write response ready
//   s_araddr     input  [31:0]        AXI read address
//   s_arvalid    input  logic         AXI read address valid
//   s_arready    output logic         AXI read address ready
//   s_rdata      output [63:0]        AXI read data
//   s_rresp      output [1:0]         AXI read response (always OKAY)
//   s_rvalid     output logic         AXI read data valid
//   s_rready     input  logic         AXI read data ready
//
// Register map (via axilite_slave, 8-byte stride):
//   0x00  CTRL  R/W  [0]=start one-shot, [1]=soft_rst
//   0x08  STAT  RO   [0]=done, [1]=busy
//   0x10  A_REG[0]   z (measurement scalar)
//   0x18  A_REG[1]   x_in[0] (prior state element 0)
//   0x20  A_REG[2]   x_in[1]
//   0x28  A_REG[3]   x_in[2]
//   0x30–0x50  A_REG[4:8]  unused (write ignored)
//   0x58–0x98  B_REG[0:8]  P_in[0:8] (prior covariance 3×3, row-major)
//   0xA0  C_REG[0]   x_out[0] (corrected state element 0)
//   0xA8  C_REG[1]   x_out[1]
//   0xB0  C_REG[2]   x_out[2]
//   0xB8  C_REG[3]   P_out[0]
//   ...   C_REG[4:8] P_out[1:5]
//
// Sub-modules instantiated:
//   u_slave  axilite_slave  AXI4-Lite register file
//   u_core   kalman_update  Kalman filter update kernel (wraps gemm_systolic)
// =============================================================================
module top #(
    parameter int ADDR_WIDTH = 32,
    parameter int DATA_WIDTH = 64
)(
    input  logic                      clk,
    input  logic                      rst_n,
    // AXI4-Lite slave port
    input  logic [ADDR_WIDTH-1:0]     s_awaddr,
    input  logic                      s_awvalid,
    output logic                      s_awready,
    input  logic [DATA_WIDTH-1:0]     s_wdata,
    input  logic [(DATA_WIDTH/8)-1:0] s_wstrb,
    input  logic                      s_wvalid,
    output logic                      s_wready,
    output logic [1:0]                s_bresp,
    output logic                      s_bvalid,
    input  logic                      s_bready,
    input  logic [ADDR_WIDTH-1:0]     s_araddr,
    input  logic                      s_arvalid,
    output logic                      s_arready,
    output logic [DATA_WIDTH-1:0]     s_rdata,
    output logic [1:0]                s_rresp,
    output logic                      s_rvalid,
    input  logic                      s_rready
);

    // Internal wires from axilite_slave
    logic        core_start, core_rst_n, core_done, core_busy;
    logic [63:0] slave_A [0:8];  // A_REG[0]=z, A_REG[1:3]=x_in, A_REG[4:8]=unused
    logic [63:0] slave_B [0:8];  // B_REG[0:8]=P_in
    logic [63:0] slave_C [0:8];  // feeds kalman_update outputs back to AXI read path

    // Unpacked array slice for x_in (unpacked ports cannot accept packed concatenation)
    logic [63:0] x_in_wire [0:2];

    // Kalman update output wires
    logic [63:0] x_out [0:2];
    logic [63:0] P_out [0:8];

    assign x_in_wire[0] = slave_A[1];
    assign x_in_wire[1] = slave_A[2];
    assign x_in_wire[2] = slave_A[3];

    // Map kalman outputs into the slave C register view
    // C_REG[0:2] = x_out[0:2]; C_REG[3:8] = P_out[0:5]
    assign slave_C[0] = x_out[0];
    assign slave_C[1] = x_out[1];
    assign slave_C[2] = x_out[2];
    assign slave_C[3] = P_out[0];
    assign slave_C[4] = P_out[1];
    assign slave_C[5] = P_out[2];
    assign slave_C[6] = P_out[3];
    assign slave_C[7] = P_out[4];
    assign slave_C[8] = P_out[5];

    axilite_slave #(
        .ADDR_WIDTH (ADDR_WIDTH),
        .DATA_WIDTH (DATA_WIDTH)
    ) u_slave (
        .clk        (clk),
        .rst_n      (rst_n),
        .s_awaddr   (s_awaddr),  .s_awvalid (s_awvalid), .s_awready (s_awready),
        .s_wdata    (s_wdata),   .s_wstrb   (s_wstrb),
        .s_wvalid   (s_wvalid),  .s_wready  (s_wready),
        .s_bresp    (s_bresp),   .s_bvalid  (s_bvalid),  .s_bready  (s_bready),
        .s_araddr   (s_araddr),  .s_arvalid (s_arvalid), .s_arready (s_arready),
        .s_rdata    (s_rdata),   .s_rresp   (s_rresp),
        .s_rvalid   (s_rvalid),  .s_rready  (s_rready),
        .core_start (core_start),
        .core_rst_n (core_rst_n),
        .core_A     (slave_A),
        .core_B     (slave_B),
        .core_C     (slave_C),
        .core_done  (core_done),
        .core_busy  (core_busy)
    );

    // Input mapping: A_REG[0]=z, A_REG[1:3]=x_in, B_REG[0:8]=P_in
    kalman_update u_core (
        .clk   (clk),
        .rst_n (core_rst_n),
        .start (core_start),
        .z     (slave_A[0]),
        .x_in  (x_in_wire),
        .P_in  (slave_B),
        .x_out (x_out),
        .P_out (P_out),
        .done  (core_done),
        .busy  (core_busy)
    );

endmodule
