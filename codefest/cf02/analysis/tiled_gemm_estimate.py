"""
Attainable FLOP/s for the Kalman filter update() kernel
if a tiled (cache-blocked) GEMM were implemented in C/C++.

Roofline model: Attainable GFLOP/s = min(Peak_Compute, AI × BW)

Key insight for 3x3 matrices:
  All persistent data (496 B) fits in a single L1 cache line region.
  With register-blocked tiled GEMM the persistent matrices are loaded once,
  all intermediate results stay in AVX registers, and only outputs are written.
  This realises the "ideal" arithmetic intensity (AI = 0.4637 FLOPs/B).

Memory hierarchy bandwidths — i7-11800H (Tiger Lake-H):
  L1D : 48 KB/core  — 2 load ports × 32 B = 64 B/cycle => 4.6 GHz * 64 B = 294 GB/s peak
                       practical ~80 % => ~235 GB/s
  L2  : 1.25 MB/core — ~64 B/cycle sustained => ~4.6 GHz * ~14 B eff ≈ 64 GB/s practical
  L3  : 24 MB shared — ~40–50 GB/s practical per core
  DRAM: dual-ch DDR4-3200, 80 % eff => ~41 GB/s
"""

# ---------------------------------------------------------------------------
# Constants (from previous analysis files)
# ---------------------------------------------------------------------------
FLOPS          = 230        # FLOPs per update() call
AI_IDEAL       = 0.4637     # FLOPs/byte — intermediates in registers (ideal tiled GEMM)
AI_DRAM_NOREUSE = 0.1155    # FLOPs/byte — worst case, no reuse

PEAK_DP_GFLOPS = 1177.6     # GFLOP/s  (8 cores × 4.6 GHz × 32 FLOPs/cy, AVX-512 DP)

# Measured baseline (Python/NumPy from sw_baseline.md)
BASELINE_US_PER_UPDATE = 81.70   # µs
BASELINE_MFLOPS = FLOPS / (BASELINE_US_PER_UPDATE * 1e-6) / 1e6  # MFLOP/s

# ---------------------------------------------------------------------------
# Memory hierarchy bandwidths (GB/s, practical)
# ---------------------------------------------------------------------------
hierarchy = [
    ("L1 cache",  235.0,  "48 KB/core, fits all KF data (496 B)"),
    ("L2 cache",   64.0,  "1.25 MB/core"),
    ("L3 cache",   45.0,  "24 MB shared"),
    ("DRAM",       41.0,  "dual-ch DDR4-3200, 80% eff"),
]

# Ridge point = Peak / BW  (FLOPs/byte at which compute and memory ceilings meet)
def ridge(bw_gbs):
    return PEAK_DP_GFLOPS / bw_gbs

def attainable(ai, bw_gbs):
    memory_ceil = ai * bw_gbs   # GFLOP/s
    return min(PEAK_DP_GFLOPS, memory_ceil), memory_ceil

# ---------------------------------------------------------------------------
# Tiled GEMM scenario
# ---------------------------------------------------------------------------
# For 3x3 matrices the tile IS the matrix — the entire update() kernel
# (496 B persistent + small intermediates) fits in L1.
# Register-blocked tiled GEMM:
#   - Load persistent inputs once from L1
#   - Compute all 230 FLOPs with intermediates in AVX registers
#   - Write outputs back to L1
# => Traffic = ideal 496 B, bandwidth = L1

tiled_bw = hierarchy[0][1]   # L1 bandwidth
tiled_att, tiled_mem_ceil = attainable(AI_IDEAL, tiled_bw)

# Expected time per update() with tiled GEMM (L1-bound)
tiled_time_ns = (AI_IDEAL * 496) / (tiled_bw * 1e9) * 1e9   # ns
# alternate: time = 496 B / (235 GB/s)
tiled_time_ns2 = 496 / (tiled_bw * 1e9) * 1e9

# compute-only time lower bound
compute_time_ns = FLOPS / (PEAK_DP_GFLOPS * 1e9) * 1e9

speedup = tiled_att / (BASELINE_MFLOPS / 1e3)   # vs baseline in GFLOP/s

# ---------------------------------------------------------------------------
# Report
# ---------------------------------------------------------------------------
SEP = "=" * 68
sep = "-" * 68

lines = [
    SEP,
    "Tiled GEMM Performance Estimate: KF update() on i7-11800H",
    SEP,
    "",
    "KERNEL PARAMETERS",
    sep,
    f"  FLOPs per update()         : {FLOPS}",
    f"  AI ideal (tiled GEMM)      : {AI_IDEAL:.4f} FLOPs/byte",
    f"  Persistent data footprint  : 496 B  (fits in L1 — tile = full matrix)",
    f"  Peak DP compute            : {PEAK_DP_GFLOPS:.1f} GFLOP/s  (AVX-512, 8c, 4.6 GHz)",
    "",
    "MEMORY HIERARCHY ROOFLINE",
    sep,
    f"  {'Level':<12} {'BW (GB/s)':>10} {'Ridge (FLOPs/B)':>16} "
    f"{'Att. GFLOP/s':>14} {'Bound'}",
    f"  {'─'*12} {'─'*10} {'─'*16} {'─'*14} {'─'*7}",
]
for name, bw, note in hierarchy:
    att, mc = attainable(AI_IDEAL, bw)
    rp = ridge(bw)
    bound = "compute" if att >= PEAK_DP_GFLOPS * 0.999 else "memory"
    lines.append(
        f"  {name:<12} {bw:>10.1f} {rp:>16.2f} {att:>14.2f}   {bound}"
        f"  [{note}]"
    )

lines += [
    "",
    SEP,
    "TILED GEMM ESTIMATE  (register-blocked, L1-resident)",
    sep,
    "  For n=3, m=1: the 3×3 matrices are smaller than one AVX-512 register.",
    "  A register-blocked tiled GEMM loads each persistent tensor once from L1,",
    "  holds all intermediates in registers, and writes outputs back to L1.",
    "  This realises the ideal AI and is bounded by L1 read bandwidth.",
    "",
    f"  Memory traffic (ideal)     : 496 B  (inputs) + 128 B  (outputs) = 496 B total",
    f"  L1 bandwidth (practical)   : {tiled_bw:.0f} GB/s",
    f"  Memory-bound time          : 496 B / {tiled_bw:.0f} GB/s = {tiled_time_ns2:.2f} ns",
    f"  Compute-bound time         : {FLOPS} FLOPs / {PEAK_DP_GFLOPS:.1f} GFLOP/s = {compute_time_ns:.3f} ns",
    f"  Bottleneck                 : MEMORY (L1)  — AI {AI_IDEAL:.4f} < ridge {ridge(tiled_bw):.2f} FLOPs/B",
    "",
    f"  ┌─────────────────────────────────────────────────────────┐",
    f"  │  Attainable FLOP/s  ≈  {tiled_att:.1f} GFLOP/s          │",
    f"  │  Time per update()  ≈  {tiled_time_ns2:.2f} ns                    │",
    f"  └─────────────────────────────────────────────────────────┘",
    "",
    "COMPARISON",
    sep,
    f"  {'Scenario':<40} {'GFLOP/s':>12} {'Time/update':>14}",
    f"  {'─'*40} {'─'*12} {'─'*14}",
    f"  {'Python/NumPy baseline (measured)':<40} {BASELINE_MFLOPS/1e3:>12.4f} {BASELINE_US_PER_UPDATE:>12.2f} µs",
    f"  {'Tiled GEMM — DRAM bound (no reuse)':<40} {AI_DRAM_NOREUSE*41:>12.2f} {(FLOPS/(AI_DRAM_NOREUSE*41e9))*1e9:>12.2f} ns",
    f"  {'Tiled GEMM — L3 bound':<40} {attainable(AI_IDEAL,45)[0]:>12.2f} {(tiled_time_ns2*235/45):>12.2f} ns",
    f"  {'Tiled GEMM — L2 bound':<40} {attainable(AI_IDEAL,64)[0]:>12.2f} {(tiled_time_ns2*235/64):>12.2f} ns",
    f"  {'Tiled GEMM — L1 bound (target)':<40} {tiled_att:>12.2f} {tiled_time_ns2:>12.2f} ns",
    f"  {'Peak compute ceiling':<40} {PEAK_DP_GFLOPS:>12.1f} {'0.195 ns':>14}",
    "",
    f"  Speedup vs Python baseline  : {speedup:.0f}×",
    f"  Efficiency vs peak compute  : {tiled_att/PEAK_DP_GFLOPS*100:.1f}%",
    "",
    "KEY TAKEAWAYS",
    sep,
    "  1. Even with perfect tiled GEMM (register-blocked, L1-resident), the",
    f"     KF update() remains MEMORY-BOUND (AI {AI_IDEAL:.4f} << ridge {ridge(tiled_bw):.2f}).",
    "  2. The L1-bound ceiling is ~109 GFLOP/s — 9.3% of peak DP compute.",
    "  3. To become compute-bound, AI must exceed the L1 ridge point",
    f"     ({ridge(tiled_bw):.2f} FLOPs/byte), requiring ~{ridge(tiled_bw)/AI_IDEAL:.0f}× more FLOPs per",
    "     byte loaded — e.g., batching many filter instances over shared A/C.",
    "  4. Practical tiled GEMM in C achieves ~80% of the L1 ceiling =>",
    f"     ~{tiled_att*0.8:.0f} GFLOP/s, still a {speedup*0.8:.0f}× improvement over baseline.",
    SEP,
]

report = "\n".join(lines)
print(report)

out = "analysis/tiled_gemm_estimate.txt"
with open(out, "w") as f:
    f.write(report)
print(f"\nSaved to {out}")
