// tb_option_b.sv — Top-level testbench for Option B (accel_top_b)
// Same structure as tb_option_a; instantiates accel_top_b instead.
// Input mapping: A_REG[0]=z (from B_pairs[0][0] as proxy scalar),
//                A_REG[1:3]=x_in (from A_pairs column),
//                B_REG[0:8]=P_in (from B_pairs).
// Reference computed by software Kalman update (H=[1,0,0], R=5.0).

`timescale 1ns/1ps

module tb_option_b;

    // Clock and reset
    logic clk, rst_n;

    clk_gen #(.CLK_PERIOD_NS(10.0)) u_clk (.clk(clk));

    initial begin
        rst_n = 1'b0;
        repeat (5) @(posedge clk);
        rst_n = 1'b1;
    end

    // AXI4-Lite signals
    logic [31:0] m_awaddr;
    logic        m_awvalid, m_awready;
    logic [63:0] m_wdata;
    logic [7:0]  m_wstrb;
    logic        m_wvalid,  m_wready;
    logic [1:0]  m_bresp;
    logic        m_bvalid,  m_bready;
    logic [31:0] m_araddr;
    logic        m_arvalid, m_arready;
    logic [63:0] m_rdata;
    logic [1:0]  m_rresp;
    logic        m_rvalid,  m_rready;

    // BFM
    veerwolf_bfm u_bfm (
        .clk       (clk),
        .rst_n     (rst_n),
        .m_awaddr  (m_awaddr),  .m_awvalid (m_awvalid), .m_awready (m_awready),
        .m_wdata   (m_wdata),   .m_wstrb   (m_wstrb),
        .m_wvalid  (m_wvalid),  .m_wready  (m_wready),
        .m_bresp   (m_bresp),   .m_bvalid  (m_bvalid),  .m_bready  (m_bready),
        .m_araddr  (m_araddr),  .m_arvalid (m_arvalid), .m_arready (m_arready),
        .m_rdata   (m_rdata),   .m_rresp   (m_rresp),
        .m_rvalid  (m_rvalid),  .m_rready  (m_rready)
    );

    // DUT: Option B top
    accel_top_b #(.ADDR_WIDTH(32), .DATA_WIDTH(64)) u_dut (
        .clk       (clk),
        .rst_n     (rst_n),
        .s_awaddr  (m_awaddr),  .s_awvalid (m_awvalid), .s_awready (m_awready),
        .s_wdata   (m_wdata),   .s_wstrb   (m_wstrb),
        .s_wvalid  (m_wvalid),  .s_wready  (m_wready),
        .s_bresp   (m_bresp),   .s_bvalid  (m_bvalid),  .s_bready  (m_bready),
        .s_araddr  (m_araddr),  .s_arvalid (m_arvalid), .s_arready (m_arready),
        .s_rdata   (m_rdata),   .s_rresp   (m_rresp),
        .s_rvalid  (m_rvalid),  .s_rready  (m_rready)
    );

    // Hierarchical references
    wire        core_start = u_dut.core_start;
    wire        core_busy  = u_dut.core_busy;
    wire        core_done  = u_dut.core_done;
    wire        core_rst_n = u_dut.core_rst_n;
    wire [63:0] core_C [0:8];
    genvar gi;
    generate
        for (gi = 0; gi < 9; gi++) begin : gen_c_tap
            assign core_C[gi] = u_dut.slave_C[gi];
        end
    endgenerate

    // AXI monitor
    axi_monitor u_mon (
        .clk       (clk),
        .rst_n     (rst_n),
        .s_awaddr  (m_awaddr),  .s_awvalid (m_awvalid), .s_awready (m_awready),
        .s_wdata   (m_wdata),   .s_wstrb   (m_wstrb),
        .s_wvalid  (m_wvalid),  .s_wready  (m_wready),
        .s_bresp   (m_bresp),   .s_bvalid  (m_bvalid),  .s_bready  (m_bready),
        .s_araddr  (m_araddr),  .s_arvalid (m_arvalid), .s_arready (m_arready),
        .s_rdata   (m_rdata),   .s_rresp   (m_rresp),
        .s_rvalid  (m_rvalid),  .s_rready  (m_rready),
        .core_C    (core_C),
        .core_done (core_done),
        .core_busy (core_busy)
    );

    // Program block
    logic [63:0] A_pairs [0:14][0:8];
    logic [63:0] B_pairs [0:14][0:8];

    program_block u_prog (
        .A_pairs (A_pairs),
        .B_pairs (B_pairs)
    );

    // Checker
    logic        check_en;
    logic [63:0] dut_C [0:8];
    logic [63:0] ref_C [0:8];

    result_checker #(.ULP_TOLERANCE(4.0)) u_chk (  // looser tolerance for Kalman NR approximation
        .clk        (clk),
        .check_en   (check_en),
        .dut_C      (dut_C),
        .ref_C      (ref_C),
        .core_start (core_start),
        .core_busy  (core_busy),
        .core_done  (core_done),
        .core_rst_n (core_rst_n)
    );

    // Software reference Kalman update
    // H=[1,0,0], R=5.0; x_in from A_pairs col, P from B_pairs, z=0.5 constant
    localparam real R_REF  = 5.0;
    localparam real Z_MEAS = 0.5;

    function automatic void kalman_ref(
        input  logic [63:0] x_in  [0:2],
        input  logic [63:0] P_in  [0:8],
        output logic [63:0] x_out [0:2],
        output logic [63:0] C_out [0:8]   // pack x_out[0:2] + P_out[0:5] into C_out[0:8]
    );
        real x[3], P[9], K[3], x_new[3], P_new[9];
        real y_tilde, S, S_inv;
        real P_row0[3];

        for (int i = 0; i < 3; i++) x[i] = $bitstoreal(x_in[i]);
        for (int i = 0; i < 9; i++) P[i] = $bitstoreal(P_in[i]);

        // Innovation
        y_tilde = Z_MEAS - x[0];
        S = P[0] + R_REF;
        S_inv = 1.0 / S;

        // Kalman gain K = P[:,0] * S_inv
        for (int i = 0; i < 3; i++) K[i] = P[i*3] * S_inv;

        // State correction
        for (int i = 0; i < 3; i++) x_new[i] = x[i] + K[i] * y_tilde;

        // Covariance update P_new = (I - K*H) * P; H=[1,0,0]
        // (I - K*H)[i,k] = delta(i,k) - K[i]*H[k] = delta(i,k) - K[i]*delta(k,0)
        // P_new[i,j] = sum_k (I-K*H)[i,k] * P[k,j]
        for (int i = 0; i < 3; i++) begin
            for (int j = 0; j < 3; j++) begin
                P_new[i*3+j] = 0.0;
                for (int k = 0; k < 3; k++) begin
                    real ikH_ik;
                    ikH_ik = ((i == k) ? 1.0 : 0.0) - K[i] * (k == 0 ? 1.0 : 0.0);
                    P_new[i*3+j] = P_new[i*3+j] + ikH_ik * P[k*3+j];
                end
            end
        end

        // Pack into output: x_out
        for (int i = 0; i < 3; i++) x_out[i] = $realtobits(x_new[i]);

        // Pack into C_out for checker comparison (x_new[0:2] at [0:2], P_new[0:5] at [3:8])
        for (int i = 0; i < 3; i++) C_out[i]   = $realtobits(x_new[i]);
        for (int i = 0; i < 6; i++) C_out[3+i] = $realtobits(P_new[i]);
    endfunction

    // Main test sequence
    // Variable declarations must be at initial-block scope, not inside for-loop body
    logic [63:0] x_iter    [0:2];
    logic [63:0] A_in      [0:8];
    logic [63:0] x_out_ref [0:2];

    initial begin
        check_en = 1'b0;
        // Initial state x0 = [0, 0, 0]
        for (int i = 0; i < 3; i++) x_iter[i] = 64'h0;

        wait (rst_n === 1'b1);
        repeat (3) @(posedge clk);

        for (int iter = 0; iter < 15; iter++) begin
            $display("TB_B: Starting iteration %0d", iter);

            // Write z into A_REG[0], x_in into A_REG[1:3], P_in into B_REG[0:8]

            A_in[0] = $realtobits(Z_MEAS);  // z measurement
            for (int i = 0; i < 3; i++) A_in[1+i] = x_iter[i];
            for (int i = 4; i < 9; i++) A_in[i] = 64'h0;  // unused A slots

            u_bfm.write_matrix_A(A_in);
            u_bfm.write_matrix_B(B_pairs[iter]);  // P_in

            u_bfm.fire_and_wait();
            u_bfm.read_matrix_C(dut_C);

            // Compute reference
            kalman_ref(x_iter, B_pairs[iter], x_out_ref, ref_C);

            // Update x for next iteration
            for (int i = 0; i < 3; i++) x_iter[i] = x_out_ref[i];

            // Trigger checker
            @(posedge clk);
            check_en = 1'b1;
            @(posedge clk);
            check_en = 1'b0;

            $display("TB_B: Iteration %0d complete", iter);
        end

        repeat (10) @(posedge clk);
        $display("TB_B: All 15 iterations complete");
        $finish;
    end

    // Timeout
    initial begin
        #2000000;
        $fatal(1, "TB_B: Simulation timeout");
    end

endmodule
