# CF03 — DRAM Traffic & Roofline Analysis
## Platform
- **GPU:** NVIDIA GeForce RTX 3070 Mobile (GA104M, SM 8.6)
- **Peak FP32 compute:** 16,590 GFLOP/s
- **Peak DRAM bandwidth:** 448 GB/s (GDDR6, 256-bit @ 14 Gbps)
- **Roofline ridge point:** 16,590 / 448 = **37.03 FLOP/byte**

Profiled with `ncu --section SpeedOfLight --section MemoryWorkloadAnalysis` (2 passes averaged).

---

## gemm_naive

### Achieved Metrics
| Metric | Value |
|---|---|
| Achieved GFLOP/s (cudaEvent) | 839 GFLOP/s |
| Compute (SM) Throughput | 95.65% of peak |
| DRAM Throughput | 9.88% of peak → **44.3 GB/s** |
| L1/TEX Throughput | 97.58% of peak |
| L1 Hit Rate | 94.93% |
| L2 Hit Rate | 65.86% |

### Roofline Position
- **Arithmetic intensity** = 839 GFLOP/s ÷ 44.3 GB/s = **18.9 FLOP/byte**
- Ridge point = 37.03 FLOP/byte
- 18.9 < 37.03 → **memory-bound**

### Interpretation
Despite 95.65% Compute (SM) Throughput, the kernel is memory-bound at the
**L1/TEX cache level** — not DRAM. The L1 hit rate of 94.93% means almost all
data is served from L1 (not DRAM), keeping the SMs fed and artificially inflating
the "compute throughput" metric (which measures SM pipeline utilization, not FP32
arithmetic). Only 9.88% of DRAM bandwidth is used because the L1 absorbs
nearly all traffic.

The naive kernel's 32×32 thread block maps each thread to a fixed output
element `C[row][col]`. All threads in a warp share the same row of A (perfect
temporal reuse → L1 hits) and access a coalesced strip of B. The L1 cache
(192 KB per SM) is large enough to hold the working tile and saturates before
DRAM does. On the DRAM roofline the kernel is memory-bound; on a cache-aware
roofline it is co-bottlenecked between L1 bandwidth and the LD/ST pipeline.

---

## gemm_tiled (tile = 8)

### Achieved Metrics
| Metric | Value |
|---|---|
| Achieved GFLOP/s (cudaEvent) | 985 GFLOP/s |
| Compute (SM) Throughput | 86.84% of peak |
| DRAM Throughput | 8.33% of peak → **37.3 GB/s** |
| L1/TEX Throughput | 87.00% of peak |
| L1 Hit Rate | 29.21% |
| L2 Hit Rate | 89.66% |

### Roofline Position
- **Arithmetic intensity** = 985 GFLOP/s ÷ 37.3 GB/s = **26.4 FLOP/byte**
- Ridge point = 37.03 FLOP/byte
- 26.4 < 37.03 → **memory-bound**

### Interpretation
The tiled kernel is also memory-bound, but the bottleneck has shifted from L1
to **L2 cache**. Tile size 8 provides only 8x reuse of shared-memory data
(theoretical arithmetic intensity = tile / 4 = 2 FLOP/byte from DRAM), but the
actual AI of 26.4 FLOP/byte shows the L2 absorbs most DRAM misses (89.66% L2
hit rate). The low L1 hit rate (29.21%) reflects that shared-memory accesses
bypass L1 and are counted as L1 misses, flooding L2 traffic (L2 Cache Throughput
rose from 8% in naive to 23.5% here).

The tile is too small to reuse data enough to escape the memory-bound regime.
Increasing to tile = 32 would raise arithmetic intensity to ~8 FLOP/byte (DRAM)
and push the design much closer to the 37.03 FLOP/byte ridge point.

---

## Roofline Summary

```
GFLOP/s
16590 |─────────────────────────────────── Peak Compute (16590 GFLOP/s)
      |                          /
      |                         / ridge @ 37.03 FLOP/byte
      |                        /
  985 |──────────────────── * tiled (26.4 FLOP/byte)   [memory-bound]
  839 |──────────────── * naive (18.9 FLOP/byte)        [memory-bound]
      |                /
      |               /  slope = 448 GB/s (peak DRAM BW)
      |              /
    0 +──────────────────────────────────────────────── FLOP/byte
      0             37.03
```

| Kernel | AI (FLOP/byte) | Ridge (FLOP/byte) | Bound |
|---|---|---|---|
| gemm_naive | 18.9 | 37.03 | Memory (L1-bound) |
| gemm_tiled (T=8) | 26.4 | 37.03 | Memory (L2-bound) |

Both kernels fall left of the ridge point and are **memory-bound**. The tiled
kernel is closer to the ridge (26.4 vs 18.9 FLOP/byte) and achieves higher
GFLOP/s because it reduces DRAM pressure via shared-memory blocking, but
tile = 8 is insufficient to cross into the compute-bound regime. A tile size
of 32 or larger would be required to make this kernel compute-bound on this GPU.
