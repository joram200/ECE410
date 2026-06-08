# M4 Benchmark — Kalman Filter Hardware Acceleration

Raw measurement data: [`benchmark_data.csv`](benchmark_data.csv)  
Roofline plot: [`roofline_final.png`](roofline_final.png)  
Source: `project/RVfpgaEL2_profiling/` (SW) and `project/SoC_Benchmarking/kalman_hw_driver/results/summary.txt` (HW)

---

## Measurement Method

Both SW and HW measurements use GDB JTAG hardware breakpoints with `mcycle` CSR
snapshots bracketing a 45-update loop on the Nexys A7 board (13 MHz SweRV EL2 clock).
Five back-to-back runs per configuration. Heap usage measured via bump-allocator
high-water mark. All raw cycle counts are in `benchmark_data.csv`.

---

## Software Baseline (M1)

Measured on Nexys A7, RVfpgaEL2 bitstream. Full Kalman predict+update in Eigen C++.

| Metric | Value |
|--------|-------|
| Total time (45 updates) | 429.778 ms |
| Per-update latency | 9.551 ms |
| Throughput | 104.71 samples/sec |
| GFLOP/s | 2.408 × 10⁻⁵ |
| Heap usage | 49,760 B (Eigen dynamic allocs) |
| Run-to-run variance | < 0.01% |
| FLOPs per update | 10,350 (full predict+update) |
| Bytes transferred per update | ~216 B (Eigen GEMM) |
| Arithmetic intensity | 0.21 FLOP/byte |
| Bound | Compute-bound |

---

## Hardware Accelerator (M4)

Measured on Nexys A7, SoC_impl bitstream (post_m3_Minor_Redesign RTL).
Driver: `project/SoC_Benchmarking/kalman_hw_driver/` (MMIO via AXI4-Lite).

| Metric | Value |
|--------|-------|
| Total time (45 updates) | 3.952 ms |
| Per-update latency | 87.8 µs |
| Throughput | 11,386 samples/sec |
| GFLOP/s | 2.733 × 10⁻⁴ |
| Heap usage | 0 B |
| Run-to-run variance | < 0.03% |
| FLOPs per update | 24 (measurement-correction only) |
| Bytes transferred per update | 272 B (34 × 8 B MMIO transactions) |
| Arithmetic intensity | 0.088 FLOP/byte |
| Bound | Memory-bound (AXI transaction latency) |

### Latency Breakdown (87.8 µs/update at 13 MHz)

| Component | Time | Share |
|-----------|------|-------|
| Accelerator compute (51 FSM states × ~0.077 µs) | ~1.1 µs | ~1.3% |
| MMIO writes: z + x_in[3] + P_in[9] = 13 transactions | ~33.8 µs | ~38.5% |
| MMIO reads: x_out[3] + P_out[9] + STAT = 13 transactions | ~33.8 µs | ~38.5% |
| STAT poll + SW overhead + AXI crossbar arbitration | ~19.1 µs | ~21.8% |
| **Total (avg 2.6 µs/transaction × 34 round-trips)** | **~87.8 µs** | **100%** |

The accelerator computes in only **1.3%** of the total per-update time; the remaining
98.7% is AXI bus round-trip latency (34 MMIO transactions per update).

---

## Speedup vs M1 Baseline

| Metric | SW Baseline | HW Accelerator | Speedup |
|--------|-------------|----------------|---------|
| Total time, 45 updates | 429.778 ms | 3.952 ms | **108.7×** |
| Per-update latency | 9.551 ms | 87.8 µs | **108.8×** |
| Throughput | 104.71 samples/sec | 11,386 samples/sec | **108.7×** |
| GFLOP/s | 2.408 × 10⁻⁵ | 2.733 × 10⁻⁴ | 11.4× |
| Heap usage | 49,760 B | 0 B | — |

**Why 11.4× GFLOP/s vs 108.7× latency speedup:** The hardware kernel executes only
24 FLOPs (measurement-correction step) versus the software's 10,350 FLOPs (full
predict+update). The hardware is faster per-update but performs far fewer floating-point
operations, so the GFLOP/s ratio is lower than the throughput ratio.

**Why ~109× vs the 35× M1 projection:** The M1 projection assumed conservative AXI
round-trip timing. The measured ~2.6 µs per transaction is faster than the worst-case
estimate because the accelerator completes in ~1.1 µs (so polling wait is short) and
AXI crossbar latency is lower than assumed.

---

## Energy Comparison

| Metric | SW Baseline | HW Accelerator |
|--------|-------------|----------------|
| Per-update runtime | 9.551 ms | 87.8 µs |
| Estimated power | ~0.2 W (SweRV EL2 CPU dynamic, FPGA) | 0.423 W dynamic (synthesis, `synth/power_report.txt`) |
| Energy per update | ~1,910 µJ | **37.1 µJ** |
| Energy ratio | 1× | **~51× lower** |

SW power estimate: SweRV EL2 core at 13 MHz on Artix-7 — approximately 0.2 W dynamic
(CPU + memory, Nexys A7 datasheet typical). HW power from Vivado synthesis report
(`synth/power_report.txt`): 0.423 W dynamic (includes all IP, LUTs, DSPs, clocks).
The HW runtime is 108.7× shorter, partially offset by the higher instantaneous power,
yielding ~51× better energy efficiency per Kalman update.

---

## Roofline Analysis

Target hardware: Nexys A7 AXI4-Lite interface at 13 MHz, 8-byte bus width.
Peak AXI4-Lite bandwidth: 13 MHz × 8 B/cycle = 104 MB/s = 0.104 GB/s.

| Parameter | Value |
|-----------|-------|
| Peak AXI bandwidth | 0.104 GB/s |
| Peak compute (OOC synthesis, 100 MHz, 24 FLOPs) | ~2.4 GFLOP/s theoretical |
| HW accelerator arithmetic intensity | 0.088 FLOP/byte |
| HW accelerator measured GFLOP/s | 2.733 × 10⁻⁴ |
| AXI bandwidth ceiling at 0.088 FLOP/byte | ~9.2 × 10⁻³ GFLOP/s |
| Gap below bandwidth ceiling | **33.6×** |

The design sits **33.6× below the AXI bandwidth ceiling** at its measured arithmetic
intensity. This is not a bandwidth bottleneck — it is a **transaction-latency** bottleneck.
Each of the 34 MMIO round-trips incurs AW→W→B or AR→R handshake latency (~2.6 µs at
13 MHz), not bandwidth saturation. The roofline model does not capture round-trip latency;
the effective constraint is transactions/second, not bytes/second.

The highest-leverage improvement (from `Post-m3_Redesign.txt`) is **state retention**:
persisting x and P internally would reduce 34 transactions to ~5 per update, yielding
an estimated ~6.8× additional speedup to ~240× overall.

See [`roofline_final.png`](roofline_final.png) for the roofline plot showing the SW
baseline point, AXI bandwidth ceiling, and the M4 hardware accelerator design point.
