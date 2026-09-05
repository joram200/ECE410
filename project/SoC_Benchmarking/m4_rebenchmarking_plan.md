# M4 Benchmark Plan — Kalman HW Accelerator
## For: Claude Sonnet (automated execution)

This document is a complete, self-contained instruction set for running the
updated benchmark program, collecting raw measurements, and producing every
benchmark deliverable required by the ECE 410/510 Milestone 4 checklist.
Execute each section in order. Do not skip steps.

---

## 1. Background and Problem Statement

### What this project is

A 1D Kalman measurement-correction accelerator implemented as an AXI slave on a
Nexys A7 FPGA (SoC_impl bitstream). The host CPU is a SweRV EL2 RISC-V core
running at 13 MHz. The accelerator handles the correction step (K, x_out, P_out)
in hardware; the host CPU handles the predict step (x_hat_new = A·x_hat,
P_pred = A·P·A^T + Q) in software.

The software baseline is `RVfpgaEL2_profiling/test/kalman-test.cpp`, which runs
the identical 3-state Kalman filter (same A, C, Q, R, P0, x0, 45 measurements)
entirely in software using the Eigen `KalmanFilter` class.

### Problem with the old benchmark program

`kalman_hw_driver/src/main.cpp` (the version before this session) implemented the
predict step as **raw C nested loops**, not using the `KalmanFilter` Eigen class.
This introduced two errors:

1. **Structural asymmetry**: The SW baseline uses `KalmanFilter::update()` (Eigen).
   The old HW benchmark used hand-written C loops. The two programs were measuring
   different implementations of the same algorithm, making the comparison misleading.
   The new program calls `KalmanFilter::update_hw()` — the same class wrapper,
   replacing only the correction step with the MMIO call — making the comparison
   apples-to-apples.

2. **Wrong FLOPs count**: `scripts/run_profiles.sh` used `HW_FLOPS=1080`
   (24 FLOPs/update × 45). This 24-FLOPs figure came from the hardware correct
   step only (`compute_metrics.py` note: "11 MACs × 2 + 2 extra ops"). But the
   mcycle CSR bracket times **both** the predict and the correct steps. Using only
   the correct-step FLOPs in the numerator while timing the full predict+correct
   window causes GFLOP/s to be severely understated.

   **Corrected FLOPs:**
   - Predict (Eigen, per update): x_hat_new = A·x_hat → 9 mults + 6 adds = 15 FLOPs;
     P = A·P·A^T + Q → 2×(27 mults + 18 adds) + 9 adds = 99 FLOPs. Total: **114 FLOPs**
   - Correct (HW MMIO, per update): S, S_inv, K, y, Ky, x_out, KP, P_out → **24 FLOPs**
   - **Total per update: 138 FLOPs**
   - **Total for 45 updates: 6,210 FLOPs**

   `run_profiles.sh` must be updated: change `HW_FLOPS=1080` → `HW_FLOPS=6210`.

### What was already fixed (do not redo)

The following source files were already rewritten. **Do not modify them.**

| File | What changed |
|------|-------------|
| `src/main.cpp` | Replaced raw-C main with KalmanFilter class structure mirroring kalman-test.cpp; calls `kf.update_hw(y)` in loop |
| `include/kalman.hpp` | Added `update_hw(const Eigen::VectorXd& y)` declaration |
| `src/kalman.cpp` | Added `#include "kalman_hw.h"` and `update_hw()` implementation: Eigen predict → marshal arrays → `kalman_hw_update()` → unmarshal |
| `platformio.ini` | Added `-I lib/eigen-5.0.0`, `-include eigen_compat.h`, stack `0x8000` → `0x20000` |

---

## 2. Pre-flight Checks

Before building or running, verify the following. These are hardware requirements
that cannot be automated.

1. **FPGA programmed**: The Nexys A7 must be programmed with the SoC_impl
   bitstream at `../SoC_impl/SoC_impl.runs/impl_1/rvfpganexys.bit`. The Kalman
   AXI slave lives at `0x80010000`.
2. **USB-JTAG connected**: OpenOCD uses the Digilent HS2 cable on port 3333.
   No other OpenOCD instance must be running.
3. **PlatformIO toolchain present**: Verify:
   ```
   ls ~/.platformio/packages/tool-openocd-riscv-chipsalliance/bin/openocd
   ls ~/.platformio/packages/toolchain-riscv/bin/riscv64-unknown-elf-gdb
   ```

Working directory for all commands below: `project/SoC_Benchmarking/kalman_hw_driver/`

---

## 3. Fix the FLOPs Count in run_profiles.sh

Edit `scripts/run_profiles.sh`. Change line 35:

```bash
# BEFORE (wrong — counts only HW correct step):
HW_FLOPS=1080          # 24 FLOPs/update × 45 updates (hardware kernel FLOPs only)

# AFTER (correct — counts full Eigen predict + HW correct window):
HW_FLOPS=6210          # 138 FLOPs/update × 45 updates (114 predict + 24 HW correct)
```

Also update the comment on the `--total-flops` note at the bottom of `compute_metrics.py`
(line 127) to match:
```python
# BEFORE:
"  FLOPs/update: 24 (11 MACs x2 + 2 extra; see cman_ai_analysis.md)",
# AFTER:
"  FLOPs/update: 138 (114 Eigen predict: 15 x_hat + 99 P_pred; 24 HW correct: 11 MACs×2 + 2)",
```

---

## 4. Build the New Firmware

```bash
cd project/SoC_Benchmarking/kalman_hw_driver
pio debug --environment swervolf_nexys
```

Expected: build completes without error. The ELF lands at
`.pio/build/swervolf_nexys/firmware.elf`.

Verify `profile_done` is present:
```bash
~/.platformio/packages/toolchain-riscv/bin/riscv64-unknown-elf-nm \
    .pio/build/swervolf_nexys/firmware.elf \
    | grep profile_done
```
Must print a `T`-type symbol. If not, the build failed silently.

---

## 5. Run the Automated Benchmark (5 Runs)

```bash
cd project/SoC_Benchmarking/kalman_hw_driver
./scripts/run_profiles.sh
```

This script:
1. Resolves `profile_done()` address via `nm`
2. Starts OpenOCD (one instance for all 5 runs)
3. For each run: generates a GDB script from `scripts/gdb_hw.gdb`, runs GDB in
   batch mode, parses `METRIC` lines, writes `results/run_N/metrics.txt`
4. Calls `scripts/compute_metrics.py` to produce `results/summary.txt`

**Expected output** (approximate — actual numbers will differ from old raw-C run):
```
=== 5 / 5 runs successful ===
```
Per-run lines should show `cycles:` in the ~50,000–200,000 range and `heap: 0 B`.
Non-zero heap indicates unexpected dynamic allocation in Eigen.

**Timeout**: each GDB session has a 120-second timeout. If FPGA is not responding,
the run fails with "FAILED — cycle metrics missing or zero".

Per-run outputs land in:
```
results/
├── openocd.log
├── run_1/
│   ├── gdb_output.txt     ← raw GDB transcript
│   └── metrics.txt        ← key=value pairs
├── run_2/ ... run_5/
└── summary.txt            ← formatted table with AVG row
```

---

## 6. Collect and Verify Results

Read `results/summary.txt`. Extract the AVG row values:
- `cycles_elapsed` (average)
- `time_ms` (average)
- `samples_per_s` (average)
- `gflops` (average — will be higher than old 2.73e-04 because FLOPs numerator is larger)
- `heap_bytes` (must be 0)

**SW baseline reference** (from `RVfpgaEL2_profiling/results/summary.txt`, already measured):
```
AVG  5,587,112  429.778 ms  104.706 samples/s  2.4082e-05 GFLOP/s  49,760 B heap
```

Compute speedup:
```
speedup_cycles   = 5,587,112 / <HW avg cycles>
speedup_samples  = <HW avg samples/s> / 104.706
```
Both ratios must agree (they are the same quantity). If they disagree, recheck parsing.

---

## 7. Produce M4 Benchmark Deliverables

All deliverables go in `project/m4_corrected/bench/`. Create the directory if it does not exist:
```bash
mkdir -p project/m4_corrected/bench
```

### 7a. benchmark_data.csv

Produce a CSV from all five `results/run_N/metrics.txt` files. The CSV must contain
one row per run plus a header and an AVG row. Columns required by M4:

```
run,cycles_elapsed,time_ms,samples_per_s,gflops,heap_bytes
1,<val>,<val>,<val>,<val>,<val>
2,...
3,...
4,...
5,...
AVG,<avg>,<avg>,<avg>,<avg>,<avg>
```

You can generate this with a short Python script reading each `metrics.txt` via
the same `read_metrics()` pattern already in `scripts/compute_metrics.py`.

Save to: `project/m4_corrected/bench/benchmark_data.csv`

### 7b. benchmark.md

Create `project/m4_corrected/bench/benchmark.md` with the following sections. Fill in
measured values where `<…>` appears:

```markdown
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
| Avg cycles | <hw_cycles> | 5,587,112 |
| Time for 45 updates | <hw_time_ms> ms | 429.778 ms |
| Samples/s | <hw_samples_per_s> | 104.706 |
| GFLOP/s | <hw_gflops> | 2.4082e-05 |
| Heap delta | 0 B | 49,760 B |

## Speedup vs M1 Software Baseline

- SW baseline time: 429.778 ms (5,587,112 cycles at 13 MHz)
- HW accelerator time: <hw_time_ms> ms (<hw_cycles> cycles)
- **Speedup: <speedup>×** (= 429.778 / <hw_time_ms>)

The speedup reflects the full predict+correct pipeline on the same SoC:
both programs run the same predict step (Eigen, 3×3 matrices) on the same CPU;
the correction step moves to hardware.

## Energy Estimate (Optional)

If synthesis power report is available (project/m4/synth/power_report.txt):

- Accelerator dynamic power from OpenLane: <P_mW> mW (at target clock)
- HW accelerator runtime: <hw_time_ms> ms = <hw_time_s> s
- Energy: <P_mW> × 10^-3 W × <hw_time_s> s = <E_uJ> µJ per 45-update batch

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
```

### 7c. roofline_final.png

Generate the roofline plot using Python + matplotlib. The script below is complete
and self-contained — run it from the repo root:

```python
#!/usr/bin/env python3
"""
Generate project/m4_corrected/bench/roofline_final.png
Run from repo root: python3 project/m4_corrected/bench/make_roofline.py
"""
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import numpy as np
import os

# ── Hardware roofline parameters (SweRV EL2, 13 MHz, no FPU) ────────────────
# Peak compute: 1 FP op/cycle (software FP via libgcc) × 13 MHz = 13 MFLOPs/s
# Memory BW: AXI bus to BRAM, estimated 4 bytes/cycle × 13 MHz = 52 MB/s
PEAK_COMPUTE_GFLOPS = 13e6 / 1e9        # 0.013 GFLOP/s
PEAK_BW_GB_S        = 52e6 / 1e9        # 0.052 GB/s

# ── Kernel arithmetic intensities (FLOPs / bytes transferred) ────────────────
# SW baseline: 10,350 FLOPs; state+cov in/out = ~9 doubles × 8 B = 72 B per
#   update × 45 = 3,240 B transferred (conservative; Eigen may transfer more)
SW_FLOPS      = 10_350
SW_BYTES      = 3_240
SW_AI         = SW_FLOPS / SW_BYTES     # ~3.19 FLOPs/byte

# HW accelerator: 6,210 FLOPs; MMIO writes/reads = 12 doubles (z,x_in[3],
#   P_in[9],x_out[3],P_out[9]) = 24×8 B = 192 B per update × 45 = 8,640 B
# Plus Eigen predict reads/writes of x(3) and P(9×2) = 12 doubles = 96 B/update
# Total per update: 192 + 96 = 288 B → 288 × 45 = 12,960 B
HW_FLOPS      = 6_210
HW_BYTES      = 12_960
HW_AI         = HW_FLOPS / HW_BYTES    # ~0.48 FLOPs/byte

# ── Measured performance points ──────────────────────────────────────────────
# Fill in from results/summary.txt AVG row after running run_profiles.sh:
SW_GFLOPS_MEASURED  = 2.4082e-05   # from RVfpgaEL2_profiling/results/summary.txt
HW_GFLOPS_MEASURED  = None         # REPLACE with <hw_gflops> from results/summary.txt AVG

# ── Plot ─────────────────────────────────────────────────────────────────────
fig, ax = plt.subplots(figsize=(8, 5))

ai_range = np.logspace(-2, 3, 500)

# Roofline: min(peak_compute, peak_bw × AI)
roof = np.minimum(PEAK_COMPUTE_GFLOPS, PEAK_BW_GB_S * ai_range)
ax.loglog(ai_range, roof, 'k-', linewidth=2, label='SweRV EL2 roofline')

# Ridge point
ridge_ai = PEAK_COMPUTE_GFLOPS / PEAK_BW_GB_S
ax.axvline(ridge_ai, color='gray', linestyle=':', linewidth=1)
ax.text(ridge_ai * 1.05, PEAK_COMPUTE_GFLOPS * 0.7,
        f'Ridge = {ridge_ai:.2f} FLOPs/B', fontsize=8, color='gray')

# SW baseline point
ax.loglog(SW_AI, SW_GFLOPS_MEASURED, 'bs', markersize=10,
          label=f'SW baseline  ({SW_AI:.2f} FLOPs/B, {SW_GFLOPS_MEASURED:.2e} GFLOP/s)')

# HW accelerator point
if HW_GFLOPS_MEASURED is not None:
    ax.loglog(HW_AI, HW_GFLOPS_MEASURED, 'r^', markersize=10,
              label=f'HW accelerator  ({HW_AI:.2f} FLOPs/B, {HW_GFLOPS_MEASURED:.2e} GFLOP/s)')
else:
    ax.axvline(HW_AI, color='red', linestyle='--', linewidth=1.5,
               label=f'HW accelerator AI = {HW_AI:.2f} FLOPs/B  (run benchmark to get Y)')

ax.set_xlabel('Arithmetic Intensity (FLOPs / byte)', fontsize=11)
ax.set_ylabel('Performance (GFLOP/s)', fontsize=11)
ax.set_title('Roofline — Kalman Filter: SW Baseline vs HW Accelerator\n'
             'SweRV EL2 @ 13 MHz, Nexys A7', fontsize=11)
ax.legend(fontsize=8)
ax.grid(True, which='both', linestyle=':', alpha=0.5)
ax.set_xlim(1e-2, 1e3)
ax.set_ylim(1e-7, 1e-1)

out = 'project/m4_corrected/bench/roofline_final.png'
os.makedirs(os.path.dirname(out), exist_ok=True)
plt.tight_layout()
plt.savefig(out, dpi=150)
print(f"Saved {out}")
```

Save this script as `project/m4_corrected/bench/make_roofline.py`.

**Before running**: replace `HW_GFLOPS_MEASURED = None` with the actual `gflops`
value from `results/summary.txt` AVG row.

Run: `python3 project/m4_corrected/bench/make_roofline.py`

Verify the output PNG exists and shows:
- Black roofline line (compute-bound region flat, memory-bound region sloped)
- Blue square: SW baseline point (low AI ≈ 3.19, low GFLOP/s ≈ 2.4e-5)
- Red triangle: HW accelerator point (lower AI ≈ 0.48 due to MMIO bytes, higher GFLOP/s)

Both points should sit below the roofline. If the HW accelerator point is above
the roofline, recheck the arithmetic intensity or FLOPs calculation.

---

## 8. M4 Deliverable Checklist for bench/

After completing all steps above, the following files must exist:

```
project/m4_corrected/bench/
├── benchmark.md           ← Section 4 of M4 checklist (throughput + speedup + energy)
├── benchmark_data.csv     ← Raw measurements, all 5 runs + AVG
├── roofline_final.png     ← Log-log roofline with SW baseline and HW point
└── make_roofline.py       ← Script used to generate the plot (keep for reproducibility)
```

Verify every number in `benchmark.md` traces to a row in `benchmark_data.csv`.
The grader and final examiner will follow specific numbers back to raw data.

---

## 9. Reference Numbers (Pre-existing, Do Not Remeasure)

These are from already-completed runs. Use them for comparison and for benchmark.md.

### SW Baseline (RVfpgaEL2_profiling, Eigen, pure software):
```
Avg cycles    : 5,587,112
Time (ms)     : 429.778
Samples/s     : 104.706
GFLOP/s       : 2.4082e-05  (at 10,350 FLOPs/45-update batch)
Heap delta    : 49,760 B
```
Source: `project/RVfpgaEL2_profiling/results/summary.txt`

### Old HW Benchmark (raw-C predict, WRONG FLOPs — for reference only):
```
Avg cycles    : 51,378
Time (ms)     : 3.952
Samples/s     : 11,386
GFLOP/s       : 2.7327e-04  (understated — used 1,080 FLOPs instead of 6,210)
Heap delta    : 0 B
```
Source: `project/SoC_Benchmarking/kalman_hw_driver/results/summary.txt`
(These were produced by the old raw-C program. Do NOT use in M4 deliverables.)

The new run from Step 5 will produce the authoritative M4 numbers.
The cycle count should be in the same ballpark (Eigen predict ≈ raw-C predict
on this compiler/target), but the GFLOP/s will be substantially higher due to
the corrected 6,210 FLOPs numerator.

---

## 10. Key File Paths

| Purpose | Path |
|---------|------|
| New main.cpp | `project/SoC_Benchmarking/kalman_hw_driver/src/main.cpp` |
| Run script | `project/SoC_Benchmarking/kalman_hw_driver/scripts/run_profiles.sh` |
| Per-run raw data | `project/SoC_Benchmarking/kalman_hw_driver/results/run_N/metrics.txt` |
| Averaged summary | `project/SoC_Benchmarking/kalman_hw_driver/results/summary.txt` |
| M4 corrected benchmark dir | `project/m4_corrected/bench/` |
| SW baseline summary | `project/RVfpgaEL2_profiling/results/summary.txt` |
| HW MMIO header | `project/SoC_Benchmarking/kalman_hw_driver/include/kalman_hw.h` |
| KalmanFilter class | `project/SoC_Benchmarking/kalman_hw_driver/src/kalman.cpp` |
