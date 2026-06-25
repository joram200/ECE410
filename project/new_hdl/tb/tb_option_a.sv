// tb_option_a.sv — Top-level testbench for Option A (accel_top_a)
// Instantiates: clk_gen, veerwolf_bfm, accel_top_a, axi_monitor, checker, program_block
// Runs 15 GEMM iterations from program_block; compares each result with $bitstoreal reference.

`timescale 1ns/1ps

module tb_option_a;

    // Clock and reset
    logic clk, rst_n;

    clk_gen #(.CLK_PERIOD_NS(10.0)) u_clk (.clk(clk));

    initial begin
        rst_n = 1'b0;
        repeat (5) @(posedge clk);
        rst_n = 1'b1;
    end

    // AXI4-Lite signals (64-bit data, 32-bit address)
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

    // BFM instance
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

    // DUT: Option A top
    accel_top_a #(.ADDR_WIDTH(32), .DATA_WIDTH(64)) u_dut (
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

    // Hierarchical references to internal core signals
    wire        core_start = u_dut.core_start;
    wire        core_busy  = u_dut.core_busy;
    wire        core_done  = u_dut.core_done;
    wire        core_rst_n = u_dut.core_rst_n;
    wire [63:0] core_C [0:8];
    genvar gi;
    generate
        for (gi = 0; gi < 9; gi++) begin : gen_c_tap
            assign core_C[gi] = u_dut.core_C[gi];
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

    // Program block (matrix data)
    logic [63:0] A_pairs [0:14][0:8];
    logic [63:0] B_pairs [0:14][0:8];

    program_block u_prog (
        .A_pairs (A_pairs),
        .B_pairs (B_pairs)
    );

    // Checker signals
    logic        check_en;
    logic [63:0] dut_C [0:8];
    logic [63:0] ref_C [0:8];

    result_checker #(.ULP_TOLERANCE(1.0)) u_chk (
        .clk        (clk),
        .check_en   (check_en),
        .dut_C      (dut_C),
        .ref_C      (ref_C),
        .core_start (core_start),
        .core_busy  (core_busy),
        .core_done  (core_done),
        .core_rst_n (core_rst_n)
    );

    // -----------------------------------------------------------------------
    // Software reference: C_ref[i][j] = sum_k A[i*3+k] * B[k*3+j]
    // Uses $bitstoreal/$realtobits for F64 arithmetic in simulation.
    // -----------------------------------------------------------------------
    function automatic void compute_ref_gemm(
        input  logic [63:0] A [0:8],
        input  logic [63:0] B [0:8],
        output logic [63:0] C [0:8]
    );
        real ra [0:8], rb [0:8], rc [0:8];
        for (int i = 0; i < 9; i++) begin
            ra[i] = $bitstoreal(A[i]);
            rb[i] = $bitstoreal(B[i]);
        end
        for (int i = 0; i < 3; i++) begin
            for (int j = 0; j < 3; j++) begin
                rc[i*3+j] = 0.0;
                for (int k = 0; k < 3; k++) begin
                    rc[i*3+j] = rc[i*3+j] + ra[i*3+k] * rb[k*3+j];
                end
                C[i*3+j] = $realtobits(rc[i*3+j]);
            end
        end
    endfunction

    // -----------------------------------------------------------------------
    // Main test sequence
    // -----------------------------------------------------------------------
    initial begin
        check_en = 1'b0;
        for (int i = 0; i < 9; i++) begin
            dut_C[i] = 64'h0;
            ref_C[i] = 64'h0;
        end

        // Wait for reset to release
        wait (rst_n === 1'b1);
        repeat (3) @(posedge clk);

        for (int iter = 0; iter < 15; iter++) begin
            $display("TB_A: Starting iteration %0d", iter);

            // Write matrices
            u_bfm.write_matrix_A(A_pairs[iter]);
            u_bfm.write_matrix_B(B_pairs[iter]);

            // Fire compute and wait for done
            u_bfm.fire_and_wait();

            // Read result
            u_bfm.read_matrix_C(dut_C);

            // Compute software reference
            compute_ref_gemm(A_pairs[iter], B_pairs[iter], ref_C);

            // Trigger checker for one cycle
            @(posedge clk);
            check_en = 1'b1;
            @(posedge clk);
            check_en = 1'b0;

            $display("TB_A: Iteration %0d complete", iter);
        end

        repeat (10) @(posedge clk);
        $display("TB_A: All 15 iterations complete");
        $finish;
    end

    // Timeout watchdog
    initial begin
        #500000;
        $fatal(1, "TB_A: Simulation timeout — hung in BFM or DUT");
    end

endmodule
