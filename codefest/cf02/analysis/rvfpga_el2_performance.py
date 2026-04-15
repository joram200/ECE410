"""
Peak FLOP/s and Memory Bandwidth for RVfpgaEL2 on Nexys A7.

Platform:
  Core   : SweRV EL2 (VeeR EL2) RISC-V
  Board  : Digilent Nexys A7-100T  (Artix-7 XC7A100T FPGA)
  FPGA clock target: 50 MHz (VeeRwolf / RVfpga default)

ISA: RV32IMC  (Integer, Multiply/Divide, Compressed)
  *** No hardware FPU in the standard RVfpga EL2 build.
      F / D extensions are commercial Codasip add-ons.
      All floating-point is emulated in software. ***

References:
  - VeeRwolf / Cores-VeeR-EL2 GitHub (chipsalliance)
  - RVfpga teaching package (Imagination Technologies / TechRxiv)
  - Digilent Nexys A7 Reference Manual
  - Micron MT47H64M16HR-25 DDR2 datasheet
"""

SEP = "=" * 68
sep = "-" * 68

# ---------------------------------------------------------------------------
# Platform constants
# ---------------------------------------------------------------------------
CORE_HZ        = 50e6      # 50 MHz FPGA clock
CORES          = 1
ISSUE_WIDTH    = 1         # single-issue, in-order, 4-stage pipeline
B              = 4         # 32-bit (float32 / int32) = 4 bytes

# DCCM (Data Closely Coupled Memory) — FPGA BRAM
DCCM_BUS_BITS  = 64        # 64-bit AXI4 data bus to DCCM
DCCM_BUS_BYTES = DCCM_BUS_BITS // 8

# DDR2 — MT47H64M16HR-25 (16-bit, 667 MT/s per pin, DDR2-667)
DDR2_RATE_MTS  = 667e6     # transfers per second (double data rate)
DDR2_WIDTH_B   = 16 // 8   # 16-bit = 2 bytes

# ---------------------------------------------------------------------------
# Peak integer throughput
# ---------------------------------------------------------------------------
peak_iops = CORES * CORE_HZ * ISSUE_WIDTH   # instructions per second

# ---------------------------------------------------------------------------
# Peak FLOP/s
# ---------------------------------------------------------------------------

# --- Case A: No FPU (standard RVfpga EL2 build, RV32IMC only) ---
# Floating-point must be emulated via libgcc soft-float.
# Typical SP FP op costs (conservative estimates from RISC-V soft-fp):
SOFTFP_FMUL_CYCLES = 40    # ~40 integer instructions per FMUL.S
SOFTFP_FADD_CYCLES = 30    # ~30 integer instructions per FADD.S
# FMADD.S = FMUL + FADD in software (sequential) ≈ 70 cycles, producing 2 FLOPs
SOFTFP_FMADD_CYCLES = SOFTFP_FMUL_CYCLES + SOFTFP_FADD_CYCLES

softfp_fmadd_per_sec = CORE_HZ / SOFTFP_FMADD_CYCLES
peak_flops_softfp    = softfp_fmadd_per_sec * 2    # 2 FLOPs per FMADD

# --- Case B: Hypothetical hardware FPU (F extension, 1 FMADD/cycle) ---
# If the F extension were present (Codasip add-on or custom):
#   - Single-precision, 1 FMADD per cycle throughput = 2 FLOPs/cycle
HW_FPU_FMADD_PER_CYCLE = 1
HW_FPU_FLOPS_PER_FMADD = 2
peak_flops_hwfp = (CORES * CORE_HZ *
                   HW_FPU_FMADD_PER_CYCLE * HW_FPU_FLOPS_PER_FMADD)

# ---------------------------------------------------------------------------
# Peak memory bandwidth
# ---------------------------------------------------------------------------

# 1. DCCM (on-chip BRAM, 1 access per cycle at full clock)
bw_dccm_read  = CORE_HZ * DCCM_BUS_BYTES   # bytes/s
bw_dccm_write = CORE_HZ * DCCM_BUS_BYTES
bw_dccm_total = bw_dccm_read + bw_dccm_write  # if dual-port

# 2. DDR2 theoretical (MT47H64M16HR-25, no memory controller overhead)
bw_ddr2_theoretical = DDR2_RATE_MTS * DDR2_WIDTH_B   # bytes/s
# Practical: FPGA MIG adds ~40-60% overhead on small transfers;
#            assume ~50% efficiency for realistic burst transfers
DDR2_EFFICIENCY     = 0.50
bw_ddr2_practical   = bw_ddr2_theoretical * DDR2_EFFICIENCY

def fmt_bw(bps):
    if bps >= 1e9:
        return f"{bps/1e9:.3f} GB/s"
    return f"{bps/1e6:.1f} MB/s"

def fmt_flops(f):
    if f >= 1e9:
        return f"{f/1e9:.3f} GFLOP/s"
    if f >= 1e6:
        return f"{f/1e6:.2f} MFLOP/s"
    return f"{f/1e3:.1f} kFLOP/s"

# ---------------------------------------------------------------------------
# Arithmetic intensity at this platform's ridge points
# ---------------------------------------------------------------------------
# Ridge point = Peak FLOP/s / Peak BW  (FLOPs/byte at the knee of roofline)
ridge_softfp_dccm = peak_flops_softfp / bw_dccm_read
ridge_hwfp_dccm   = peak_flops_hwfp   / bw_dccm_read
ridge_hwfp_ddr2   = peak_flops_hwfp   / bw_ddr2_practical

# ---------------------------------------------------------------------------
# Kalman filter context
# ---------------------------------------------------------------------------
KF_FLOPS_PER_UPDATE  = 230     # from arithmetic_intensity.py
KF_AI_IDEAL          = 0.4637  # FLOPs/byte (ideal, from prior analysis)

# Time to execute one update on RVfpgaEL2 (software FP):
kf_update_cycles_soft  = KF_FLOPS_PER_UPDATE / 2 * SOFTFP_FMADD_CYCLES
kf_update_time_soft_us = kf_update_cycles_soft / CORE_HZ * 1e6

# ---------------------------------------------------------------------------
# Report
# ---------------------------------------------------------------------------
lines = [
    SEP,
    "Peak FLOP/s & Memory Bandwidth: RVfpgaEL2 on Nexys A7",
    SEP,
    "PLATFORM",
    sep,
    f"  Core            : SweRV EL2 (VeeR EL2), in-order, 4-stage, single-issue",
    f"  FPGA            : Xilinx Artix-7 XC7A100T  (Nexys A7-100T)",
    f"  Clock frequency : {CORE_HZ/1e6:.0f} MHz  (VeeRwolf / RVfpga default)",
    f"  ISA             : RV32IMC  (NO hardware FPU in standard RVfpga build)",
    f"  DCCM            : 32–64 KB, 64-bit AXI4 bus",
    f"  DDR2            : MT47H64M16HR-25, 16-bit, 667 MT/s",
    "",
    SEP,
    "PEAK INTEGER THROUGHPUT",
    sep,
    f"  {CORES} core × {CORE_HZ/1e6:.0f} MHz × {ISSUE_WIDTH} issue/cycle",
    f"  = {peak_iops/1e6:.0f} MIPS",
    "",
    SEP,
    "PEAK FLOP/s",
    sep,
    "Case A — Standard RVfpga EL2  (RV32IMC, software FP emulation)",
    f"  {'Soft FMADD cost':.<40} ~{SOFTFP_FMADD_CYCLES} integer instructions",
    f"  {'FMADDs per second':.<40} {softfp_fmadd_per_sec/1e3:.1f} k/s",
    f"  {'Peak SP FLOP/s (soft-float)':.<40} {fmt_flops(peak_flops_softfp)}",
    "",
    "Case B — Hypothetical hardware FPU  (F extension, 1 FMADD/cycle)",
    f"  {'FLOPs per cycle per core':.<40} {HW_FPU_FMADD_PER_CYCLE * HW_FPU_FLOPS_PER_FMADD}",
    f"  {'Peak SP FLOP/s (hw FPU)':.<40} {fmt_flops(peak_flops_hwfp)}",
    "",
    SEP,
    "MEMORY BANDWIDTH",
    sep,
    "1. DCCM (on-chip BRAM, 64-bit AXI4)",
    f"   {'Read  (1 bus transfer/cycle)':.<40} {fmt_bw(bw_dccm_read)}",
    f"   {'Write (1 bus transfer/cycle)':.<40} {fmt_bw(bw_dccm_write)}",
    f"   {'Combined (dual-port peak)':.<40} {fmt_bw(bw_dccm_total)}",
    "",
    "2. DDR2  (MT47H64M16HR-25, 16-bit × 667 MT/s)",
    f"   {'Theoretical peak':.<40} {fmt_bw(bw_ddr2_theoretical)}",
    f"   {'Practical (~{:.0f}% MIG efficiency)'.format(DDR2_EFFICIENCY*100):<40} {fmt_bw(bw_ddr2_practical)}",
    "",
    SEP,
    "ROOFLINE RIDGE POINTS  (AI = Peak FLOP/s / Peak BW)",
    sep,
    f"  Soft-FP  vs DCCM (read)   : {ridge_softfp_dccm:.4f} FLOPs/byte",
    f"  HW-FPU   vs DCCM (read)   : {ridge_hwfp_dccm:.4f} FLOPs/byte",
    f"  HW-FPU   vs DDR2 (pract.) : {ridge_hwfp_ddr2:.4f} FLOPs/byte",
    "",
    SEP,
    "KALMAN FILTER CONTEXT",
    sep,
    f"  KF update() FLOPs         : {KF_FLOPS_PER_UPDATE}",
    f"  KF arithmetic intensity   : {KF_AI_IDEAL:.4f} FLOPs/byte (ideal)",
    "",
    "  Estimated update() time on RVfpgaEL2 (soft-float):",
    f"    ~{KF_FLOPS_PER_UPDATE}/2 FMADDs × {SOFTFP_FMADD_CYCLES} cycles = {kf_update_cycles_soft:.0f} cycles",
    f"    @ {CORE_HZ/1e6:.0f} MHz → {kf_update_time_soft_us:.2f} µs  (~{kf_update_time_soft_us/1000:.2f} ms)",
    "",
    "  Compare: i7-11800H achieved ~38.89 µs/update (Python/numpy)",
    f"           RVfpgaEL2 estimate: ~{kf_update_time_soft_us:.0f} µs/update (soft-float C)",
    f"           Slowdown factor   : ~{kf_update_time_soft_us/38.89:.0f}×",
    "",
    "  Note: KF AI (0.46 FLOPs/byte) is ABOVE the ridge point for soft-FP",
    "  on DCCM, meaning the filter is compute-bound on RVfpgaEL2 (not",
    "  memory-bound), unlike on the i7-11800H.",
    SEP,
]

report = "\n".join(lines)
print(report)

out_path = "analysis/rvfpga_el2_performance.txt"
with open(out_path, "w") as f:
    f.write(report)
print(f"\nSaved to {out_path}")
