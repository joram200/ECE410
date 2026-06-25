// checker.sv — F64 ULP checker + compute-core SVA module
// Two layers:
//   1. module compute_core_checker: 7 concurrent SVAs on FSM contracts
//   2. module result_checker: functional ULP comparator (triggered by check_en)
// Note: xsim does not support the SV 'checker' construct; SVAs are placed in
// a plain module with explicit @(posedge clk) clocking on each property.

// ============================================================================
// module compute_core_checker — SVA assertions on core FSM contracts
// ============================================================================
module compute_core_checker (
    input logic clk,
    input logic core_start,
    input logic core_busy,
    input logic core_done,
    input logic core_rst_n
);

    // 1. start must not assert while busy
    property p_no_start_while_busy;
        @(posedge clk) disable iff (!core_rst_n)
        !(core_start && core_busy);
    endproperty
    assert property (p_no_start_while_busy)
        else $error("CHECKER: start asserted while core is busy");

    // 2. busy must rise within one cycle of start
    property p_busy_follows_start;
        @(posedge clk) disable iff (!core_rst_n)
        core_start |=> core_busy;
    endproperty
    assert property (p_busy_follows_start)
        else $error("CHECKER: busy did not assert the cycle after start");

    // 3. busy must hold HIGH for at least 3 cycles (minimum GEMM latency)
    property p_busy_min_duration;
        @(posedge clk) disable iff (!core_rst_n)
        $rose(core_busy) |-> core_busy [*3];
    endproperty
    assert property (p_busy_min_duration)
        else $error("CHECKER: busy deasserted in fewer than 3 cycles (pipeline underrun)");

    // 4. done must not assert without busy having been HIGH (no phantom done)
    property p_done_requires_busy;
        @(posedge clk) disable iff (!core_rst_n)
        $rose(core_done) |-> $past(core_busy, 1);
    endproperty
    assert property (p_done_requires_busy)
        else $error("CHECKER: done rose without a preceding busy cycle");

    // 5. busy and done are mutually exclusive
    property p_busy_done_mutex;
        @(posedge clk) disable iff (!core_rst_n)
        !(core_busy && core_done);
    endproperty
    assert property (p_busy_done_mutex)
        else $error("CHECKER: busy and done asserted simultaneously");

    // 6. After done pulses, busy must be LOW
    property p_idle_after_done;
        @(posedge clk) disable iff (!core_rst_n)
        $rose(core_done) |=> !core_busy;
    endproperty
    assert property (p_idle_after_done)
        else $error("CHECKER: core still busy after done pulse");

    // 7. done is a single-cycle pulse
    property p_done_one_cycle;
        @(posedge clk) disable iff (!core_rst_n)
        $rose(core_done) |=> !core_done;
    endproperty
    assert property (p_done_one_cycle)
        else $error("CHECKER: done held HIGH for more than one cycle");

    // Cover: full start → busy → done sequence
    cover property (@(posedge clk) disable iff (!core_rst_n)
        core_start ##1 core_busy [*1:$] ##1 core_done)
        $display("CHECKER cover: full compute cycle observed");

endmodule : compute_core_checker

// ============================================================================
// module result_checker — ULP comparator
// ('checker' is a SV-2012 reserved keyword; use result_checker as the module name)
// ============================================================================
module result_checker #(
    parameter real ULP_TOLERANCE = 1.0
)(
    input logic        clk,
    input logic        check_en,       // one-cycle pulse after done
    input logic [63:0] dut_C   [0:8],
    input logic [63:0] ref_C   [0:8],
    // Core signals forwarded to checker block
    input logic        core_start,
    input logic        core_busy,
    input logic        core_done,
    input logic        core_rst_n
);

    // Instantiate checker block
    compute_core_checker u_core_chk (
        .clk        (clk),
        .core_start (core_start),
        .core_busy  (core_busy),
        .core_done  (core_done),
        .core_rst_n (core_rst_n)
    );

    // ULP distance: treats F64 as unsigned 64-bit integer.
    // For same-sign normals: |dut - ref| gives ULP distance directly.
    // For opposite-sign or sign-magnitude edge cases: sum magnitudes.
    function automatic logic [63:0] ulp_dist(
        input logic [63:0] x, y
    );
        logic [63:0] ax, ay;
        ax = {1'b0, x[62:0]};  // magnitude (abs)
        ay = {1'b0, y[62:0]};
        if (x[63] == y[63]) begin
            // Same sign: ULP = |raw_x - raw_y|
            ulp_dist = (ax >= ay) ? (ax - ay) : (ay - ax);
        end else begin
            // Opposite signs: ULP = ax + ay (worst case)
            ulp_dist = ax + ay;
        end
    endfunction

    int unsigned pass_count = 0, fail_count = 0;

    always @(posedge clk) begin
        if (check_en) begin
            for (int i = 0; i < 9; i++) begin
                automatic logic [63:0] ulp_d = ulp_dist(dut_C[i], ref_C[i]);
                if (ulp_d > $realtobits(ULP_TOLERANCE)) begin
                    $error("CHECKER: C[%0d] ULP error=%0d  dut=%h  ref=%h",
                           i, ulp_d, dut_C[i], ref_C[i]);
                    fail_count++;
                end else begin
                    pass_count++;
                end
            end
        end
    end

    final begin
        $display("CHECKER summary: %0d elements passed, %0d failed",
                 pass_count, fail_count);
        if (fail_count > 0) $error("CHECKER: %0d ULP failures detected", fail_count);
    end

endmodule : result_checker
