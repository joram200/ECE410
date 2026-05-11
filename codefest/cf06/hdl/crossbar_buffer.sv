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
