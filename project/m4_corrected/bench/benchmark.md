# Kalman HW Accelerator — M4 Benchmark Results

## System

- **Platform**: SweRV EL2 RISC-V (rv32imac), 13 MHz, Nexys A7 FPGA
- **Accelerator**: 1D scalar Kalman correction step, AXI slave at 0x80010000
- **Host driver**: `KalmanFilter::update_hw()` — Eigen predict (host CPU) +
  MMIO correct (accelerator)
- **Workload**: 45 predict+correct updates, 3-state filter
- **FLOPs counted**: 6,210 total (138/update: 114 Eigen predict + 24 HW correct)
- **Measurement method**: mcycle CSR delta (GDB JTAG, hardware breakpoint at
  `profile_done()`), 5 runs averaged

## Measured Accelerator Throughput

| Metric | HW Accelerator | SW Baseline |
|--------|---------------|-------------|
| Avg cycles | 1,865,478 | 5,587,112 |
| Time for 45 updates | 143.498 ms | 429.778 ms |
| Samples/s | 313.590 | 104.706 |
| GFLOP/s | 4.3276e-05 | 2.4082e-05 |
| Heap delta | 10,832 B | 49,760 B |

## Speedup vs M1 Software Baseline

- SW baseline time: 429.778 ms (5,587,112 cycles at 13 MHz)
- HW accelerator time: 143.498 ms (1,865,478 cycles)
- **Speedup: 2.995×** (= 429.778 / 143.498)

The speedup reflects the full predict+correct pipeline on the same SoC:
both programs run the same predict step (Eigen, 3×3 matrices) on the same CPU;
the correction step moves to hardware.

## Energy Estimate (Optional)

If synthesis power report is available (project/m4/synth/power_report.txt):

- Accelerator dynamic power from OpenLane: <P_mW> mW (at target clock)
- HW accelerator runtime: 143.498 ms = 0.143498 s
- Energy: <P_mW> × 10^-3 W × 0.143498 s = <E_uJ> µJ per 45-update batch

Note: this estimate covers only the accelerator tile, not the SoC or DRAM.

## Raw Data

See `benchmark_data.csv` in this folder for per-run cycle counts and derived
metrics. Each number in the table above traces to a run in that file.

## Notes on FLOPs Accounting

The old benchmark (`HW_FLOPS=1080`, 24 FLOPs/update) counted only the hardware
correction step FLOPs while timing the full predict+correct window. This caused
the reported GFLOP/s to understate the true value. The corrected count (6,210
total, 138/update) includes the Eigen predict step that executes on the host CPU
inside the mcycle bracket.
