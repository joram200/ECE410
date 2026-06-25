// gemm_systolic.sv — 3×3 weight-stationary systolic GEMM, Option A
// Computes C = A × B (row-major F64 matrices).
// FSM: IDLE → LOAD → STEP0 → STEP1 → STEP2 → FINISH
// Each STEP accumulates one inner-dimension slice (k=0,1,2).
// 9 f64_mul + 9 f64_add instances run in parallel each cycle.

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
