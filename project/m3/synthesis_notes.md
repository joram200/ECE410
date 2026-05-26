# Synthesis Notes — Milestone 3: Option B Kalman Update Accelerator

## What Was Synthesized

The entire Option B RTL hierarchy synthesized successfully through Vivado 2024.1 OOC
(out-of-context) mode targeting `xc7a100tcsg324-1` (Artix-7 100T, speed-grade -1).
The design reads from a single combined file `rtl/top.sv` containing six modules:
`f64_mul`, `f64_add`, `gemm_systolic`, `kalman_update`, `axilite_slave`, and the
integration top module `top`. No module was stubbed or omitted. The synthesis
command was `synth_design -top top -mode out_of_context -part xc7a100tcsg324-1`
with a 100 MHz target clock.

The OOC mode excludes I/O buffers (IBUF/OBUF), which is appropriate because
this design will eventually be integrated as a slave on the VeerWolf SoC AXI
interconnect rather than placed as a standalone top-level. All internal logic
including DSP48E1 multiplier chains, LUT-based adder trees, and FSM registers
was inferred correctly with no unresolved references.

One pre-simulation fix was required: the `rtl/top.sv` file and the module
definitions at the top of `tb/tb_top.sv` (specifically `clk_gen`) lacked a
`` `timescale `` directive. Vivado xsim requires all modules in a simulation to
carry a timescale when any module in the design has one. A single
`` `timescale 1ns/1ps `` was added at the top of each file to resolve the
elaboration error. Synthesis tools ignore this directive, so it has no effect
on OOC synthesis results.

## Timing Results

**WNS: -50.419 ns (timing constraints NOT met)**

The design fails timing significantly at 100 MHz. Key numbers from
`synth/timing_report.txt`:

| Metric | Value |
|--------|-------|
| Worst Negative Slack (WNS) | -50.419 ns |
| Total Negative Slack (TNS) | -28924.338 ns |
| Failing setup endpoints | 1085 of 16663 |
| Worst Hold Slack (WHS) | +0.256 ns (no hold violations) |
| Max achievable frequency | ~16.6 MHz (1000 / 60.38 ns) |

The critical path is the Newton-Raphson reciprocal update loop in `kalman_update`:
from register `u_core/nr_x_reg[61]` through 6 cascaded DSP48E1 tiles and 43
CARRY4 chains (92 logic levels total) to register `u_core/nr_x_reg[54]`. The
data-path delay is 60.379 ns (logic 31.743 ns + routing 28.636 ns). Full detail
and mitigation strategies are in `synth/critical_path.md`.

The root cause is that `f64_mul` is a purely combinational module with no
pipeline registers. The Newton-Raphson step chains two `f64_mul` and one `f64_add`
in a single clock cycle (`nr_x_new = nr_x * (2.0 - S * nr_x)`), which is
6x longer than the 10 ns budget. Reducing the clock to ~65 ns (15 MHz) would
achieve closure without RTL changes, but this is not useful for performance.
The correct fix for M4 is to add pipeline registers between the chained F64
arithmetic units in the NR datapath.

Hold slack is positive (WHS = +0.256 ns) — no hold violations anywhere.

## Area Results

From `synth/area_report.txt` (Artix-7 100T):

| Resource | Used | Available | Utilisation |
|---|---|---|---|
| Slice LUTs | 14,642 | 63,400 | 23.09% |
| Slice Registers (FFs) | 5,535 | 126,800 | 4.37% |
| DSP48E1 | 126 | 240 | 52.50% |
| F7 Muxes | 128 | 31,700 | 0.40% |
| F8 Muxes | 64 | 15,850 | 0.40% |
| Block RAM | 0 | 135 | 0.00% |

The 126 DSP48E1 tiles is notable — 52.5% of the available tiles on the Artix-7
100T. Each 53x53-bit mantissa multiply requires a multi-DSP cascade. With
approximately 15 `f64_mul` instances across the design (9 in `gemm_systolic`,
3 for K computation, 3 for X correction, 2 for Newton-Raphson, 1 for IKH
elements), and each requiring ~7–8 DSP tiles in cascade, this is expected.
A design targeting a larger device (e.g., Kintex-7 or UltraScale) would have
ample DSP resources. For the Artix-7 100T specifically, DSP utilisation is
not a blocker (52.5% leaves headroom), but it rules out adding a second
accelerator instance to the same device.

## Power Estimation

From `synth/power_report.txt` (at 12.5% default toggle rate):

| Metric | Value |
|---|---|
| Total on-chip power | 358 mW |
| Dynamic power | 273 mW |
| Device static (leakage) | 85 mW |
| Max ambient temperature | 83.4°C (junction 26.6°C) |

The 358 mW estimate is based on a 12.5% activity factor applied to all registers.
In reality, the Kalman core runs for approximately 15 cycles per invocation and
then sits idle. If the host CPU calls the accelerator at, say, 100 Hz, the active
fraction is ~15 cycles / (100 MHz / 100 Hz) = 1.5e-5. Scaled accordingly,
the actual dynamic power contribution from the accelerator logic is negligible
(<1 mW). The dominant term in practice would be the 85 mW device static, which
is independent of activity.

## Scope Decisions

**Chosen scope:** Option B (Kalman update accelerator) — OOC synthesis and
co-simulation in M3; full SoC integration in M4.

The M3 submission covers:
1. Behavioral co-simulation: full 15-iteration Kalman filter sequence verified
   against a software reference, with AXI4-Lite as the only interface path.
2. Vivado OOC synthesis: timing, area, and power reports for the `top` module.

**Deferred to M4:** SoC integration — connecting `top` as a slave on the
VeerWolf AXI interconnect, adding it to `project_1.xpr`, and running full
place-and-route. This will be completed in M4 once the timing violation in
the NR datapath is resolved and the address-map assignment at 0x80010000 to
0x80011000 is confirmed against the VeerWolf memory map.

**Why this scope still answers the M1 question:** The M1 profiling identified
3x3 F64 GEMM (wrapped as a Kalman filter update) as the dominant kernel at
1.38e-4 GFLOP/s on the bare-metal SweRV EL2. The OOC synthesis result gives the
resource cost, maximum operating frequency, and power of the accelerator, which
is sufficient to project the speedup ratio once the SoC integration is done.
The full throughput comparison (bare-metal vs. hardware-accelerated) will be
completed in M4.

## What Worked and What Did Not

**Worked:**
- All six RTL modules elaborate without errors in both xsim (simulation) and
  Vivado synthesis. Synthesis completed without errors in ~2 minutes.
- The AXI4-Lite register file correctly decodes all addresses and routes data
  to the Kalman core.
- The Newton-Raphson reciprocal converges to sufficient accuracy within 3
  iterations (verified by ULP comparator, tolerance <= 4 ULP, 135/135 elements
  passed, 0 failed across all 15 iterations).
- All AXI4-Lite protocol SVAs and FSM contract assertions pass throughout the
  15-iteration simulation.
- Simulation runtime: ~18.6 us simulated time; `sim/cosim_run.log` contains the
  unambiguous `SIMULATION RESULT: PASS` line.

**Known issues:**
- **Timing at 100 MHz:** WNS = -50.419 ns. The design requires a 65 ns clock
  period (15 MHz) to meet timing without RTL changes. For M4, pipeline registers
  will be added between the chained F64 arithmetic units in the NR datapath,
  which is expected to bring the design to closure at 100 MHz.
- **Timescale directives required by xsim:** Added `` `timescale 1ns/1ps `` to
  `rtl/top.sv` and to the top of `tb/tb_top.sv`. This is a simulation-only
  requirement; Vivado synthesis ignores timescale and the reports are unaffected.
- **P_out partial readback:** Only P_out[0:5] (6 of 9 covariance elements) are
  visible via AXI reads due to the 9-element C_REG window in `axilite_slave`.
  P_out[6:8] require a register map extension. For M3 verification scope (state
  convergence check), the first 6 elements confirm correctness.

## M4 Plan

1. **Fix timing:** Add one pipeline register between `u_nr_mul1` output and
   `u_nr_sub` input, and another between `u_nr_mul2` input and output in the
   Newton-Raphson datapath. Target: WNS >= 0 at 100 MHz.
2. **SoC integration:** Edit `axi_intercon.sv` to add `top` as slave S3 at
   0x80010000, run `run_soc_integration.tcl`.
3. **Driver:** Write bare-metal C to write z/x_in/P_in via MMIO, poll STAT,
   read back x_out/P_out, measure round-trip latency in SweRV cycles.
4. **Benchmark:** Compute GFLOP/s for the hardware-accelerated Kalman path and
   compare to the M1 bare-metal baseline of 1.38e-4 GFLOP/s.
