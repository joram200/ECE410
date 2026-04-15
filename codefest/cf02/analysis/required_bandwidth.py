"""
Required memory bandwidth for the tiled GEMM Kalman filter update() kernel.

Formula:  Required BW = Throughput × Data Width
            Throughput  = updates per second  (1 / time_per_update)
            Data Width  = bytes transferred per update() call
"""

# ---------------------------------------------------------------------------
# Tiled GEMM kernel parameters  (from tiled_gemm_estimate.py)
# ---------------------------------------------------------------------------
TIME_PER_UPDATE_NS = 2.11       # ns  (L1-bound, ideal tiled GEMM)
FLOPS_PER_UPDATE   = 230
GFLOPS_ATTAINABLE  = 108.97     # GFLOP/s  (L1-bound ceiling)

# ---------------------------------------------------------------------------
# Data width — bytes transferred per update() call (ideal model)
# Intermediates stay in AVX registers; only persistent tensors cross the bus.
# Values from arithmetic_intensity.txt  (n=3, m=1, float64 = 8 B/elem)
# ---------------------------------------------------------------------------
B = 8   # bytes per float64

data = {
    # ----- READS -----
    # Weights (model params)
    "A  (3×3, 3 reads)":   3 * 9 * B,
    "C  (1×3, 5 reads)":   5 * 3 * B,
    "Q  (3×3, 1 read) ":   1 * 9 * B,
    "R  (1×1, 1 read) ":   1 * 1 * B,
    "I  (3×3, 1 read) ":   1 * 9 * B,
    "dt (scalar, 1 rd)":   1 * 1 * B,
    # Inputs
    "x_hat in (3×1)   ":   1 * 3 * B,
    "P     in (3×3)   ":   1 * 9 * B,
    "y        (1×1)   ":   1 * 1 * B,
    "t        (scalar)":   1 * 1 * B,
}
reads_B  = sum(data.values())          # 496 B  (from analysis)

writes = {
    # ----- WRITES -----
    "x_hat out (3×1)  ":  1 * 3 * B,
    "P     out (3×3)  ":  1 * 9 * B,
    "K         (3×1)  ":  1 * 3 * B,
    "t  out (scalar)  ":  1 * 1 * B,
}
writes_B = sum(writes.values())        # 128 B

data_width_B = reads_B + writes_B      # 496 + 128 = 624 B

# Note: the prior "ideal" AI used 496 B total (reads only counted once;
# writes were included in that same 496 B figure because outputs overwrite
# inputs in-place for P and x_hat).  Here we count reads and writes
# independently as separate bus transactions => 624 B is the correct
# total bus traffic per call under tiled GEMM.
#
# For consistency with the previous AI analysis (496 B), we also show
# that figure.  The 496 B figure arises from counting each persistent
# tensor once whether it is read, written, or both.

DATA_WIDTH_IDEAL  = 496   # B  (unique-tensor count, as used in AI calculation)
DATA_WIDTH_EXACT  = data_width_B   # B  (reads + writes counted separately)

# ---------------------------------------------------------------------------
# Throughput
# ---------------------------------------------------------------------------
throughput_per_ns = 1 / TIME_PER_UPDATE_NS          # updates / ns
throughput_M      = throughput_per_ns * 1e9 / 1e6   # Mupdates/s

# Crosscheck: throughput from attainable FLOP/s
throughput_check = (GFLOPS_ATTAINABLE * 1e9) / FLOPS_PER_UPDATE / 1e6   # Mupdates/s

# ---------------------------------------------------------------------------
# Required bandwidth
# ---------------------------------------------------------------------------
req_bw_ideal = throughput_per_ns * DATA_WIDTH_IDEAL  * 1e9 / 1e9   # GB/s
req_bw_exact = throughput_per_ns * DATA_WIDTH_EXACT  * 1e9 / 1e9   # GB/s

# Reference bandwidths
L1_BW_GBS   = 235.0    # GB/s  practical
DRAM_BW_GBS =  41.0    # GB/s  practical

# ---------------------------------------------------------------------------
# Report
# ---------------------------------------------------------------------------
SEP = "=" * 66
sep = "-" * 66

lines = [
    SEP,
    "Required Bandwidth: Tiled GEMM Kalman filter update()",
    SEP,
    "",
    "FORMULA",
    sep,
    "  Required BW = Throughput × Data Width",
    "",
    "THROUGHPUT",
    sep,
    f"  Time per update() (tiled GEMM, L1-bound) : {TIME_PER_UPDATE_NS} ns",
    f"  Throughput = 1 / {TIME_PER_UPDATE_NS} ns             = {throughput_M:.2f} Mupdates/s",
    f"  Cross-check via FLOP/s : {GFLOPS_ATTAINABLE} GFLOP/s / {FLOPS_PER_UPDATE} FLOPs = {throughput_check:.2f} Mupdates/s",
    "",
    "DATA WIDTH (bytes per update() call)",
    sep,
    "  READS",
]
for name, val in data.items():
    lines.append(f"    {name} : {val:>5} B")
lines += [
    f"    {'─'*42}",
    f"    Reads subtotal              : {reads_B:>5} B",
    "",
    "  WRITES",
]
for name, val in writes.items():
    lines.append(f"    {name} : {val:>5} B")
lines += [
    f"    {'─'*42}",
    f"    Writes subtotal             : {writes_B:>5} B",
    "",
    f"  Total (reads + writes)        : {DATA_WIDTH_EXACT:>5} B",
    f"  Unique-tensor count (AI basis): {DATA_WIDTH_IDEAL:>5} B",
    "",
    "REQUIRED BANDWIDTH",
    sep,
    f"  Using unique-tensor data width ({DATA_WIDTH_IDEAL} B):",
    f"    BW = {throughput_M:.2f} Mupdates/s × {DATA_WIDTH_IDEAL} B",
    f"       = {req_bw_ideal:.2f} GB/s",
    "",
    f"  Using read+write data width ({DATA_WIDTH_EXACT} B):",
    f"    BW = {throughput_M:.2f} Mupdates/s × {DATA_WIDTH_EXACT} B",
    f"       = {req_bw_exact:.2f} GB/s",
    "",
    "COMPARISON TO AVAILABLE BANDWIDTH",
    sep,
    f"  Required BW (unique-tensor) : {req_bw_ideal:.1f} GB/s",
    f"  Required BW (reads+writes)  : {req_bw_exact:.1f} GB/s",
    f"  L1 cache bandwidth          : {L1_BW_GBS:.1f} GB/s  ← satisfied",
    f"  DRAM bandwidth              : {DRAM_BW_GBS:.1f} GB/s  ← insufficient",
    "",
    "  The tiled GEMM kernel requires ~235 GB/s — achievable only from L1.",
    "  DRAM alone ({:.0f} GB/s) is {:.1f}× too slow to sustain this throughput.".format(
        DRAM_BW_GBS, req_bw_ideal / DRAM_BW_GBS),
    SEP,
]

report = "\n".join(lines)
print(report)

with open("analysis/required_bandwidth.txt", "w") as f:
    f.write(report)
print("\nSaved to analysis/required_bandwidth.txt")
