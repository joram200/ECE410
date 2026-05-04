`timescale 1ns/1ps
// =============================================================================
// Module  : pcie_tlp_ep
// File    : project/m2/rtl/interface.sv
//
// Protocol: PCIe Gen4  (PCIe Base Specification Revision 4.0, June 2017)
//
// Specification References
// ------------------------
// §2.2.1  — Common TLP Header Fields (Fmt[2:0], Type[4:0], TC, Length[9:0])
// §2.2.7  — Memory Read (MRd32) and Memory Write (MWr32) Transactions
//            3DW header format, 32-bit address, DWORD payload
// §2.2.9  — Completion with Data (CplD): Completer ID, Status, Byte Count,
//            Lower Address, echoed Requester ID and Tag
// §6.2.3.1— BAR sizing: 32-bit non-prefetchable BAR0, 256-byte aperture
//
// Interface Summary
// -----------------
// Exposes a 128-bit AXI4-Stream TLP bus (one 128-bit beat per 3DW+1DW TLP).
// At PCIe Gen4 ×16 with 128b/130b encoding the raw bandwidth is
// 16 GT/s × 16 lanes × (128/130) / 8 ≈ 31.5 GB/s per direction, matching
// the 51.2 GB/s system-memory target cited in interface_selection.md.
//
// Supported TLP types
// -------------------
//   MWr32 (Fmt=010, Type=00000) — write one DWORD to BAR0 register map
//   MRd32 (Fmt=000, Type=00000) — read  one DWORD, reply with CplD
//   All other TLP types are silently discarded.
//
// Register Map  (BAR0, 32-bit DWORD registers, byte-addressed)
// -----------------------------------------------------------
//  Byte    DW     Name    Dir   Width  Description
//  Offset  Offset
//  0x00     0     CTRL    R/W   32     [0]=core_en (enable compute_core clocking)
//                                      [1]=soft_rst (synchronous rst to core, R/W)
//  0x04     1     STAT    RO    32     [0]=valid_out  (output registers are fresh)
//                                      [1]=busy       (update pipeline active)
//                                      [31:2]=reserved, read 0
//  0x08     2     MEAS    WO    32     Measurement y[31:0] in Q16.16 signed.
//                                      Writing asserts core_valid_in for 1 cycle.
//                                      Reading always returns 0x00000000 (RAZ).
//  0x0C     3     XHAT0   RO    32     Corrected position  x̂₀ (Q16.16, read-only)
//  0x10     4     XHAT1   RO    32     Corrected velocity  x̂₁ (Q16.16, read-only)
//  0x14     5     XHAT2   RO    32     Corrected acceleration x̂₂ (Q16.16, read-only)
//  0x18–0xFC  6–63  —     —     —     Reserved, RAZ/WI
//
// TLP Encoding on the 128-bit Bus  (§2.2.1, §2.2.7, §2.2.9)
// -----------------------------------------------------------
// All TLPs that fit in 4 DW (3DW header + 1DW data) are transferred in a
// single 128-bit beat.  DW0 occupies the most-significant 32 bits.
//
//  MWr32  (Fmt=010, Type=00000, 3DW header + data):
//   [127:125] Fmt[2:0]    = 3'b010
//   [124:120] Type[4:0]   = 5'b00000
//   [119]     T9          = 0
//   [118:116] TC[2:0]     = traffic class
//   [115]     T8          = 0
//   [114]     Attr[2]     = 0
//   [113]     LN          = 0
//   [112]     TH          = 0
//   [111]     TD          = 0  (no ECRC)
//   [110]     EP          = 0
//   [109:108] Attr[1:0]   = 0
//   [107:106] AT[1:0]     = 0
//   [105:96]  Length[9:0] = 10'd1  (one DWORD payload)
//   [95:80]   Requester ID (Bus[7:0], Dev[4:0], Fn[2:0])
//   [79:72]   Tag[7:0]
//   [71:68]   Last DW BE[3:0]
//   [67:64]   First DW BE[3:0]
//   [63:34]   Address[31:2]   (32-bit byte address, bits [1:0] always 0)
//   [33:32]   PH[1:0]         = 0
//   [31:0]    Payload (one DWORD write data)
//
//  MRd32  (Fmt=000, Type=00000, 3DW header, no data):
//   Same as MWr32 DW0-DW2; [31:0] is zero-padded and ignored.
//
//  CplD   (Fmt=010, Type=01010, 3DW header + data):
//   [127:125] Fmt[2:0]        = 3'b010
//   [124:120] Type[4:0]       = 5'b01010
//   [119:96]  (misc fields)   = TC=0, TD=0, EP=0, Attr=0, Length=10'd1
//   [95:80]   Completer ID    = COMPLETER_ID parameter
//   [79:77]   Cpl Status[2:0] = 3'b000  (Successful Completion)
//   [76]      BCM             = 0
//   [75:64]   Byte Count[11:0]= 12'd4
//   [63:48]   Requester ID    (echoed from MRd32)
//   [47:40]   Tag[7:0]        (echoed from MRd32)
//   [39]      Rsvd            = 0
//   [38:32]   Lower Addr[6:0] = addr[6:0] of the MRd32
//   [31:0]    Payload (one DWORD read data)
// =============================================================================

module pcie_tlp_ep #(
    // Completer ID presented in CplD TLPs (§2.2.9)
    // Default: Bus 0x00, Device 1, Function 0
    parameter logic [15:0] COMPLETER_ID = 16'h0008   // {Bus=0x00, Dev=1, Fn=0}
)(
    // ── System ───────────────────────────────────────────────────────────────
    input  logic         clk,
    input  logic         rst_n,          // Active-LOW asynchronous reset

    // ── RX TLP stream — AXI4-Stream sink (§2.2.1 bit packing above) ─────────
    input  logic [127:0] rx_tdata,
    input  logic         rx_tvalid,
    output logic         rx_tready,
    input  logic         rx_tlast,       // Always 1 for single-beat TLPs here

    // ── TX TLP stream — AXI4-Stream source ──────────────────────────────────
    output logic [127:0] tx_tdata,
    output logic         tx_tvalid,
    input  logic         tx_tready,
    output logic         tx_tlast,

    // ── Compute-core interface (matches compute_core port list) ──────────────
    output logic         core_valid_in,
    output logic  [31:0] core_y,
    input  logic         core_valid_out,
    input  logic  [31:0] core_x_hat_0,
    input  logic  [31:0] core_x_hat_1,
    input  logic  [31:0] core_x_hat_2
);

// ── TLP type constants  (§2.2.1) ────────────────────────────────────────────
localparam logic [2:0] FMT_3DW_NODATA = 3'b000;  // MRd32
localparam logic [2:0] FMT_3DW_DATA   = 3'b010;  // MWr32, CplD
localparam logic [4:0] TYPE_MEM       = 5'b00000; // Memory read/write
localparam logic [4:0] TYPE_CPLD      = 5'b01010; // Completion with Data

// ── Register file ────────────────────────────────────────────────────────────
logic [31:0] reg_ctrl;    // 0x00  R/W
logic [31:0] reg_xhat0;   // 0x0C  RO  latched from core on valid_out
logic [31:0] reg_xhat1;   // 0x10  RO
logic [31:0] reg_xhat2;   // 0x14  RO
logic        busy_r;      // tracks an in-progress pipeline update

// STAT is fully combinational; not stored
/* verilator lint_off UNUSEDSIGNAL */
wire [31:0] reg_stat = {30'b0, busy_r, core_valid_out};
/* verilator lint_on UNUSEDSIGNAL */

// ── Captured TLP fields (registered on IDLE→state transition) ────────────────
logic [2:0]  c_fmt;
logic [4:0]  c_type;
logic [15:0] c_req_id;
logic [7:0]  c_tag;
logic [31:0] c_addr;
logic [2:0]  c_dw_off;  // c_addr[4:2] → DW index 0–5 in BAR0
logic [31:0] c_wdata;   // payload for MWr32

// ── Register read mux (combinational, §2.2.7 read path) ─────────────────────
logic [31:0] rd_data;
always_comb begin
    unique case (c_dw_off)
        3'd0:    rd_data = reg_ctrl;
        3'd1:    rd_data = reg_stat;
        3'd2:    rd_data = 32'h0;      // MEAS is WO → RAZ
        3'd3:    rd_data = reg_xhat0;
        3'd4:    rd_data = reg_xhat1;
        3'd5:    rd_data = reg_xhat2;
        default: rd_data = 32'h0;      // reserved → RAZ
    endcase
end

// ── FSM ──────────────────────────────────────────────────────────────────────
typedef enum logic [1:0] {
    IDLE    = 2'd0,  // waiting for RX TLP
    WR_EXEC = 2'd1,  // execute register write, one cycle
    TX_CPL  = 2'd2   // transmit CplD, hold until tx_tready
} state_t;

state_t state;

// One-cycle pulse gating core_valid_in
logic meas_pulse;

// ── Main sequential logic ────────────────────────────────────────────────────
always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        state      <= IDLE;
        reg_ctrl   <= 32'h0;
        reg_xhat0  <= 32'h0;
        reg_xhat1  <= 32'h0;
        reg_xhat2  <= 32'h0;
        busy_r     <= 1'b0;
        c_fmt      <= 3'b0;
        c_type     <= 5'b0;
        c_req_id   <= 16'h0;
        c_tag      <= 8'h0;
        c_addr     <= 32'h0;
        c_dw_off   <= 3'h0;
        c_wdata    <= 32'h0;
        meas_pulse <= 1'b0;
        tx_tdata   <= 128'h0;
        tx_tvalid  <= 1'b0;
        tx_tlast   <= 1'b0;
    end else begin
        meas_pulse <= 1'b0;   // default: deassert every cycle

        // Latch core outputs the cycle valid_out pulses
        if (core_valid_out) begin
            reg_xhat0 <= core_x_hat_0;
            reg_xhat1 <= core_x_hat_1;
            reg_xhat2 <= core_x_hat_2;
            busy_r    <= 1'b0;
        end

        case (state)

            // ── IDLE: accept and decode one TLP beat ─────────────────────────
            // §2.2.1 — decode Fmt and Type from DW0 bits [127:120]
            IDLE: begin
                tx_tvalid <= 1'b0;
                if (rx_tvalid) begin
                    // Capture header fields from the 128-bit beat
                    c_fmt    <= rx_tdata[127:125];           // §2.2.1 Fmt
                    c_type   <= rx_tdata[124:120];           // §2.2.1 Type
                    c_req_id <= rx_tdata[95:80];             // §2.2.7 DW1 Requester ID
                    c_tag    <= rx_tdata[79:72];             // §2.2.7 DW1 Tag
                    c_addr   <= {rx_tdata[63:34], 2'b00};   // §2.2.7 DW2 Address[31:2]
                    c_dw_off <= rx_tdata[36:34];             // addr[4:2] → DW 0–5
                    c_wdata  <= rx_tdata[31:0];              // §2.2.7 DW3 payload

                    // Dispatch on TLP type (§2.2.7)
                    if      (rx_tdata[127:125] == FMT_3DW_DATA   &&
                             rx_tdata[124:120] == TYPE_MEM)
                        state <= WR_EXEC;
                    else if (rx_tdata[127:125] == FMT_3DW_NODATA &&
                             rx_tdata[124:120] == TYPE_MEM)
                        state <= TX_CPL;
                    // else: unsupported TLP type, stay IDLE (discard)
                end
            end

            // ── WR_EXEC: commit write to register file ────────────────────────
            // §2.2.7 — MWr32: update addressed register; RO registers silently
            // ignored; MEAS write additionally pulses core_valid_in.
            WR_EXEC: begin
                unique case (c_dw_off)
                    3'd0: reg_ctrl <= c_wdata;   // CTRL — R/W
                    3'd2: begin                   // MEAS — WO, triggers filter update
                        meas_pulse <= 1'b1;
                        busy_r     <= 1'b1;
                    end
                    default: ;                    // STAT/XHAT* are RO — silently ignore
                endcase
                state <= IDLE;
            end

            // ── TX_CPL: build and send Completion with Data (CplD, §2.2.9) ────
            // Header fields follow §2.2.9 Table 2-35.
            TX_CPL: begin
                tx_tdata <= {
                    //── DW0 ────────────────────────────────────────────────────
                    FMT_3DW_DATA,   // [127:125] Fmt  = 3'b010 (3DW with data)
                    TYPE_CPLD,      // [124:120] Type = 5'b01010 (CplD)
                    1'b0,           // [119]     T9
                    3'b000,         // [118:116] TC   (Traffic Class 0)
                    1'b0,           // [115]     T8
                    1'b0,           // [114]     Attr[2]
                    1'b0,           // [113]     LN
                    1'b0,           // [112]     TH
                    1'b0,           // [111]     TD   (no ECRC)
                    1'b0,           // [110]     EP   (not poisoned)
                    2'b00,          // [109:108] Attr[1:0]
                    2'b00,          // [107:106] AT
                    10'd1,          // [105:96]  Length = 1 DWORD
                    //── DW1 ────────────────────────────────────────────────────
                    COMPLETER_ID,   // [95:80]   Completer ID
                    3'b000,         // [79:77]   Completion Status = SC (success)
                    1'b0,           // [76]      BCM (Byte Count Modified = 0)
                    12'd4,          // [75:64]   Byte Count = 4 (one DWORD)
                    //── DW2 ────────────────────────────────────────────────────
                    c_req_id,       // [63:48]   Requester ID (echoed)
                    c_tag,          // [47:40]   Tag (echoed)
                    1'b0,           // [39]      Reserved
                    c_addr[6:0],    // [38:32]   Lower Address (byte addr[6:0])
                    //── DW3 ────────────────────────────────────────────────────
                    rd_data         // [31:0]    Read data from register file
                };
                tx_tvalid <= 1'b1;
                tx_tlast  <= 1'b1;

                // Hold until downstream accepts
                if (tx_tready) begin
                    tx_tvalid <= 1'b0;
                    state     <= IDLE;
                end
            end

            default: state <= IDLE;
        endcase
    end
end

// ── Combinational output assignments ─────────────────────────────────────────
// rx_tready: accept a new TLP only when the FSM is idle
assign rx_tready    = (state == IDLE);
// core_valid_in: one-cycle pulse generated in WR_EXEC when MEAS is written
assign core_valid_in = meas_pulse;
// core_y: captured MWr32 payload held until next measurement write
assign core_y        = c_wdata;

endmodule
