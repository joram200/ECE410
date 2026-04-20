"""
Roofline model for CF03 GEMM kernels on RTX 3070 Mobile.
Saves codefest/cf03/profiling/roofline.png
"""
import numpy as np
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches

# ── Machine limits (RTX 3070 Mobile, GA104M) ──────────────────────────────────
PEAK_COMPUTE_GFLOPS = 16_590.0   # FP32, GFLOP/s
PEAK_BW_GBS         =    448.0   # GDDR6, GB/s
RIDGE_POINT         = PEAK_COMPUTE_GFLOPS / PEAK_BW_GBS   # FLOP/byte

# ── Measured kernel data ──────────────────────────────────────────────────────
# Arithmetic intensity = achieved GFLOP/s / achieved DRAM BW (GB/s)
kernels = [
    {
        "name":   "gemm_naive\n(32×32 blocks)",
        "ai":     839.0  / 44.3,   # 18.9 FLOP/byte
        "perf":   839.0,           # GFLOP/s
        "color":  "#E84040",
        "marker": "o",
        "label_offset": (0.35, 0.12),   # (x_mul, y_mul relative to point)
    },
    {
        "name":   "gemm_tiled\n(tile = 8)",
        "ai":     985.0  / 37.3,   # 26.4 FLOP/byte
        "perf":   985.0,           # GFLOP/s
        "color":  "#3A7FD5",
        "marker": "s",
        "label_offset": (1.6, 2.8),
    },
]

# ── Build roofline curve ──────────────────────────────────────────────────────
ai_range = np.logspace(-2, 3, 1000)   # 0.01 → 1000 FLOP/byte

def roofline(ai):
    return np.minimum(ai * PEAK_BW_GBS, PEAK_COMPUTE_GFLOPS)

# ── Plot ──────────────────────────────────────────────────────────────────────
fig, ax = plt.subplots(figsize=(9, 6))
fig.patch.set_facecolor("#1A1A2E")
ax.set_facecolor("#1A1A2E")

# Grid
ax.set_xscale("log")
ax.set_yscale("log")
ax.grid(True, which="both", color="#333355", linewidth=0.6, linestyle="--")
ax.tick_params(colors="white", which="both")
for spine in ax.spines.values():
    spine.set_edgecolor("#555577")

# Roofline
ax.plot(ai_range, roofline(ai_range),
        color="#AAAACC", linewidth=2.2, zorder=2, label="Roofline (RTX 3070 Mobile)")

# Annotate ridge point
ax.axvline(RIDGE_POINT, color="#AAAACC", linewidth=1.0,
           linestyle=":", alpha=0.7)
ax.text(RIDGE_POINT * 1.08, 200,
        f"Ridge\n{RIDGE_POINT:.1f} FLOP/byte",
        color="#CCCCDD", fontsize=8.5, va="bottom")

# Memory-bound slope label
slope_ai = 0.06
ax.text(slope_ai, slope_ai * PEAK_BW_GBS * 1.35,
        f"Mem BW ceiling\n{PEAK_BW_GBS:.0f} GB/s",
        color="#AAAACC", fontsize=8, rotation=38, va="bottom")

# Compute ceiling label
ax.text(300, PEAK_COMPUTE_GFLOPS * 1.08,
        f"Compute ceiling  {PEAK_COMPUTE_GFLOPS/1e3:.2f} TFLOP/s",
        color="#AAAACC", fontsize=8.5, ha="right")

# Kernels
for k in kernels:
    ax.scatter(k["ai"], k["perf"],
               color=k["color"], marker=k["marker"],
               s=130, zorder=5, edgecolors="white", linewidths=0.8)
    # Annotation offset: nudge label up-right
    ox, oy = k["label_offset"]
    ax.annotate(
        f"{k['name']}\n{k['ai']:.1f} FLOP/byte\n{k['perf']:.0f} GFLOP/s",
        xy=(k["ai"], k["perf"]),
        xytext=(k["ai"] * ox, k["perf"] * oy),
        color=k["color"], fontsize=8.5,
        arrowprops=dict(arrowstyle="-", color=k["color"],
                        lw=1.0, alpha=0.7),
    )

# Axes
ax.set_xlabel("Arithmetic Intensity  [FLOP / byte]",
              color="white", fontsize=11, labelpad=8)
ax.set_ylabel("Performance  [GFLOP/s]",
              color="white", fontsize=11, labelpad=8)
ax.set_title("Roofline Model — 1024×1024 FP32 GEMM\nNVIDIA GeForce RTX 3070 Mobile (GA104M, SM 8.6)",
             color="white", fontsize=12, pad=12)

ax.set_xlim(0.05, 800)
ax.set_ylim(5, 80_000)
ax.xaxis.set_tick_params(labelcolor="white")
ax.yaxis.set_tick_params(labelcolor="white")

# Legend
legend_handles = [
    mpatches.Patch(color="#AAAACC", label="Roofline (RTX 3070 Mobile)"),
] + [
    plt.Line2D([0], [0], marker=k["marker"], color="w",
               markerfacecolor=k["color"], markersize=9,
               label=k["name"].replace("\n", " "))
    for k in kernels
]
ax.legend(handles=legend_handles, facecolor="#2A2A4A",
          edgecolor="#555577", labelcolor="white", fontsize=9,
          loc="upper left")

plt.tight_layout()
out = "codefest/cf03/profiling/roofline.png"
plt.savefig(out, dpi=150, bbox_inches="tight", facecolor=fig.get_facecolor())
print(f"Saved → {out}")
