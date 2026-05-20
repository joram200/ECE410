`timescale 1ns/1ps
// =============================================================================
// Module:      crossbar_buffer
// Description: Single crosspoint element for a binary-weight crossbar.
//              Passes or inverts its 8-bit signed input based on the stored
//              weight.  weight = +1 when inv = 0, weight = -1 when inv = 1.
//
// -----------------------------------------------------------------------------
// Port List
// -----------------------------------------------------------------------------
//   Name   Dir   Width   Purpose
//   -----  ----  ------  ------------------------------------------------------
//   in     in    8       Signed activation input.
//   inv    in    1       Active-high invert: 0 -> pass (+1), 1 -> negate (-1).
//   out    out   8       Signed weighted output: inv ? -in : in.
// =============================================================================

module crossbar_buffer (
    input  logic signed [7:0] in,
    input  logic              inv,
    output logic signed [7:0] out
);

    assign out = inv ? -in : in;

endmodule

// =============================================================================
// Module:      crossbar_mac
// Description: 4x4 binary-weight crossbar MAC unit.
//              Computes out[j] = SUM_i( weight[i][j] * in[i] ) each clock
//              cycle, where each weight is +1 or -1.  Each crosspoint is
//              implemented with a crossbar_buffer instance whose inv port is
//              asserted when the stored weight equals -1.
//
// Arithmetic:  8-bit signed inputs; 8-bit signed outputs (truncated sum).
//
// Weights:     4x4 register array, one sign bit per crosspoint.  Written via
//              a single-entry port (we / w_row / w_col / w_val).
//              w_val = 0 encodes +1, w_val = 1 encodes -1.
//              Default after reset: all weights = +1 (sign = 0).
//
// Latency:     1 clock cycle (combinatorial crossbar + output register).
//
// -----------------------------------------------------------------------------
// Clock Domain
// -----------------------------------------------------------------------------
//   Single clock domain: clk.  No clock-domain crossings inside this module.
//
// -----------------------------------------------------------------------------
// Reset
// -----------------------------------------------------------------------------
//   Reset type:   Synchronous, active-HIGH (rst).
//   Behavior:     On the rising edge of clk while rst = 1, all weight
//                 registers set to +1 (2'sb01) and all output registers
//                 clear to 0.
//
// -----------------------------------------------------------------------------
// Port List
// -----------------------------------------------------------------------------
//   Name    Dir   Width   Purpose
//   ------  ----  ------  -----------------------------------------------------
//   clk     in    1       System clock.  All registers sample on rising edge.
//   rst     in    1       Synchronous active-HIGH reset.
//   in      in    8x4     Signed activation inputs in[0..3].
//   out     out   8x4     Signed accumulator outputs out[0..3] (truncated).
//   we      in    1       Weight write enable (active-HIGH, one cycle pulse).
//   w_row   in    2       Row index of weight to write (selects input line).
//   w_col   in    2       Column index of weight to write (selects output line).
//   w_val   in    1       Sign of weight: 0 = +1, 1 = -1.  Stored directly
//                         and wired to the buffer's inv port.
// =============================================================================

module crossbar_mac (
    input  logic              clk,
    input  logic              rst,

    input  logic signed [7:0] in  [3:0],
    output logic signed [7:0] out [3:0],

    // Weight programming port
    input  logic              we,
    input  logic [1:0]        w_row,
    input  logic [1:0]        w_col,
    input  logic              w_val   // sign bit: 0 = +1, 1 = -1
);

    // -------------------------------------------------------------------------
    // Weight register array: weight[row][col] stores the sign bit of ±1.
    //     0 -> buffer passes  in[row]  (weight = +1)
    //     1 -> buffer negates in[row]  (weight = -1)
    // -------------------------------------------------------------------------
    logic weight [3:0][3:0];

    always_ff @(posedge clk) begin
        if (rst) begin
            for (int r = 0; r < 4; r++)
                for (int c = 0; c < 4; c++)
                    weight[r][c] <= 1'b0;   // +1
        end else if (we) begin
            weight[w_row][w_col] <= w_val;
        end
    end

    // -------------------------------------------------------------------------
    // Crossbar: 4x4 crossbar_buffer instances.
    //   xp_out[i][j] = weight[i][j] * in[i]  (either +in[i] or -in[i])
    //   inv is the sign bit of the stored weight (1 when weight = -1).
    // -------------------------------------------------------------------------
    logic signed [7:0] xp_out [3:0][3:0];

    genvar i, j;
    generate
        for (i = 0; i < 4; i++) begin : gen_row
            for (j = 0; j < 4; j++) begin : gen_col
                crossbar_buffer u_buf (
                    .in  (in[i]),
                    .inv (weight[i][j]),
                    .out (xp_out[i][j])
                );
            end
        end
    endgenerate

    // -------------------------------------------------------------------------
    // Column accumulation and output register.
    //   out[j] = xp_out[0][j] + xp_out[1][j] + xp_out[2][j] + xp_out[3][j]
    //   Result is truncated to 8 bits on assignment.
    // -------------------------------------------------------------------------
    always_ff @(posedge clk) begin
        if (rst) begin
            for (int jj = 0; jj < 4; jj++)
                out[jj] <= '0;
        end else begin
            for (int jj = 0; jj < 4; jj++) begin
                out[jj] <= 8'(signed'(xp_out[0][jj])
                             + signed'(xp_out[1][jj])
                             + signed'(xp_out[2][jj])
                             + signed'(xp_out[3][jj]));
            end
        end
    end

endmodule
