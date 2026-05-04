`timescale 1ns/1ps
// =============================================================================
// tb_compute_core.sv
// Self-checking testbench for compute_core (project/m2/rtl/compute_core.sv).
//
// Representative input
// --------------------
// All 45 projectile-motion measurements from kalman_profile.py
// (project/profiling/kalman_profile.py, MEASUREMENTS array).
// These measurements exercise tiled_matmul — the dominant kernel per
// project_profile_tiled.txt (405 calls/run, >80% of total runtime) — across
// the full filter trajectory: positive acceleration, peak, and deceleration
// including negative measurements.  An all-zeros input would never activate
// the gain computation or covariance update paths.
//
// Reference values
// ----------------
// Derived from the kalman_profile.py KalmanFilter algorithm (same Q, R, P_init,
// dt, and A, C matrices) with initial state x=[0,0,0] to match the hardware
// synchronous reset.  The reference was computed by a standalone Python
// simulation of the exact Q16.16 fixed-point arithmetic (no RTL run):
//
//   x0_ref = -31152   (-0.47534 in float, Q16.16)
//   x1_ref = -546812  (-8.34369 in float, Q16.16)
//   x2_ref = -677100  (-10.33173 in float, Q16.16)
//
// Tolerance = 8192 LSBs (0.125 in float).  The float64 reference computed
// directly from kalman_profile.py run_filter() (which uses x_init =
// [measurements[0], 0, -9.81]) gives x0 = -32881, within 0.025 of the
// HDL-matching reference, confirming the filter has converged by update 45.
//
// Pass / Fail
// -----------
// The final line of the simulation log is either:
//   PASS
// or:
//   FAIL  x0_err=<v> x1_err=<v> x2_err=<v>  (all Q16.16 LSBs)
// =============================================================================

module tb_compute_core;

    // -----------------------------------------------------------------------
    // Parameters
    // -----------------------------------------------------------------------
    localparam int DATA_WIDTH = 32;
    localparam int FRAC_BITS  = 16;
    localparam int CLK_HALF   = 5;   // half-period ns  → 100 MHz
    localparam int N_MEAS     = 45;
    localparam int TIMEOUT    = 20;  // max cycles to wait for valid_out

    // -----------------------------------------------------------------------
    // DUT ports
    // -----------------------------------------------------------------------
    logic                         clk;
    logic                         rst;
    logic                         valid_in;
    logic signed [DATA_WIDTH-1:0] y;
    logic signed [DATA_WIDTH-1:0] x_hat_0, x_hat_1, x_hat_2;
    logic                         valid_out;

    // -----------------------------------------------------------------------
    // DUT instantiation
    // -----------------------------------------------------------------------
    compute_core #(
        .DATA_WIDTH(DATA_WIDTH),
        .FRAC_BITS (FRAC_BITS)
    ) dut (
        .clk      (clk),
        .rst      (rst),
        .valid_in (valid_in),
        .y        (y),
        .x_hat_0  (x_hat_0),
        .x_hat_1  (x_hat_1),
        .x_hat_2  (x_hat_2),
        .valid_out(valid_out)
    );

    // -----------------------------------------------------------------------
    // Clock
    // -----------------------------------------------------------------------
    initial clk = 1'b0;
    always #CLK_HALF clk = ~clk;

    // -----------------------------------------------------------------------
    // Reference values (Q16.16)
    // Computed by the kalman_profile.py algorithm in Q16.16 fixed-point
    // arithmetic (Python simulation, independent of any RTL run).
    // -----------------------------------------------------------------------
    localparam signed [DATA_WIDTH-1:0] X0_REF    = -32'sd31152;
    localparam signed [DATA_WIDTH-1:0] X1_REF    = -32'sd546812;
    localparam signed [DATA_WIDTH-1:0] X2_REF    = -32'sd677100;
    localparam signed [DATA_WIDTH-1:0] TOLERANCE =  32'sd8192;  // 0.125 in float

    // -----------------------------------------------------------------------
    // 45 measurements as Q16.16 (from kalman_profile.py MEASUREMENTS array)
    // Representative: non-trivial trajectory exercising all FSM stages and
    // the tiled_matmul kernel (dominant hot-spot in project_profile_tiled.txt)
    // -----------------------------------------------------------------------
    logic signed [DATA_WIDTH-1:0] meas [0:N_MEAS-1];

    initial begin
        meas[ 0] =  32'sd68290;   // +1.0420271006
        meas[ 1] =  32'sd72566;   // +1.1072679045
        meas[ 2] =  32'sd84630;   // +1.2913511148
        meas[ 3] =  32'sd97311;   // +1.4848525095
        meas[ 4] =  32'sd113263;  // +1.7282590103
        meas[ 5] =  32'sd114175;  // +1.7421648974
        meas[ 6] =  32'sd138721;  // +2.1167203977
        meas[ 7] =  32'sd140594;  // +2.1452922511
        meas[ 8] =  32'sd141577;  // +2.1602964140
        meas[ 9] =  32'sd145011;  // +2.2126937113
        meas[10] =  32'sd168892;  // +2.5770935024
        meas[11] =  32'sd174865;  // +2.6682215744
        meas[12] =  32'sd164916;  // +2.5164183943
        meas[13] =  32'sd180902;  // +2.7603405678
        meas[14] =  32'sd188830;  // +2.8813178062
        meas[15] =  32'sd188989;  // +2.8837378652
        meas[16] =  32'sd192993;  // +2.9448468727
        meas[17] =  32'sd185379;  // +2.8286660013
        meas[18] =  32'sd196651;  // +3.0006601946
        meas[19] =  32'sd205076;  // +3.1292059167
        meas[20] =  32'sd187326;  // +2.8583617830
        meas[21] =  32'sd185997;  // +2.8380817035
        meas[22] =  32'sd176276;  // +2.6897533096
        meas[23] =  32'sd174675;  // +2.6653318559
        meas[24] =  32'sd184558;  // +2.8161349953
        meas[25] =  32'sd184159;  // +2.8100361205
        meas[26] =  32'sd188955;  // +2.8832184935
        meas[27] =  32'sd176809;  // +2.6978926483
        meas[28] =  32'sd159529;  // +2.4342229249
        meas[29] =  32'sd146450;  // +2.2346479182
        meas[30] =  32'sd150915;  // +2.3027877622
        meas[31] =  32'sd132428;  // +2.0206977039
        meas[32] =  32'sd127398;  // +1.9439398581
        meas[33] =  32'sd119602;  // +1.8249839874
        meas[34] =  32'sd99960;   // +1.5252623035
        meas[35] =  32'sd122531;  // +1.8696780817
        meas[36] =  32'sd77380;   // +1.1807320785
        meas[37] =  32'sd72568;   // +1.1072960509
        meas[38] =  32'sd60042;   // +0.9161683499
        meas[39] =  32'sd44469;   // +0.6785476645
        meas[40] =  32'sd36856;   // +0.5623817516
        meas[41] =  32'sd23296;   // +0.3554684749
        meas[42] = -32'sd10198;   // -0.1556074866
        meas[43] = -32'sd18822;   // -0.2871986610
        meas[44] = -32'sd39516;   // -0.6029731738
    end

    // -----------------------------------------------------------------------
    // Stimulus and self-checking
    // -----------------------------------------------------------------------
    integer i, wcnt;
    logic signed [DATA_WIDTH-1:0] e0, e1, e2;
    logic all_pass;

    initial begin
        $dumpfile("../sim/tb_compute_core.vcd");
        $dumpvars(0, tb_compute_core);

        valid_in = 1'b0;
        y        = '0;
        rst      = 1'b1;

        // Hold reset for 3 rising edges
        repeat (3) @(posedge clk);
        #1;
        rst = 1'b0;
        @(posedge clk); #1;

        // --- Drive all 45 measurements ---
        for (i = 0; i < N_MEAS; i++) begin
            valid_in = 1'b1;
            y        = meas[i];
            @(posedge clk); #1;
            valid_in = 1'b0;
            y        = '0;

            // Poll for valid_out (7-cycle latency per spec)
            wcnt = 0;
            while (!valid_out && wcnt < TIMEOUT) begin
                @(posedge clk); #1;
                wcnt++;
            end

            if (!valid_out) begin
                $display("[TIMEOUT] valid_out not seen after measurement %0d", i);
                $display("FAIL");
                $finish;
            end
        end

        // --- Compare final state to reference ---
        // Outputs are registered on the DONE clock edge; valid_out is HIGH now.
        e0 = x_hat_0 - X0_REF;
        e1 = x_hat_1 - X1_REF;
        e2 = x_hat_2 - X2_REF;
        // Absolute value (signed, so negate if negative)
        if (e0[DATA_WIDTH-1]) e0 = -e0;
        if (e1[DATA_WIDTH-1]) e1 = -e1;
        if (e2[DATA_WIDTH-1]) e2 = -e2;

        $display("--- compute_core output (Q16.16) ---");
        $display("  x_hat_0 = %0d  ref = %0d  |err| = %0d", x_hat_0, X0_REF, e0);
        $display("  x_hat_1 = %0d  ref = %0d  |err| = %0d", x_hat_1, X1_REF, e1);
        $display("  x_hat_2 = %0d  ref = %0d  |err| = %0d", x_hat_2, X2_REF, e2);
        $display("  tolerance = %0d LSBs", TOLERANCE);

        all_pass = (e0 <= TOLERANCE) && (e1 <= TOLERANCE) && (e2 <= TOLERANCE);

        if (all_pass)
            $display("PASS");
        else
            $display("FAIL  x0_err=%0d x1_err=%0d x2_err=%0d", e0, e1, e2);

        $finish;
    end

endmodule
