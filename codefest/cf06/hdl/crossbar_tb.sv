`timescale 1ns/1ps
// =============================================================================
// Module:      crossbar_tb
// Description: Testbench for crossbar_mac.
//              All messages are written to both stdout and sim.log.
//
//   Loads weight matrix:
//       weight = [[ +1, -1, +1, -1 ],   // row 0 (in[0])
//                 [ +1, +1, -1, -1 ],   // row 1 (in[1])
//                 [ -1, +1, +1, -1 ],   // row 2 (in[2])
//                 [ -1, -1, -1, +1 ]]   // row 3 (in[3])
//
//   Applies inputs:  in = [10, 20, 30, 40]
//
//   Expected outputs (out[j] = SUM_i weight[i][j]*in[i]):
//       out[0] = (+1)*10 + (+1)*20 + (-1)*30 + (-1)*40 = -40
//       out[1] = (-1)*10 + (+1)*20 + (+1)*30 + (-1)*40 =   0
//       out[2] = (+1)*10 + (-1)*20 + (+1)*30 + (-1)*40 = -20
//       out[3] = (-1)*10 + (-1)*20 + (-1)*30 + (+1)*40 = -20
// =============================================================================

module crossbar_tb;

    // -------------------------------------------------------------------------
    // DUT signals
    // -------------------------------------------------------------------------
    logic              clk;
    logic              rst;
    logic signed [7:0] in  [3:0];
    logic signed [7:0] out [3:0];
    logic              we;
    logic [1:0]        w_row;
    logic [1:0]        w_col;
    logic              w_val;

    // -------------------------------------------------------------------------
    // DUT instantiation
    // -------------------------------------------------------------------------
    crossbar_mac dut (
        .clk   (clk),
        .rst   (rst),
        .in    (in),
        .out   (out),
        .we    (we),
        .w_row (w_row),
        .w_col (w_col),
        .w_val (w_val)
    );

    // -------------------------------------------------------------------------
    // Clock: 10 ns period
    // -------------------------------------------------------------------------
    initial clk = 0;
    always #5 clk = ~clk;

    // -------------------------------------------------------------------------
    // Log file handle (opened in initial block before any other use)
    // -------------------------------------------------------------------------
    integer log_fd;

    // Write a message to both stdout and sim.log
    task automatic log_msg(input string msg);
        $display("%s", msg);
        $fdisplay(log_fd, "%s", msg);
    endtask

    // Log the current output vector with a label
    task automatic log_outputs(input string label);
        log_msg($sformatf("[%0t ns] %s: out = [%0d, %0d, %0d, %0d]",
                          $time, label, out[0], out[1], out[2], out[3]));
    endtask

    // -------------------------------------------------------------------------
    // Weight write task: one cycle per entry
    // -------------------------------------------------------------------------
    task automatic write_weight(
        input logic [1:0] row,
        input logic [1:0] col,
        input logic       val    // 0 = +1, 1 = -1
    );
        @(negedge clk);
        we    = 1'b1;
        w_row = row;
        w_col = col;
        w_val = val;
        @(posedge clk);
        #1;
        we = 1'b0;
    endtask

    // -------------------------------------------------------------------------
    // Main stimulus
    // -------------------------------------------------------------------------
    integer pass_count = 0;
    integer fail_count = 0;

    initial begin
        // -- Open log file ---------------------------------------------
        log_fd = $fopen("sim.log", "w");
        if (log_fd == 0)
            $fatal(1, "ERROR: could not open sim.log");

        // -- Initialise -------------------------------------------------
        rst   = 1'b1;
        we    = 1'b0;
        w_row = '0;
        w_col = '0;
        w_val = '0;
        in[0] = 8'sh00;
        in[1] = 8'sh00;
        in[2] = 8'sh00;
        in[3] = 8'sh00;

        // -- Reset for 2 cycles ----------------------------------------
        repeat (2) @(posedge clk);
        #1;
        rst = 1'b0;
        log_msg($sformatf("[%0t ns] Reset released.", $time));

        // -- Load weight matrix ----------------------------------------
        // weight[row][col]: 0 = +1, 1 = -1
        // Row 0: [ +1, -1, +1, -1 ]
        write_weight(2'd0, 2'd0, 1'b0);
        write_weight(2'd0, 2'd1, 1'b1);
        write_weight(2'd0, 2'd2, 1'b0);
        write_weight(2'd0, 2'd3, 1'b1);
        // Row 1: [ +1, +1, -1, -1 ]
        write_weight(2'd1, 2'd0, 1'b0);
        write_weight(2'd1, 2'd1, 1'b0);
        write_weight(2'd1, 2'd2, 1'b1);
        write_weight(2'd1, 2'd3, 1'b1);
        // Row 2: [ -1, +1, +1, -1 ]
        write_weight(2'd2, 2'd0, 1'b1);
        write_weight(2'd2, 2'd1, 1'b0);
        write_weight(2'd2, 2'd2, 1'b0);
        write_weight(2'd2, 2'd3, 1'b1);
        // Row 3: [ -1, -1, -1, +1 ]
        write_weight(2'd3, 2'd0, 1'b1);
        write_weight(2'd3, 2'd1, 1'b1);
        write_weight(2'd3, 2'd2, 1'b1);
        write_weight(2'd3, 2'd3, 1'b0);

        log_msg($sformatf("[%0t ns] Weights loaded.", $time));

        // -- Apply inputs ----------------------------------------------
        @(negedge clk);
        in[0] = 8'sh0A;   // 10
        in[1] = 8'sh14;   // 20
        in[2] = 8'sh1E;   // 30
        in[3] = 8'sh28;   // 40
        log_msg($sformatf("[%0t ns] Inputs applied: in = [%0d, %0d, %0d, %0d]",
                          $time, in[0], in[1], in[2], in[3]));

        // -- Wait one clock cycle for output register to capture -------
        @(posedge clk);
        #1;
        log_outputs("MAC result");

        // -- Check outputs ---------------------------------------------
        log_msg($sformatf("[%0t ns] --- Checking outputs ---", $time));

        if (out[0] === 8'shD8) begin   // -40
            log_msg($sformatf("  PASS  out[0] = %0d (expected -40)", out[0]));
            pass_count++;
        end else begin
            log_msg($sformatf("  FAIL  out[0] = %0d (expected -40)", out[0]));
            fail_count++;
        end

        if (out[1] === 8'sh00) begin   // 0
            log_msg($sformatf("  PASS  out[1] = %0d (expected  0)", out[1]));
            pass_count++;
        end else begin
            log_msg($sformatf("  FAIL  out[1] = %0d (expected  0)", out[1]));
            fail_count++;
        end

        if (out[2] === 8'shEC) begin   // -20
            log_msg($sformatf("  PASS  out[2] = %0d (expected -20)", out[2]));
            pass_count++;
        end else begin
            log_msg($sformatf("  FAIL  out[2] = %0d (expected -20)", out[2]));
            fail_count++;
        end

        if (out[3] === 8'shEC) begin   // -20
            log_msg($sformatf("  PASS  out[3] = %0d (expected -20)", out[3]));
            pass_count++;
        end else begin
            log_msg($sformatf("  FAIL  out[3] = %0d (expected -20)", out[3]));
            fail_count++;
        end

        log_msg($sformatf("[%0t ns] --- Results: %0d passed, %0d failed ---",
                          $time, pass_count, fail_count));

        $fclose(log_fd);
        $finish;
    end

endmodule
