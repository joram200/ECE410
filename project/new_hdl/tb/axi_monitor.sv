// axi_monitor.sv — Passive AXI4-Lite protocol monitor with SVAs
// Observe the bus between BFM (master) and DUT (slave).
// All assertions are concurrent; no driving of signals.

module axi_monitor (
    input logic        clk,
    input logic        rst_n,
    // AXI4-Lite signals (passive observation)
    input logic [31:0] s_awaddr,
    input logic        s_awvalid,
    input logic        s_awready,
    input logic [63:0] s_wdata,
    input logic [7:0]  s_wstrb,
    input logic        s_wvalid,
    input logic        s_wready,
    input logic [1:0]  s_bresp,
    input logic        s_bvalid,
    input logic        s_bready,
    input logic [31:0] s_araddr,
    input logic        s_arvalid,
    input logic        s_arready,
    input logic [63:0] s_rdata,
    input logic [1:0]  s_rresp,
    input logic        s_rvalid,
    input logic        s_rready,
    // Core signals (for compute-core–level checks)
    input logic [63:0] core_C [0:8],
    input logic        core_done,
    input logic        core_busy
);

    // 1. AWVALID must not deassert before AWREADY
    property p_awvalid_stable;
        @(posedge clk) disable iff (!rst_n)
        (s_awvalid && !s_awready) |=> s_awvalid;
    endproperty
    assert property (p_awvalid_stable)
        else $error("AXI MONITOR: AWVALID withdrew before AWREADY");

    // 2. WVALID must not deassert before WREADY
    property p_wvalid_stable;
        @(posedge clk) disable iff (!rst_n)
        (s_wvalid && !s_wready) |=> s_wvalid;
    endproperty
    assert property (p_wvalid_stable)
        else $error("AXI MONITOR: WVALID withdrew before WREADY");

    // 3. ARVALID must not deassert before ARREADY
    property p_arvalid_stable;
        @(posedge clk) disable iff (!rst_n)
        (s_arvalid && !s_arready) |=> s_arvalid;
    endproperty
    assert property (p_arvalid_stable)
        else $error("AXI MONITOR: ARVALID withdrew before ARREADY");

    // 4. BRESP must be OKAY (2'b00) on all accepted write responses
    property p_bresp_okay;
        @(posedge clk) disable iff (!rst_n)
        (s_bvalid && s_bready) |-> (s_bresp == 2'b00);
    endproperty
    assert property (p_bresp_okay)
        else $error("AXI MONITOR: Write response non-OKAY");

    // 5. RRESP must be OKAY (2'b00) on all accepted read data beats
    property p_rresp_okay;
        @(posedge clk) disable iff (!rst_n)
        (s_rvalid && s_rready) |-> (s_rresp == 2'b00);
    endproperty
    assert property (p_rresp_okay)
        else $error("AXI MONITOR: Read response non-OKAY");

    // 6. core_done must be a single-cycle pulse
    property p_done_pulse;
        @(posedge clk) disable iff (!rst_n)
        $rose(core_done) |=> !core_done;
    endproperty
    assert property (p_done_pulse)
        else $error("AXI MONITOR: core_done held HIGH for more than one cycle");

    // 7. core_C must be stable when core is idle (not busy, not done)
    property p_c_stable;
        @(posedge clk) disable iff (!rst_n)
        (!core_busy && !core_done) |=> $stable(core_C);
    endproperty
    assert property (p_c_stable)
        else $error("AXI MONITOR: core_C changed while core is idle");

    // Cover groups — AXI transaction targets
    covergroup axi_write_targets @(posedge clk);
        cp_ctrl:  coverpoint s_awaddr[7:3] iff (s_awvalid && s_awready) {
            bins ctrl    = {5'd0};
            bins a_reg_0 = {5'd2};
            bins a_reg_8 = {5'd10};
            bins b_reg_0 = {5'd11};
            bins b_reg_8 = {5'd19};
        }
    endgroup

    covergroup axi_read_targets @(posedge clk);
        cp_stat:  coverpoint s_araddr[7:3] iff (s_arvalid && s_arready) {
            bins stat    = {5'd1};
            bins c_reg_0 = {5'd20};
            bins c_reg_8 = {5'd28};
        }
    endgroup

    axi_write_targets cg_wr = new();
    axi_read_targets  cg_rd = new();

endmodule
