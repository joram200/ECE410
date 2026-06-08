# ECE 410/510 Spring 2026
### Jose Ramirez

## Project: Basic Kalman Filter Update Hardware Accelerator

This project implements and benchmarks a hardware accelerator for the Kalman filter
measurement-update step on a Nexys A7 FPGA board (Artix-7 100T). The accelerator
offloads the measurement-correction kernel (innovation, Newton-Raphson matrix inversion,
Kalman gain, state and covariance update) from a SweRV EL2 RISC-V softcore, achieving
a **108.7× throughput speedup** over the software baseline running the same kernel in
Eigen C++ on the same board.

- **M4 deliverables:** [`project/m4/README.md`](project/m4/README.md)
- **Benchmark results:** [`project/m4/bench/benchmark.md`](project/m4/bench/benchmark.md)
- **Design justification report:** `project/m4/report/design_justification.pdf` *(Section 5 — in progress)*

---

## Interface

AXI4-Lite slave, 64-bit data path, 32-bit address space. The accelerator is
memory-mapped at the SweRV EL2 peripheral bus base address. The host writes z,
x_in[3], P_in[9], and R via MMIO, pulses CTRL.start, polls STAT.busy, then reads
x_out[3] and P_out[9] — 34 AXI round-trips per Kalman update.

The design is **memory-bound (AXI transaction latency)** at an arithmetic intensity
of 0.088 FLOP/byte. The accelerator compute completes in ~1.1 µs per update (1.3%
of total); the remaining 98.7% is AXI bus round-trip overhead.

## Precision

IEEE-754 double precision (FP64) throughout. Custom pipelined `f64_mul` (3-stage,
2-cycle latency) and `f64_add` (4-stage, 3-cycle latency) units synthesised into
Artix-7 DSP48E1 slices. Verified against software reference with ≤4 ULP error on
all 15-iteration test vectors.

## Key Numbers

| Metric | Value |
|--------|-------|
| SW baseline throughput (M1) | 104.71 samples/sec |
| HW accelerator throughput (M4) | 11,386 samples/sec |
| Speedup | **108.7×** |
| Per-update latency (HW) | 87.8 µs |
| Energy per update (HW) | ~37.1 µJ (~51× more efficient than SW) |
| Synthesis: LUTs / FFs / DSPs | see `project/m4/synth/area_report.txt` |
| WNS (100 MHz OOC) | see `project/m4/synth/timing_report.txt` |

## Milestone History

| Milestone | Path | Description |
|-----------|------|-------------|
| M1 | `project/m1/` | Interface selection, SW baseline profiling |
| M2 | `project/m2/` | Precision analysis, initial RTL |
| M3 | `project/m3/` | Synthesis + co-simulation, OOC timing closure |
| **M4** | **`project/m4/`** | **Final RTL (3-file split), synthesis, benchmarks** |
