# CF09 Benchmark Results — Kalman Filter Hardware Acceleration

## Software Baseline Metrics

**Measurement method**: GDB JTAG hardware breakpoints; `mcycle` CSR snapshots bracket
the 45-update loop; bump allocator high-water marks measure heap usage.
Source data: `project/RVfpgaEL2_profiling/results/summary.txt`

### 5-Run Average (measured on Nexys A7, RVfpgaEL2 bitstream)

| Metric | Value |
|--------|-------|
| Total time (45 updates) | 429.778 ms |
| Per-update latency | 9.551 ms |
| Throughput | 104.71 samples/sec |
| GFLOP/s | 2.408 × 10⁻⁵ |
| Heap usage | 49,760 B (Eigen dynamic allocs) |
| Run-to-run variance | < 0.01% (5,586,952–5,587,246 cycles) |

**Raw 5-run data:**

| Run | Cycles | Time (ms) | Samples/s | GFLOP/s | Heap (B) | Arcs |
|-----|--------|-----------|-----------|---------|---------|------|
| 1 | 5,587,059 | 429.774 | 104.710 | 2.4082 × 10⁻⁵ | 49,760 | 185 |
| 2 | 5,587,246 | 429.788 | 104.700 | 2.4082 × 10⁻⁵ | 49,760 | 185 |
| 3 | 5,587,246 | 429.788 | 104.700 | 2.4082 × 10⁻⁵ | 49,760 | 185 |
| 4 | 5,587,059 | 429.774 | 104.710 | 2.4082 × 10⁻⁵ | 49,760 | 185 |
| 5 | 5,586,952 | 429.766 | 104.710 | 2.4083 × 10⁻⁵ | 49,760 | 185 |
| **AVG** | **5,587,112** | **429.778** | **104.706** | **2.4082 × 10⁻⁵** | **49,760** | **185** |

---

## Hardware Accelerator Metrics

**Measurement method**: GDB JTAG hardware breakpoints; `mcycle` CSR snapshots bracket
the 45-update loop; bump allocator high-water marks measure heap usage.
Source data: `project/SoC_Benchmarking/kalman_hw_driver/results/summary.txt`

### 5-Run Average (measured on Nexys A7, SoC_impl bitstream)

| Metric | Value |
|--------|-------|
| Total time (45 updates) | 3.952 ms |
| Per-update latency | 87.8 µs |
| Throughput | 11,386 samples/sec |
| GFLOP/s | 2.733 × 10⁻⁴ |
| Heap usage | 0 B |
| Run-to-run variance | < 0.03% (51,367–51,384 cycles) |

**Raw 5-run data:**

| Run | Cycles | Time (ms) | Samples/s | GFLOP/s | Heap (B) |
|-----|--------|-----------|-----------|---------|---------|
| 1 | 51,383 | 3.953 | 11,385.09 | 2.7324 × 10⁻⁴ | 0 |
| 2 | 51,372 | 3.952 | 11,387.53 | 2.7330 × 10⁻⁴ | 0 |
| 3 | 51,384 | 3.953 | 11,384.87 | 2.7324 × 10⁻⁴ | 0 |
| 4 | 51,382 | 3.952 | 11,385.31 | 2.7325 × 10⁻⁴ | 0 |
| 5 | 51,367 | 3.951 | 11,388.63 | 2.7333 × 10⁻⁴ | 0 |
| **AVG** | **51,378** | **3.952** | **11,386.29** | **2.7327 × 10⁻⁴** | **0** |

**Latency breakdown** (at 13 MHz SweRV EL2 core clock, 87.8 µs/update):
- Accelerator compute: 14 FSM states × ~77 ns ≈ 1.1 µs (~1.3% of total)
- MMIO writes: 19 AXI transactions (z + x_in[3] + P_in[9])
- MMIO reads: 15 AXI transactions (x_out[3] + P_out[9])
- Polling STAT.busy + SW instruction overhead + AXI crossbar arbitration ≈ remainder
- **Dominant cost: AXI bus transactions** (34 round-trips × ~2.6 µs avg ≈ 87 µs)

---

## Speedup Tables

### Roofline Parameters

| Parameter | SW Baseline | HW Accelerator |
|-----------|-------------|----------------|
| FLOPs per update | 10,350 (full Kalman, with prediction) | 24 (measurement correction only) |
| Bandwidth per update | 216 B (Eigen matrix GEMM) | 272 B (MMIO: 34 × 8 B transactions) |
| Arithmetic intensity | 0.21 FLOP/byte | 0.088 FLOP/byte |
| Bound | Compute-bound | **Memory-bound (AXI bus)** |

### Performance Comparison

| Metric | SW Baseline (measured) | HW Accelerator (measured) | Speedup |
|--------|-------------------------------|-----------------------------------|---------|
| Total time, 45 updates | 429.778 ms | **3.952 ms** | **~108.7×** |
| Per-update latency | 9.551 ms | **87.8 µs** | **~108.8×** |
| Throughput | 104.71 samples/sec | **11,386 samples/sec** | **~108.7×** |
| GFLOP/s | 2.408 × 10⁻⁵ | **2.733 × 10⁻⁴** | ~11.4× |
| Heap usage | 49,760 B (Eigen allocs) | **0 B** | — |
| Clock | 13 MHz (SweRV EL2, rv32imac) | 13 MHz (same SoC) | — |

### Why ~109× and not the projected 35×?

The 35× projection assumed conservative AXI round-trip timing. The measured ~87.8 µs per
update means 34 transactions average **~2.6 µs each** — faster than anticipated, likely
because polling is short (the accelerator finishes in ~1.1 µs) and the AXI crossbar latency
is lower than worst-case estimates. The actual speedup of **~109×** reflects the real
hardware behaviour.

The GFLOP/s speedup (11.4×) is lower than throughput speedup because the hardware kernel
performs only 24 FLOPs vs the software's 10,350 FLOPs — the hardware offloads only the
measurement-correction step, not the full predict+update cycle.

### Potential Further Improvements (from `Post-m3_Redesign.txt`)

| Option | Estimated Speedup |
|--------|------------------|
| **Current (measured)** | **~109×** |
| + State retention (remove P_in/x_in writes each iteration) | ~240× |
| + Interrupt-driven polling (remove busy-wait) | ~250× |
| + Clock increase to 25 MHz | ~218× standalone |
| + Hardware batch loop (N=10) | ~1,500× |

---

*SW baseline: `project/RVfpgaEL2_profiling/RVfpgaEL2_profiling.txt`, Session 4 (GDB JTAG, 5-run avg)*
*HW results: `project/SoC_Benchmarking/kalman_hw_driver/results/summary.txt`, 2026-06-06*
*HW accelerator: `project/post_m3_Minor_Redesign/rtl/top.sv` in `project/SoC_Benchmarking/SoC_impl`*
*Driver: `project/SoC_Benchmarking/kalman_hw_driver/`*
