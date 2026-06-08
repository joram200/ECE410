# ECE 410 — Milestone 4: Option B Kalman Update Accelerator

## How to Reproduce

**Simulator:** Vivado xsim (via `xvlog` / `xelab` / `xsim`, non-project mode)  
**Synthesis:** Vivado OOC non-project mode (`vivado -mode batch`)  
**Target device:** Artix-7 100T (`xc7a100tcsg324-1`), 100 MHz

Compile and simulate:
```bash
cd project/m4
xvlog -sv rtl/compute_core.sv rtl/interface.sv rtl/top.sv tb/tb_top.sv
xelab -top tb_top -snapshot tb_top_snap
xsim tb_top_snap -runall -log sim/final_run.log
```

Run OOC synthesis:
```bash
cd project/m4
vivado -mode batch -source synth/run_ooc.tcl \
       -log synth/openlane_run.log -journal reports/ooc.jou
```

Requires Vivado 2023.x or later in `PATH` (or set `VIVADO=<path>`).

---

## Synthesis Note — Vivado OOC replaces OpenLane 2

The M4 deliverable checklist lists `synth/config.json` (OpenLane 2 ASIC synthesis).
This project uses **Vivado 2023.x Out-of-Context (OOC) synthesis** targeting the
Artix-7 100T FPGA (`xc7a100tcsg324-1`) instead, for the following reason:

> The hardware accelerator is deployed on the Nexys A7 FPGA board (Artix-7 device).
> OpenLane 2 targets ASIC standard-cell flows (SKY130, GF180). Vivado OOC is the
> appropriate and functionally equivalent synthesis flow for this target.

**`synth/constraints.xdc` serves the role of `config.json`**: it specifies the target
clock period (10 ns / 100 MHz), I/O delays (2 ns setup/hold), and the part number
(`xc7a100tcsg324-1`). The synthesis log (`synth/openlane_run.log`) and reports
(`area_report.txt`, `timing_report.txt`, `power_report.txt`) are Vivado outputs.

This substitution was disclosed at M3 (`project/m3/README.md`) and is carried forward
to M4.

---

## RTL Changes from M3

The M3 RTL was a single combined file (`project/m3/rtl/top.sv`). M4 splits it into
three files matching the required `project/m4/rtl/` structure:

| M3 | M4 | Contents |
|----|-----|---------|
| `top.sv` (lines 1–902) | `compute_core.sv` | `f64_mul`, `f64_add`, `gemm_systolic`, `kalman_update` |
| `top.sv` (lines 927–1168) | `interface.sv` | `axilite_slave` |
| `top.sv` (lines 1183–1269) | `top.sv` | `top` integration wrapper |

The source is `project/post_m3_Minor_Redesign/rtl/top.sv`, which incorporates the
post-M3 redesign (pipelined f64_mul/f64_add, 51-state FSM, programmable R_REG at 0xE8).
This is the RTL that produced the final benchmark numbers.

---

## Waveform Note

`sim/final_waveform.png` was copied from `project/m3/sim/cosim_waveform.png`.
The post_m3_Minor_Redesign simulation produced `cosim_waveform.vcd` (same testbench,
same AXI4-Lite interface) but no annotated PNG export. The M3 waveform shows the same
host-write / compute / host-read transaction pattern on the same interface.
To regenerate from the post_m3 VCD:
```bash
gtkwave project/post_m3_Minor_Redesign/sim/cosim_waveform.vcd \
        --script project/post_m3_Minor_Redesign/synth/gtkwave_export.tcl
```

---

## File Catalog

### Top-level

| File | Description | Checklist item |
|------|-------------|----------------|
| `README.md` | This file — M4 file catalog, synthesis note, reproduction instructions | §1 M4 folder README |

### `rtl/`

| File | Description | Checklist item |
|------|-------------|----------------|
| `rtl/compute_core.sv` | Compute core: `f64_mul`, `f64_add`, `gemm_systolic`, `kalman_update` | §2 Final RTL |
| `rtl/interface.sv` | AXI4-Lite interface: `axilite_slave` | §2 Final RTL |
| `rtl/top.sv` | Integration top: `top` (instantiates compute_core + interface) | §2 Final RTL |

### `tb/`

| File | Description | Checklist item |
|------|-------------|----------------|
| `tb/tb_top.sv` | Combined testbench: `clk_gen`, `veerwolf_bfm`, `axi_monitor`, `compute_core_checker`, `result_checker`, `program_block`, `tb_top`. Drives DUT through AXI4-Lite only. Dumps VCD; prints SIMULATION RESULT: PASS/FAIL. | §2 Final testbench |

### `sim/`

| File | Description | Checklist item |
|------|-------------|----------------|
| `sim/final_run.log` | Full xsim transcript — contains "SIMULATION RESULT: PASS" | §2 Final simulation log |
| `sim/final_waveform.png` | Annotated waveform: host-write / compute / host-read regions (see waveform note above) | §2 Final waveform image |

### `synth/`

| File | Description | Checklist item |
|------|-------------|----------------|
| `synth/constraints.xdc` | Vivado timing constraints: 10 ns clock, 2 ns I/O delays, part `xc7a100tcsg324-1` — replaces OpenLane `config.json` (see synthesis note) | §3 OpenLane 2 configuration |
| `synth/run_ooc.tcl` | Vivado OOC Tcl script: reads all 3 RTL files, runs `synth_design`, writes reports | §3 (synthesis script) |
| `synth/openlane_run.log` | Vivado OOC synthesis stdout/stderr — equivalent to OpenLane run log | §3 OpenLane run log |
| `synth/area_report.txt` | Utilisation: LUT, FF, DSP, BRAM counts and percentages | §3 Area report |
| `synth/timing_report.txt` | Timing summary: WNS, WHS, critical path start/end | §3 Timing report |
| `synth/power_report.txt` | Power estimate: 0.509 W total (0.423 W dynamic + 0.085 W static) | §3 Power report |

### `bench/`

| File | Description | Checklist item |
|------|-------------|----------------|
| `bench/benchmark.md` | Throughput, speedup (~108.7×), energy comparison (~51×), roofline analysis | §4 Measured throughput + speedup + energy |
| `bench/benchmark_data.csv` | Raw 5-run data for SW baseline and HW accelerator (cycles, time_ms, samples/sec, GFLOP/s, heap) | §4 Raw measurement data |
| `bench/roofline_final.png` | Roofline plot: target hardware ceiling, SW baseline point, M4 HW accelerator point | §4 Final roofline plot |

---

## Design Summary

**Selected option:** Option B — Kalman update accelerator (`top`)  
**Interface:** AXI4-Lite slave, 64-bit data, 32-bit address  
**Compute core:** `kalman_update` (H=[1,0,0], programmable R via R_REG, Newton-Raphson reciprocal, 51-state FSM)  
**Internal sub-core:** `gemm_systolic` (3×3 F64 weight-stationary array, 21-state FSM)  
**Test stimulus:** 15-iteration Kalman filter sequence from RVfpgaEL2 profiling data  
**Verification:** AXI4-Lite protocol SVAs + FSM contract assertions + F64 ULP comparator (≤4 ULP)  
**Measured speedup:** **108.7× throughput** vs RVfpgaEL2 software baseline (45-update loop)  
**Bottleneck:** AXI transaction latency (34 MMIO round-trips per update; compute is 1.3% of total time)
