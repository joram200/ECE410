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
SW_GFLOPS_MEASURED  = 2.4082e-05   # from RVfpgaEL2_profiling/results/summary.txt
HW_GFLOPS_MEASURED  = 4.3276e-05   # from results/summary.txt AVG row

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
ax.loglog(HW_AI, HW_GFLOPS_MEASURED, 'r^', markersize=10,
          label=f'HW accelerator  ({HW_AI:.2f} FLOPs/B, {HW_GFLOPS_MEASURED:.2e} GFLOP/s)')

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
