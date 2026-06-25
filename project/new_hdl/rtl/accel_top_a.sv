// accel_top_a.sv — Option A synthesis top: axilite_slave + gemm_systolic
// DATA_WIDTH=64 matches VeerWolf SoC AXI interconnect natively.
// This is the synthesis top for OOC Run 1A and SoC Run 2.

module accel_top_a #(
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

    // Internal core wires
    logic        core_start, core_rst_n, core_done, core_busy;
    logic [63:0] core_A [0:8];
    logic [63:0] core_B [0:8];
    logic [63:0] core_C [0:8];

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
        .core_A     (core_A),
        .core_B     (core_B),
        .core_C     (core_C),
        .core_done  (core_done),
        .core_busy  (core_busy)
    );

    gemm_systolic u_core (
        .clk   (clk),
        .rst_n (core_rst_n),
        .start (core_start),
        .A     (core_A),
        .B     (core_B),
        .C     (core_C),
        .done  (core_done),
        .busy  (core_busy)
    );

endmodule
