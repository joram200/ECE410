"""
Peak FLOP/s calculation for the Intel Core i7-11800H (Tiger Lake-H).

Formula:  Peak FLOP/s = cores × frequency × FLOPs_per_cycle_per_core

FLOPs per cycle per core depends on SIMD width and FMA units:
  FLOPs/cycle/core = (vector_width_bits / dtype_bits) × FMA_units × 2

Tiger Lake (Willow Cove) execution units:
  - 2 × 512-bit FMA ports (ports 0 and 1)
  - AVX-512 and AVX2 both use these ports
  - Each FMA instruction = 1 multiply + 1 add = 2 FLOPs
"""

# ---------------------------------------------------------------------------
# CPU Specs – Intel Core i7-11800H (Tiger Lake-H, Willow Cove)
# ---------------------------------------------------------------------------
CORES        = 8
BASE_GHZ     = 2.3
TURBO_GHZ    = 4.6      # max single-core boost; all-core ~4.2-4.4 GHz
FMA_UNITS    = 2        # 2x 512-bit FMA units (ports 0 & 1)
BYTES_F64    = 8
BYTES_F32    = 4
BYTES_F16    = 2

SEP = "=" * 68
sep = "-" * 68

configs = [
    ("Scalar",   64,  BYTES_F64, "float64 (no SIMD)"),
    ("Scalar",   32,  BYTES_F32, "float32 (no SIMD)"),
    ("AVX2",    256,  BYTES_F64, "float64"),
    ("AVX2",    256,  BYTES_F32, "float32"),
    ("AVX-512", 512,  BYTES_F64, "float64"),
    ("AVX-512", 512,  BYTES_F32, "float32"),
    ("AVX-512", 512,  BYTES_F16, "float16 (bfloat16)"),
]

lines = [
    SEP,
    "Peak FLOP/s: Intel Core i7-11800H (Tiger Lake-H, Willow Cove)",
    SEP,
    f"  Cores            : {CORES}",
    f"  Base clock       : {BASE_GHZ} GHz",
    f"  Max turbo        : {TURBO_GHZ} GHz",
    f"  FMA units/core   : {FMA_UNITS} × 512-bit (ports 0 & 1)",
    f"  FLOPs per FMA    : 2  (1 multiply + 1 add)",
    "",
    "  Formula: cores × freq × (vec_bits / dtype_bits) × FMA_units × 2",
    "",
    sep,
    f"  {'ISA':<10} {'dtype':<22} {'FLOPs/cy/core':>14} {'Peak @ Base':>14} {'Peak @ Turbo':>14}",
    f"  {'───':<10} {'─────':<22} {'─────────────':>14} {'───────────':>14} {'────────────':>14}",
]

for isa, vec_bits, dtype_bytes, label in configs:
    if isa == "Scalar":
        elems    = 1          # scalar: 1 element per cycle
        fma_u    = 1          # scalar ops typically use 1 FMA unit
    else:
        elems    = vec_bits // (dtype_bytes * 8)
        fma_u    = FMA_UNITS

    flops_per_cycle = elems * fma_u * 2

    peak_base  = CORES * BASE_GHZ  * 1e9 * flops_per_cycle
    peak_turbo = CORES * TURBO_GHZ * 1e9 * flops_per_cycle

    def fmt(x):
        if x >= 1e12:
            return f"{x/1e12:.3f} TFLOP/s"
        return f"{x/1e9:.1f} GFLOP/s"

    lines.append(
        f"  {isa:<10} {f'{label}':<22} {flops_per_cycle:>14} {fmt(peak_base):>14} {fmt(peak_turbo):>14}"
    )

# ---------------------------------------------------------------------------
# Key figure for Kalman filter (float64, AVX-512, turbo)
# ---------------------------------------------------------------------------
elems_avx512_f64 = 512 // 64       # 8 doubles
flops_cy_avx512  = elems_avx512_f64 * FMA_UNITS * 2   # 32
peak_dp_base     = CORES * BASE_GHZ  * 1e9 * flops_cy_avx512
peak_dp_turbo    = CORES * TURBO_GHZ * 1e9 * flops_cy_avx512

lines += [
    "",
    SEP,
    "KEY FIGURE (relevant to Kalman filter, float64)",
    sep,
    f"  Peak DP FLOP/s @ base  = {CORES} cores × {BASE_GHZ} GHz × {flops_cy_avx512} FLOPs/cy",
    f"                         = {peak_dp_base/1e9:.1f} GFLOP/s",
    f"  Peak DP FLOP/s @ turbo = {CORES} cores × {TURBO_GHZ} GHz × {flops_cy_avx512} FLOPs/cy",
    f"                         = {peak_dp_turbo/1e9:.1f} GFLOP/s  ({peak_dp_turbo/1e12:.3f} TFLOP/s)",
    "",
]

# ---------------------------------------------------------------------------
# Effective FLOP/s achieved by our profiled Kalman filter
# (from profiling results: ~1.75 ms per 45-measurement run, warm runs)
# ---------------------------------------------------------------------------
FLOPS_PER_UPDATE  = 230          # from arithmetic_intensity.py
MEASUREMENTS      = 45
WARM_RUN_MS       = 1.75         # average warm-run wall time (ms)

time_per_update_s = (WARM_RUN_MS * 1e-3) / MEASUREMENTS
achieved_flops_s  = FLOPS_PER_UPDATE / time_per_update_s
efficiency_base   = achieved_flops_s / peak_dp_base * 100
efficiency_turbo  = achieved_flops_s / peak_dp_turbo * 100

lines += [
    sep,
    "ACHIEVED vs PEAK (from profiling: ~1.75 ms / 45 updates, warm runs)",
    sep,
    f"  FLOPs per update()     : {FLOPS_PER_UPDATE}",
    f"  Time per update()      : {time_per_update_s*1e6:.2f} µs  ({WARM_RUN_MS} ms / {MEASUREMENTS} updates)",
    f"  Achieved FLOP/s        : {achieved_flops_s/1e6:.2f} MFLOP/s",
    f"  Peak DP (base)         : {peak_dp_base/1e9:.1f} GFLOP/s",
    f"  Peak DP (turbo)        : {peak_dp_turbo/1e9:.1f} GFLOP/s",
    f"  Efficiency (vs base)   : {efficiency_base:.4f}%",
    f"  Efficiency (vs turbo)  : {efficiency_turbo:.4f}%",
    "",
    "  The filter achieves < 0.01% of peak — consistent with a",
    "  memory-bound, Python-overhead-dominated workload operating on",
    "  tiny (3×3) matrices that cannot exploit SIMD or multi-core.",
    SEP,
]

report = "\n".join(lines)
print(report)

out_path = "analysis/peak_flops.txt"
with open(out_path, "w") as f:
    f.write(report)
print(f"\nSaved to {out_path}")
