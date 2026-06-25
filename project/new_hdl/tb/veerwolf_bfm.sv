// veerwolf_bfm.sv — AXI4-Lite master BFM (64-bit data width)
// Simulates the SweRV EL2 / VeerWolf CPU AXI master issuing transactions
// to the accelerator slave. All tasks are automatic (re-entrant safe).

module veerwolf_bfm (
    input  logic        clk,
    input  logic        rst_n,
    // AXI4-Lite master port — 64-bit data, 32-bit address
    output logic [31:0] m_awaddr,
    output logic        m_awvalid,
    input  logic        m_awready,
    output logic [63:0] m_wdata,
    output logic [7:0]  m_wstrb,
    output logic        m_wvalid,
    input  logic        m_wready,
    input  logic [1:0]  m_bresp,
    input  logic        m_bvalid,
    output logic        m_bready,
    output logic [31:0] m_araddr,
    output logic        m_arvalid,
    input  logic        m_arready,
    input  logic [63:0] m_rdata,
    input  logic [1:0]  m_rresp,
    input  logic        m_rvalid,
    output logic        m_rready
);

    // Default idle state
    initial begin
        m_awaddr  = 32'h0;
        m_awvalid = 1'b0;
        m_wdata   = 64'h0;
        m_wstrb   = 8'hFF;
        m_wvalid  = 1'b0;
        m_bready  = 1'b1;
        m_araddr  = 32'h0;
        m_arvalid = 1'b0;
        m_rready  = 1'b1;
    end

    // -----------------------------------------------------------------------
    // axi_write — issue one 64-bit write transaction
    // -----------------------------------------------------------------------
    task automatic axi_write(input logic [31:0] addr, input logic [63:0] data);
        // Drive AW and W simultaneously (single-beat, no ID)
        @(posedge clk);
        m_awaddr  <= addr;
        m_awvalid <= 1'b1;
        m_wdata   <= data;
        m_wstrb   <= 8'hFF;
        m_wvalid  <= 1'b1;

        // Wait for both AW and W to be accepted
        fork
            begin
                wait (m_awready);
                @(posedge clk);
                m_awvalid <= 1'b0;
            end
            begin
                wait (m_wready);
                @(posedge clk);
                m_wvalid <= 1'b0;
            end
        join

        // Wait for write response
        m_bready <= 1'b1;
        wait (m_bvalid);
        @(posedge clk);
    endtask

    // -----------------------------------------------------------------------
    // axi_read — issue one 64-bit read transaction
    // -----------------------------------------------------------------------
    task automatic axi_read(input logic [31:0] addr, output logic [63:0] data);
        @(posedge clk);
        m_araddr  <= addr;
        m_arvalid <= 1'b1;
        m_rready  <= 1'b1;

        wait (m_arready);
        @(posedge clk);
        m_arvalid <= 1'b0;

        wait (m_rvalid);
        data = m_rdata;
        @(posedge clk);
    endtask

    // -----------------------------------------------------------------------
    // Matrix write helpers — 9 × 64-bit beats per matrix
    // Base addresses match the register map (8-byte stride)
    //   A_REG base: 0x10
    //   B_REG base: 0x58
    // -----------------------------------------------------------------------
    task automatic write_matrix_A(input logic [63:0] A [0:8]);
        for (int i = 0; i < 9; i++) begin
            axi_write(32'h10 + (i * 8), A[i]);
        end
    endtask

    task automatic write_matrix_B(input logic [63:0] B [0:8]);
        for (int i = 0; i < 9; i++) begin
            axi_write(32'h58 + (i * 8), B[i]);
        end
    endtask

    // -----------------------------------------------------------------------
    // Matrix read helper — 9 × 64-bit beats
    //   C_REG base: 0xA0
    // -----------------------------------------------------------------------
    task automatic read_matrix_C(output logic [63:0] C [0:8]);
        for (int i = 0; i < 9; i++) begin
            axi_read(32'hA0 + (i * 8), C[i]);
        end
    endtask

    // -----------------------------------------------------------------------
    // fire_and_wait — write CTRL=1, poll STAT[0] until done
    // -----------------------------------------------------------------------
    task automatic fire_and_wait();
        logic [63:0] stat;
        // Write start bit
        axi_write(32'h00, 64'h0000_0000_0000_0001);
        // Poll STAT[1] (busy). Two-phase: wait for busy to assert then deassert.
        // This is more reliable than catching the 1-cycle done pulse (STAT[0]).
        stat = 64'h0;
        while (!stat[1]) axi_read(32'h08, stat);  // wait for busy
        while  (stat[1]) axi_read(32'h08, stat);  // wait for done (busy drops)
    endtask

endmodule
