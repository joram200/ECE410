`timescale 1ns/1ps
// Kalman Filter Hardware Compute Core
// Implements kf.update() for the 1-D projectile motion filter from
// https://github.com/hmartiro/kalman-cpp  (n=3 state, m=1 measurement)
//
// Arithmetic: Q16.16 fixed-point  (DATA_WIDTH=32, FRAC_BITS=16)
// Latency:    7 clock cycles per update (one FSM state per major step)
// Protocol:   pulse valid_in with new measurement y; valid_out pulses
//             for one cycle when x_hat_0/1/2 hold the corrected state.

module kalman_filter #(
    parameter int DATA_WIDTH = 32,
    parameter int FRAC_BITS  = 16
)(
    input  logic                         clk,
    input  logic                         rst,
    input  logic                         valid_in,
    input  logic signed [DATA_WIDTH-1:0] y,
    output logic signed [DATA_WIDTH-1:0] x_hat_0,
    output logic signed [DATA_WIDTH-1:0] x_hat_1,
    output logic signed [DATA_WIDTH-1:0] x_hat_2,
    output logic                         valid_out
);

    // -----------------------------------------------------------------------
    // Fixed-point constants (Q16.16)
    // -----------------------------------------------------------------------
    localparam signed [DATA_WIDTH-1:0] FP_ONE = 32'sd65536;    // 1.0
    localparam signed [DATA_WIDTH-1:0] FP_DT  = 32'sd2185;     // 1/30
    localparam signed [DATA_WIDTH-1:0] FP_Q00 = 32'sd3277;     // 0.05
    localparam signed [DATA_WIDTH-1:0] FP_R   = 32'sd327680;   // 5.0

    // P initialisation values (from kalman-test.cpp)
    localparam signed [DATA_WIDTH-1:0] P00_INIT = 32'sd6554;       // 0.1
    localparam signed [DATA_WIDTH-1:0] P01_INIT = 32'sd6554;       // 0.1
    localparam signed [DATA_WIDTH-1:0] P02_INIT = 32'sd6554;       // 0.1
    localparam signed [DATA_WIDTH-1:0] P11_INIT = 32'sd655360000;  // 1e4
    localparam signed [DATA_WIDTH-1:0] P12_INIT = 32'sd655360;     // 10
    localparam signed [DATA_WIDTH-1:0] P22_INIT = 32'sd6553600;    // 100

    // -----------------------------------------------------------------------
    // Fixed-point multiply: Q16.16 * Q16.16 -> Q16.16
    // -----------------------------------------------------------------------
    function automatic logic signed [DATA_WIDTH-1:0] fp_mul(
        input logic signed [DATA_WIDTH-1:0] a,
        input logic signed [DATA_WIDTH-1:0] b
    );
        logic signed [2*DATA_WIDTH-1:0] prod;
        prod = (64'(signed'(a)) * 64'(signed'(b)));
        return prod[DATA_WIDTH-1+FRAC_BITS : FRAC_BITS];
    endfunction

    // -----------------------------------------------------------------------
    // FSM state encoding
    // -----------------------------------------------------------------------
    typedef enum logic [2:0] {
        IDLE   = 3'd0,
        PRED_X = 3'd1,
        PRED_P = 3'd2,
        INNOV  = 3'd3,
        KG     = 3'd4,
        CORR   = 3'd5,
        DONE   = 3'd6
    } state_t;

    state_t state;

    // -----------------------------------------------------------------------
    // State vector registers  x = [pos, vel, acc]
    // -----------------------------------------------------------------------
    logic signed [DATA_WIDTH-1:0] x0, x1, x2;

    // -----------------------------------------------------------------------
    // Covariance matrix P (symmetric 3x3, 6 unique entries)
    // -----------------------------------------------------------------------
    logic signed [DATA_WIDTH-1:0] p00, p01, p02, p11, p12, p22;

    // -----------------------------------------------------------------------
    // Scratch registers used across FSM stages
    // -----------------------------------------------------------------------
    logic signed [DATA_WIDTH-1:0] y_reg;      // latched measurement
    logic signed [DATA_WIDTH-1:0] x0p, x1p, x2p;  // predicted state
    // Predicted P (pp = A*P*A' + Q)
    logic signed [DATA_WIDTH-1:0] pp00, pp01, pp02, pp11, pp12, pp22;
    logic signed [DATA_WIDTH-1:0] s_reg;      // innovation variance S = P[0,0]+R
    logic signed [DATA_WIDTH-1:0] k0, k1, k2; // Kalman gain

    // -----------------------------------------------------------------------
    // Output registers
    // -----------------------------------------------------------------------
    logic signed [DATA_WIDTH-1:0] x0_out, x1_out, x2_out;
    logic                         vout;

    assign x_hat_0  = x0_out;
    assign x_hat_1  = x1_out;
    assign x_hat_2  = x2_out;
    assign valid_out = vout;

    // -----------------------------------------------------------------------
    // Main FSM
    // -----------------------------------------------------------------------
    always_ff @(posedge clk) begin
        if (rst) begin
            state  <= IDLE;
            vout   <= 1'b0;
            x0     <= '0;  x1    <= '0;  x2    <= '0;
            x0_out <= '0;  x1_out <= '0; x2_out <= '0;
            p00    <= P00_INIT; p01 <= P01_INIT; p02 <= P02_INIT;
            p11    <= P11_INIT; p12 <= P12_INIT; p22 <= P22_INIT;
            y_reg  <= '0;
            x0p    <= '0;  x1p   <= '0;  x2p   <= '0;
            pp00   <= '0;  pp01  <= '0;  pp02  <= '0;
            pp11   <= '0;  pp12  <= '0;  pp22  <= '0;
            s_reg  <= FP_ONE;
            k0     <= '0;  k1    <= '0;  k2    <= '0;
        end else begin
            vout <= 1'b0; // default: deassert

            case (state)
                // ----------------------------------------------------------
                IDLE: begin
                    if (valid_in) begin
                        y_reg <= y;
                        state <= PRED_X;
                    end
                end

                // ----------------------------------------------------------
                // Predict state:  x_new = A * x
                //   A = [[1, dt, 0],
                //        [0,  1, dt],
                //        [0,  0,  1]]
                // x0' = x0 + dt*x1
                // x1' = x1 + dt*x2
                // x2' = x2
                // ----------------------------------------------------------
                PRED_X: begin
                    x0p   <= x0 + fp_mul(FP_DT, x1);
                    x1p   <= x1 + fp_mul(FP_DT, x2);
                    x2p   <= x2;
                    state <= PRED_P;
                end

                // ----------------------------------------------------------
                // Predict covariance:  P = A*P*A' + Q
                //
                // With A = [[1,dt,0],[0,1,dt],[0,0,1]] and Q diagonal(Q00,Q00,0):
                //
                // pp00 = p00 + dt*(p01+p10) + dt^2*p11 + Q00
                // pp01 = p01 + dt*(p02+p11) + dt^2*p12   (=pp10)
                // pp02 = p02 + dt*p12                     (=pp20)
                // pp11 = p11 + dt*(p12+p21) + dt^2*p22 + Q00
                // pp12 = p12 + dt*p22                     (=pp21)
                // pp22 = p22
                // ----------------------------------------------------------
                PRED_P: begin
                    pp00 <= p00
                          + fp_mul(FP_DT, p01) + fp_mul(FP_DT, p01)
                          + fp_mul(FP_DT, fp_mul(FP_DT, p11))
                          + FP_Q00;
                    pp01 <= p01
                          + fp_mul(FP_DT, p02) + fp_mul(FP_DT, p11)
                          + fp_mul(FP_DT, fp_mul(FP_DT, p12));
                    pp02 <= p02 + fp_mul(FP_DT, p12);
                    pp11 <= p11
                          + fp_mul(FP_DT, p12) + fp_mul(FP_DT, p12)
                          + fp_mul(FP_DT, fp_mul(FP_DT, p22))
                          + FP_Q00;
                    pp12 <= p12 + fp_mul(FP_DT, p22);
                    pp22 <= p22;
                    state <= INNOV;
                end

                // ----------------------------------------------------------
                // Innovation covariance:  S = C*P*C' + R
                //   C = [1, 0, 0]  =>  S = pp00 + R  (scalar)
                // ----------------------------------------------------------
                INNOV: begin
                    s_reg <= pp00 + FP_R;
                    state <= KG;
                end

                // ----------------------------------------------------------
                // Kalman gain:  K = P*C' / S
                //   C' = [1;0;0]  =>  K = P[:,0] / S
                // Division: shift numerator left by FRAC_BITS then divide
                // ----------------------------------------------------------
                KG: begin
                    k0    <= DATA_WIDTH'(signed'((64'(signed'(pp00)) <<< FRAC_BITS) / 64'(signed'(s_reg))));
                    k1    <= DATA_WIDTH'(signed'((64'(signed'(pp01)) <<< FRAC_BITS) / 64'(signed'(s_reg))));
                    k2    <= DATA_WIDTH'(signed'((64'(signed'(pp02)) <<< FRAC_BITS) / 64'(signed'(s_reg))));
                    state <= CORR;
                end

                // ----------------------------------------------------------
                // Correct state:       x = x' + K*(y - C*x')
                //   innov = y - x0' (since C = [1,0,0])
                //
                // Correct covariance:  P = (I - K*C)*P'
                //   K*C = K * [1,0,0]  so only first column of P' is affected:
                //   p00 = pp00 - fp_mul(k0, pp00)
                //   p01 = pp01 - fp_mul(k0, pp01)
                //   p02 = pp02 - fp_mul(k0, pp02)
                //   p11 = pp11 - fp_mul(k1, pp01)
                //   p12 = pp12 - fp_mul(k1, pp02)
                //   p22 = pp22 - fp_mul(k2, pp02)
                // ----------------------------------------------------------
                CORR: begin
                    // Innovation
                    logic signed [DATA_WIDTH-1:0] innov;
                    innov = y_reg - x0p;

                    // Corrected state
                    x0 <= x0p + fp_mul(k0, innov);
                    x1 <= x1p + fp_mul(k1, innov);
                    x2 <= x2p + fp_mul(k2, innov);

                    // Corrected covariance  P = (I - K*C) * P'
                    p00 <= pp00 - fp_mul(k0, pp00);
                    p01 <= pp01 - fp_mul(k0, pp01);
                    p02 <= pp02 - fp_mul(k0, pp02);
                    p11 <= pp11 - fp_mul(k1, pp01);
                    p12 <= pp12 - fp_mul(k1, pp02);
                    p22 <= pp22 - fp_mul(k2, pp02);

                    state <= DONE;
                end

                // ----------------------------------------------------------
                DONE: begin
                    x0_out <= x0;
                    x1_out <= x1;
                    x2_out <= x2;
                    vout   <= 1'b1;
                    state  <= IDLE;
                end

                default: state <= IDLE;
            endcase
        end
    end

endmodule
