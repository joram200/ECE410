`timescale 1ns/1ps
// =============================================================================
// Testbench : tb_interface
// File      : project/m2/tb/tb_interface.sv
//
// Tests three scenarios for pcie_tlp_ep (project/m2/rtl/interface.sv):
//
//   TEST 1 — MWr32 to CTRL (addr=0x00, data=0xDEADBEEF)
//     Full AXI4-Stream valid/ready handshake.  After the write completes,
//     dut.reg_ctrl is checked via hierarchical reference.
//
//   TEST 2 — MRd32 from CTRL (addr=0x00)
//     tx_tready held low so the DUT must assert tx_tvalid.  The full 128-bit
//     CplD response is compared against an independently constructed expected
//     value (§2.2.9 field layout).  tx_tlast also verified.
//
//   TEST 3 — MWr32 to MEAS (addr=0x08, data=0xCAFEBABE)
//     core_valid_in is verified high for exactly the WR_EXEC cycle and low
//     in the next (IDLE) cycle.  core_y is verified equal to the write data.
//
// Prints PASS or FAIL on stdout.
// =============================================================================

module tb_interface;

// ─── Clock ──────────────────────────────────────────────────────────────────
logic clk = 1'b0;
always #5 clk = ~clk;          // 100 MHz, 10 ns period

// ─── DUT signals ────────────────────────────────────────────────────────────
logic         rst_n;
logic [127:0] rx_tdata;
logic         rx_tvalid;
logic         rx_tready;
logic         rx_tlast;
logic [127:0] tx_tdata;
logic         tx_tvalid;
logic         tx_tready;
logic         tx_tlast;
logic         core_valid_in;
logic  [31:0] core_y;
logic         core_valid_out;
logic  [31:0] core_x_hat_0;
logic  [31:0] core_x_hat_1;
logic  [31:0] core_x_hat_2;

// ─── DUT ────────────────────────────────────────────────────────────────────
pcie_tlp_ep #(
    .COMPLETER_ID(16'h0008)
) dut (
    .clk           (clk),
    .rst_n         (rst_n),
    .rx_tdata      (rx_tdata),
    .rx_tvalid     (rx_tvalid),
    .rx_tready     (rx_tready),
    .rx_tlast      (rx_tlast),
    .tx_tdata      (tx_tdata),
    .tx_tvalid     (tx_tvalid),
    .tx_tready     (tx_tready),
    .tx_tlast      (tx_tlast),
    .core_valid_in (core_valid_in),
    .core_y        (core_y),
    .core_valid_out(core_valid_out),
    .core_x_hat_0  (core_x_hat_0),
    .core_x_hat_1  (core_x_hat_1),
    .core_x_hat_2  (core_x_hat_2)
);

// ─── TLP Constructors (§2.2.1, §2.2.7, §2.2.9) ─────────────────────────────

// MWr32: Fmt=010, Type=00000, 3DW header + 1DW data
function automatic logic [127:0] mwr32(
    input logic [31:0] addr,
    input logic [15:0] req_id,
    input logic  [7:0] tag,
    input logic [31:0] wdata
);
    return {
        3'b010,            // [127:125] Fmt = 3DW+data  (§2.2.1)
        5'b00000,          // [124:120] Type = Memory   (§2.2.7)
        1'b0, 3'b000,      // T9, TC
        1'b0, 1'b0, 1'b0, 1'b0,  // T8, Attr2, LN, TH
        1'b0, 1'b0,        // TD, EP
        2'b00, 2'b00,      // Attr[1:0], AT
        10'd1,             // [105:96]  Length = 1 DWORD
        req_id,            // [95:80]   Requester ID    (§2.2.7)
        tag,               // [79:72]   Tag
        4'b1111, 4'b1111,  // [71:64]   Last/First DW BE
        addr[31:2], 2'b00, // [63:32]   Address + PH
        wdata              // [31:0]    Write data
    };
endfunction

// MRd32: Fmt=000, Type=00000, 3DW header, no data
function automatic logic [127:0] mrd32(
    input logic [31:0] addr,
    input logic [15:0] req_id,
    input logic  [7:0] tag
);
    return {
        3'b000,
        5'b00000,
        1'b0, 3'b000,
        1'b0, 1'b0, 1'b0, 1'b0,
        1'b0, 1'b0,
        2'b00, 2'b00,
        10'd1,
        req_id,
        tag,
        4'b1111, 4'b1111,
        addr[31:2], 2'b00,
        32'h0              // [31:0] zero (no payload for read)
    };
endfunction

// Expected CplD: Fmt=010, Type=01010 (§2.2.9)
function automatic logic [127:0] make_cpld(
    input logic [15:0] req_id,
    input logic  [7:0] tag,
    input logic [31:0] addr,
    input logic [31:0] rd_data
);
    return {
        3'b010,            // [127:125] Fmt = 3DW+data
        5'b01010,          // [124:120] Type = CplD     (§2.2.9)
        1'b0, 3'b000,
        1'b0, 1'b0, 1'b0, 1'b0,
        1'b0, 1'b0,
        2'b00, 2'b00,
        10'd1,             // Length = 1 DWORD
        16'h0008,          // [95:80]   Completer ID    (§2.2.9)
        3'b000,            // [79:77]   Status = SC (Successful Completion)
        1'b0,              // [76]      BCM
        12'd4,             // [75:64]   Byte Count = 4
        req_id,            // [63:48]   Requester ID (echoed)
        tag,               // [47:40]   Tag (echoed)
        1'b0,              // [39]      Reserved
        addr[6:0],         // [38:32]   Lower Address
        rd_data            // [31:0]    Read data
    };
endfunction

// ─── Task: present one TLP beat with valid/ready handshake ───────────────────
// rx_tready is asserted combinatorially when the DUT is IDLE.
// We wait for a negedge where rx_tready=1, drive the beat, then deassert.
task automatic send_tlp(input logic [127:0] tlp);
    @(negedge clk);
    while (!rx_tready) @(negedge clk);
    rx_tdata  = tlp;
    rx_tvalid = 1'b1;
    rx_tlast  = 1'b1;
    @(posedge clk);        // rising edge: DUT captures TLP, transitions state
    @(negedge clk);        // deassert after handshake
    rx_tvalid = 1'b0;
    rx_tlast  = 1'b0;
    rx_tdata  = 128'h0;
    // Returns here with DUT one state past IDLE (WR_EXEC or TX_CPL)
endtask

// ─── Test-level variables ────────────────────────────────────────────────────
logic         all_pass;
logic [127:0] got_cpld;
logic [127:0] exp_cpld;

localparam logic [31:0] CTRL_WDATA  = 32'hDEAD_BEEF;
localparam logic [31:0] MEAS_WDATA  = 32'hCAFE_BABE;
localparam logic [15:0] REQ_ID      = 16'hABCD;
localparam logic  [7:0] TAG_WR_CTRL = 8'h01;
localparam logic  [7:0] TAG_RD_CTRL = 8'h02;
localparam logic  [7:0] TAG_WR_MEAS = 8'h03;

// ─── Main test sequence ──────────────────────────────────────────────────────
initial begin
    $dumpfile("../sim/tb_interface.vcd");
    $dumpvars(0, tb_interface);

    // Default signal values
    rx_tdata       = 128'h0;
    rx_tvalid      = 1'b0;
    rx_tlast       = 1'b0;
    tx_tready      = 1'b1;
    core_valid_out = 1'b0;
    core_x_hat_0   = 32'h0;
    core_x_hat_1   = 32'h0;
    core_x_hat_2   = 32'h0;
    all_pass       = 1'b1;

    // ── Asynchronous reset ────────────────────────────────────────────────
    rst_n = 1'b0;
    repeat(4) @(posedge clk);
    @(negedge clk);
    rst_n = 1'b1;
    @(posedge clk);

    // ════════════════════════════════════════════════════════════════════
    // TEST 1: MWr32 to CTRL (addr=0x00)
    //   Assert rx_tvalid when rx_tready=1 (IDLE state). After WR_EXEC
    //   completes, check reg_ctrl via hierarchical path.
    // ════════════════════════════════════════════════════════════════════
    $display("TEST 1: MWr32 to CTRL addr=0x00 data=0x%08X", CTRL_WDATA);

    send_tlp(mwr32(32'h0000_0000, REQ_ID, TAG_WR_CTRL, CTRL_WDATA));
    // send_tlp returns at negedge with state=WR_EXEC.
    // Next posedge: WR_EXEC commits reg_ctrl=c_wdata, state→IDLE.
    repeat(2) @(posedge clk);   // WR_EXEC + one spare cycle

    if (dut.reg_ctrl !== CTRL_WDATA) begin
        $display("  FAIL: reg_ctrl=0x%08X expected=0x%08X",
                 dut.reg_ctrl, CTRL_WDATA);
        all_pass = 1'b0;
    end else begin
        $display("  reg_ctrl=0x%08X  OK", dut.reg_ctrl);
    end

    // ════════════════════════════════════════════════════════════════════
    // TEST 2: MRd32 from CTRL (addr=0x00) → CplD response
    //   tx_tready=0 so the DUT must hold tx_tvalid=1 until accepted.
    //   The full 128-bit CplD is compared to an independently built
    //   expected value (§2.2.9 layout).
    // ════════════════════════════════════════════════════════════════════
    $display("TEST 2: MRd32 from CTRL addr=0x00 expect CplD data=0x%08X",
             CTRL_WDATA);

    tx_tready = 1'b0;                    // hold: forces DUT to assert valid
    send_tlp(mrd32(32'h0000_0000, REQ_ID, TAG_RD_CTRL));
    // send_tlp returns at negedge with state=TX_CPL.

    // TX_CPL fires on next posedge: tx_tdata=CplD, tx_tvalid=1, tx_tlast=1
    // (tx_tready=0, so valid is NOT overridden — it stays 1)
    @(posedge clk);
    @(negedge clk);   // sample in stable inter-clock region

    got_cpld = tx_tdata;
    exp_cpld = make_cpld(REQ_ID, TAG_RD_CTRL, 32'h0000_0000, CTRL_WDATA);

    if (!tx_tvalid) begin
        $display("  FAIL: tx_tvalid not asserted during TX_CPL");
        all_pass = 1'b0;
    end else if (!tx_tlast) begin
        $display("  FAIL: tx_tlast not asserted during TX_CPL");
        all_pass = 1'b0;
    end else if (got_cpld !== exp_cpld) begin
        $display("  FAIL: CplD mismatch");
        $display("    got=0x%032X", got_cpld);
        $display("    exp=0x%032X", exp_cpld);
        all_pass = 1'b0;
    end else begin
        $display("  CplD=0x%032X  OK", got_cpld);
    end

    // Accept the completion: assert tx_tready so DUT returns to IDLE
    @(negedge clk);
    tx_tready = 1'b1;
    repeat(2) @(posedge clk);   // TX_CPL completes + one spare cycle

    // ════════════════════════════════════════════════════════════════════
    // TEST 3: MWr32 to MEAS (addr=0x08)
    //   Verify core_valid_in pulses for exactly one WR_EXEC cycle.
    //   Verify core_y equals the written measurement data.
    // ════════════════════════════════════════════════════════════════════
    $display("TEST 3: MWr32 to MEAS addr=0x08 data=0x%08X", MEAS_WDATA);

    send_tlp(mwr32(32'h0000_0008, REQ_ID, TAG_WR_MEAS, MEAS_WDATA));
    // send_tlp returns at negedge with state=WR_EXEC.
    // Next posedge: WR_EXEC sets meas_pulse=1 → core_valid_in=1, state→IDLE.

    @(posedge clk);    // WR_EXEC cycle: meas_pulse registered high
    @(negedge clk);    // sample: core_valid_in should be 1

    if (!core_valid_in) begin
        $display("  FAIL: core_valid_in not pulsed after MEAS write");
        all_pass = 1'b0;
    end else begin
        $display("  core_valid_in=1  OK (WR_EXEC cycle)");
    end

    if (core_y !== MEAS_WDATA) begin
        $display("  FAIL: core_y=0x%08X expected=0x%08X", core_y, MEAS_WDATA);
        all_pass = 1'b0;
    end else begin
        $display("  core_y=0x%08X  OK", core_y);
    end

    @(posedge clk);    // IDLE cycle: default meas_pulse <= 0 fires
    @(negedge clk);    // sample: core_valid_in should be back to 0

    if (core_valid_in) begin
        $display("  FAIL: core_valid_in still high in IDLE (not a 1-cycle pulse)");
        all_pass = 1'b0;
    end else begin
        $display("  core_valid_in=0  OK (IDLE cycle)");
    end

    // ── Result ───────────────────────────────────────────────────────────
    repeat(2) @(posedge clk);
    if (all_pass)
        $display("PASS");
    else
        $display("FAIL");
    $finish;
end

// ─── Timeout watchdog ────────────────────────────────────────────────────────
initial begin
    #50000;
    $display("FAIL: simulation timeout");
    $finish;
end

endmodule
