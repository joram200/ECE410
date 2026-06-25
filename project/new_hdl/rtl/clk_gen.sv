// clk_gen.sv — Simulation-only clock generator. NOT synthesisable.
// Add to sim_1 fileset only; never to sources_1.

module clk_gen #(
    parameter real CLK_PERIOD_NS = 10.0   // 100 MHz default
)(
    output logic clk
);
    initial clk = 1'b0;
    always #(CLK_PERIOD_NS / 2.0) clk = ~clk;
endmodule
