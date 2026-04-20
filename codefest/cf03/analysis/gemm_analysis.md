# GEMM Analysis

## (a) Why the naive kernel is memory-bound
Each thread independently computes one output element by streaming through N=1024
elements of a row of A and a column of B. Although both accesses are coalesced
within a warp, the arithmetic intensity is only 0.25 FLOP/byte theoretically:
two FLOPs (one FMA) are performed per four bytes loaded from global memory.
Even with a 94.93% L1 hit rate hiding most DRAM traffic, the LD/ST pipeline
saturates at 97.6% utilisation — the kernel is bottlenecked by data movement
through the memory hierarchy, not by floating-point throughput.

## (b) How tiling reduces DRAM traffic.
Shared-memory tiling loads a T×T block of A and B into on-chip SRAM once per
tile step, amortising each global load across T threads. DRAM traffic scales as
2N³/T bytes instead of 2N³ bytes, raising arithmetic intensity by a factor of T.

## (c) Whether the tiled kernel achieved the expected improvement.
With T=8 the expected 8× reduction in DRAM traffic was largely realised
(DRAM throughput fell from 44.3 GB/s to 37.3 GB/s), yet performance improved
only 17% (839 → 985 GFLOP/s). The remaining bottleneck is the small tile size:
T=8 yields only 2 FLOP/byte arithmetic intensity, still well below the 37.03
FLOP/byte ridge point. The kernel shifted from L1-bound to L2-bound
(L2 hit rate 89.7%), meaning shared-memory saves bypass L1 but not L2.
A tile of 32 is needed to approach compute-bound operation.
