"""
Arithmetic Intensity Analysis for the Basic Kalman Filter update() step.
Source: https://github.com/hmartiro/kalman-cpp

Arithmetic Intensity (AI) = FLOPs / Bytes of memory traffic

Problem dimensions (from kalman-test.cpp):
  n = 3  (state dimension)
  m = 1  (measurement dimension)
  dtype = float64  -> 8 bytes per element

The update() step performs:
  1. x_hat_new  = A  @ x_hat                        predict state
  2. P          = A  @ P @ A.T + Q                  predict covariance
  3. S          = C  @ P @ C.T + R                  innovation covariance
     K          = P  @ C.T @ inv(S)                 Kalman gain
  4. x_hat_new += K  @ (y - C @ x_hat_new)          correct state
  5. P          = (I - K @ C) @ P                   correct covariance
  6. x_hat      = x_hat_new                         store state
  7. t         += dt                                 advance time
"""

# ---------------------------------------------------------------------------
# Dimensions
# ---------------------------------------------------------------------------
n = 3          # state
m = 1          # measurement
B = 8          # bytes per float64

# ---------------------------------------------------------------------------
# FLOP counting
# Helper: exact FLOPs for (p x q) @ (q x r)  -> p*r*(2q-1)
# ---------------------------------------------------------------------------
def matmul_flops(p, q, r):
    """Multiplications + additions for a (p×q)·(q×r) matmul."""
    return p * r * (2 * q - 1)

def matadd_flops(p, q):
    """Element-wise add/sub for (p×q) matrices."""
    return p * q

steps = {}

# Step 1: x_hat_new = A @ x_hat   (n×n)·(n×1)
steps["1: x_hat_new = A @ x_hat"] = matmul_flops(n, n, 1)

# Step 2: P = A @ P @ A.T + Q
#   AP   = A @ P            (n×n)·(n×n)
#   APAT = AP @ A.T         (n×n)·(n×n)
#   P    = APAT + Q         (n×n) add
steps["2a: AP = A @ P"] = matmul_flops(n, n, n)
steps["2b: APAT = AP @ A.T"] = matmul_flops(n, n, n)
steps["2c: P = APAT + Q"] = matadd_flops(n, n)

# Step 3a: S = C @ P @ C.T + R
#   CP  = C @ P             (m×n)·(n×n)
#   CPC = CP @ C.T          (m×n)·(n×m)
#   S   = CPC + R           (m×m) add
steps["3a: CP = C @ P"] = matmul_flops(m, n, n)
steps["3b: CPC.T = CP @ C.T"] = matmul_flops(m, n, m)
steps["3c: S = CPC.T + R"] = matadd_flops(m, m)

# Step 3b: K = P @ C.T @ inv(S)
#   PCT    = P @ C.T        (n×n)·(n×m)
#   inv(S) for 1×1          1 division
#   K      = PCT / S        scalar multiply (n×m)·(m×m)
steps["3d: PCT = P @ C.T"] = matmul_flops(n, n, m)
steps["3e: inv(S)"] = 1                               # 1×1 inversion = 1 division
steps["3f: K = PCT @ inv(S)"] = matmul_flops(n, m, m)

# Step 4: x_hat_new += K @ (y - C @ x_hat_new)
#   Cx = C @ x_hat_new      (m×n)·(n×1)
#   innov = y - Cx           (m×1) sub
#   Kinnov = K @ innov       (n×m)·(m×1)
#   x_hat_new += Kinnov      (n×1) add
steps["4a: Cx = C @ x_hat_new"] = matmul_flops(m, n, 1)
steps["4b: innov = y - Cx"] = matadd_flops(m, 1)
steps["4c: K @ innov"] = matmul_flops(n, m, 1)
steps["4d: x_hat_new += ..."] = matadd_flops(n, 1)

# Step 5: P = (I - K @ C) @ P
#   KC   = K @ C            (n×m)·(m×n)
#   IKC  = I - KC            (n×n) sub
#   P    = IKC @ P           (n×n)·(n×n)
steps["5a: KC = K @ C"] = matmul_flops(n, m, n)
steps["5b: IKC = I - KC"] = matadd_flops(n, n)
steps["5c: P = IKC @ P"] = matmul_flops(n, n, n)

# Step 7: t += dt
steps["7: t += dt"] = 1

total_flops = sum(steps.values())

# ---------------------------------------------------------------------------
# Memory traffic counting (bytes)
# Two models:
#   (A) Ideal    – each persistent matrix read/written once; intermediates in registers
#   (B) Naive    – every intermediate array allocated and freed (numpy style)
# ---------------------------------------------------------------------------

# Persistent data sizes (elements)
sizes = dict(
    A     = n * n,   # 9
    C     = m * n,   # 3
    Q     = n * n,   # 9
    R     = m * m,   # 1
    P     = n * n,   # 9   (read + write)
    K     = n * m,   # 3   (write only)
    I     = n * n,   # 9
    x_hat = n,       # 3   (read + write)
    y     = m,       # 1
    dt    =  1,
    t     =  1,
)

# Model A: Ideal (each array touched exactly once total, R/W counted)
reads_ideal = dict(
    A=sizes["A"], C=sizes["C"], Q=sizes["Q"], R=sizes["R"],
    P=sizes["P"], I=sizes["I"], x_hat=sizes["x_hat"], y=sizes["y"],
    dt=sizes["dt"], t=sizes["t"],
)
writes_ideal = dict(P=sizes["P"], K=sizes["K"], x_hat=sizes["x_hat"], t=sizes["t"])

bytes_read_ideal  = sum(reads_ideal.values()) * B
bytes_write_ideal = sum(writes_ideal.values()) * B
bytes_ideal       = bytes_read_ideal + bytes_write_ideal

# Model B: Naive numpy – intermediates written to + read from DRAM
intermediates = {
    "x_hat_new (predict)" : n * 1,      # step 1 result
    "AP"                  : n * n,      # step 2a
    "CP"                  : m * n,      # step 3a
    "CPCT"                : m * m,      # step 3b
    "S_inv"               : m * m,      # step 3e
    "PCT"                 : n * m,      # step 3d
    "innov"               : m * 1,      # step 4b
    "Kinnov"              : n * 1,      # step 4c
    "KC"                  : n * n,      # step 5a
    "IKC"                 : n * n,      # step 5b
}
# Each intermediate is written once and read once
bytes_intermediates = sum(2 * v * B for v in intermediates.values())
bytes_naive         = bytes_ideal + bytes_intermediates

ai_ideal = total_flops / bytes_ideal
ai_naive = total_flops / bytes_naive

# ---------------------------------------------------------------------------
# Report
# ---------------------------------------------------------------------------
SEP = "=" * 68
sep = "-" * 68

lines = [
    SEP,
    "Arithmetic Intensity: Kalman Filter update()",
    "Source: https://github.com/hmartiro/kalman-cpp",
    f"State dim n={n}, Measurement dim m={m}, dtype=float64 ({B} bytes)",
    SEP,
    "",
    "FLOP COUNT PER update() CALL",
    sep,
    f"{'Operation':<40} {'FLOPs':>8}",
    f"{'─'*40} {'─'*8}",
]
for name, f in steps.items():
    lines.append(f"{name:<40} {f:>8}")
lines += [
    f"{'─'*40} {'─'*8}",
    f"{'TOTAL':.<40} {total_flops:>8}",
    "",
    "MEMORY TRAFFIC",
    sep,
    "Model A – Ideal (intermediates stay in registers/cache)",
    f"{'─'*40} {'─'*8}",
]
for k, v in reads_ideal.items():
    lines.append(f"  READ  {k:<34} {v*B:>6} B")
for k, v in writes_ideal.items():
    lines.append(f"  WRITE {k:<34} {v*B:>6} B")
lines += [
    f"  {'Total reads':.<38} {bytes_read_ideal:>6} B",
    f"  {'Total writes':.<38} {bytes_write_ideal:>6} B",
    f"  {'Total (ideal)':.<38} {bytes_ideal:>6} B",
    "",
    "Model B – Naive (numpy-style: intermediates go to DRAM)",
    f"{'─'*40} {'─'*8}",
    f"  {'Persistent data (same as ideal)':.<38} {bytes_ideal:>6} B",
]
for k, v in intermediates.items():
    lines.append(f"  TEMP  {k:<34} {2*v*B:>6} B  (read+write)")
lines += [
    f"  {'Total (naive)':.<38} {bytes_naive:>6} B",
    "",
    "ARITHMETIC INTENSITY",
    sep,
    f"  AI (ideal) = {total_flops} FLOPs / {bytes_ideal} B = {ai_ideal:.4f} FLOPs/byte",
    f"  AI (naive) = {total_flops} FLOPs / {bytes_naive} B = {ai_naive:.4f} FLOPs/byte",
    "",
    "INTERPRETATION",
    sep,
    "  Both models yield AI << 1 FLOPs/byte, placing the Kalman filter",
    "  squarely in the MEMORY-BOUND region of the Roofline model.",
    "  For reference, modern CPUs achieve ~10–100 FLOPs/byte of peak",
    "  compute-to-bandwidth ratio; the ridge point lies well above this AI.",
    "",
    "  Performance is limited by memory bandwidth, not arithmetic throughput.",
    "  Bottleneck is the repeated read/write of the 3×3 P covariance matrix",
    "  across five distinct sub-expressions in a single update step.",
    SEP,
]

report = "\n".join(lines)
print(report)

out_path = "analysis/arithmetic_intensity.txt"
with open(out_path, "w") as f:
    f.write(report)
print(f"\nSaved to {out_path}")
