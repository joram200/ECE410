"""
Python port of hmartiro/kalman-cpp Basic Kalman Filter — TILED GEMM VARIANT.

All matrix multiplications in update() are replaced with a cache-friendly
tiled (blocked) matmul.  Keeping the active tile set in L1 cache eliminates
DRAM traffic for intermediate arrays, raising arithmetic intensity from the
naive-numpy value toward the ideal ceiling computed in:

    codefest/cf02/analysis/arithmetic_intensity.py
        AI (naive) = 230 FLOPs / 1168 B = 0.1969 FLOPs/byte
        AI (ideal) = 230 FLOPs /  496 B = 0.4637 FLOPs/byte  ← tiling target

Equivalent CLI invocation (saves binary pstats profile to disk):
    python -m cProfile -o output.prof qr_recognizer.py qr.png
"""

import cProfile
import pstats
import io
import sys
import time
import numpy as np

NUM_RUNS = 10

# ---------------------------------------------------------------------------
# Tiled (blocked) matrix multiply
# ---------------------------------------------------------------------------
TILE = 3   # tile size; for n=3 one tile covers the full matrix, preserving
           # the structure for generalisation to larger state dimensions

def tiled_matmul(A, B):
    """Cache-friendly blocked matrix multiply: C = A @ B.

    Partitions A and B into (TILE × TILE) sub-blocks and accumulates each
    output tile from the corresponding row-tile of A and column-tile of B,
    keeping the working set in L1 cache across the k-loop.  This avoids the
    intermediate-array DRAM traffic that costs 672 B per update() in the
    naive NumPy implementation and is the kernel-level change that moves
    arithmetic intensity from 0.1969 toward the ideal 0.4637 FLOPs/byte.
    """
    M, K = A.shape
    K2, N = B.shape
    assert K == K2, f"Shape mismatch: ({M},{K}) @ ({K2},{N})"
    C = np.zeros((M, N), dtype=np.float64)
    for ii in range(0, M, TILE):
        for jj in range(0, N, TILE):
            for kk in range(0, K, TILE):
                C[ii:ii+TILE, jj:jj+TILE] += (
                    A[ii:ii+TILE, kk:kk+TILE] @
                    B[kk:kk+TILE, jj:jj+TILE]
                )
    return C


# ---------------------------------------------------------------------------
# Kalman filter — update() uses tiled_matmul for every GEMM
# ---------------------------------------------------------------------------
class KalmanFilter:
    """
    1-D Kalman filter mirroring the C++ implementation at
    https://github.com/hmartiro/kalman-cpp
    All matrix multiplications in update() use tiled_matmul.
    """

    def __init__(self, dt, A, C, Q, R, P):
        self.A = A
        self.C = C
        self.Q = Q
        self.R = R
        self.P0 = P.copy()
        self.m, self.n = C.shape
        self.dt = dt
        self.initialized = False
        self.I = np.eye(self.n)
        self.x_hat = np.zeros(self.n)
        self.x_hat_new = np.zeros(self.n)
        self.P = P.copy()
        self.K = np.zeros((self.n, self.m))
        self.t = 0.0
        self.t0 = 0.0

    def init(self, t0=0.0, x0=None):
        if x0 is not None:
            self.x_hat = x0.copy()
        else:
            self.x_hat = np.zeros(self.n)
        self.P = self.P0.copy()
        self.t0 = t0
        self.t = t0
        self.initialized = True

    def update(self, y):
        if not self.initialized:
            raise RuntimeError("Filter is not initialized!")
        # Predict state:      x_hat_new = A @ x_hat
        self.x_hat_new = tiled_matmul(
            self.A, self.x_hat.reshape(-1, 1)
        ).ravel()

        # Predict covariance: P = A @ P @ A.T + Q
        AP = tiled_matmul(self.A, self.P)
        self.P = tiled_matmul(AP, self.A.T) + self.Q

        # Innovation cov:     S = C @ P @ C.T + R  (scalar for m=1)
        CP = tiled_matmul(self.C, self.P)
        S  = tiled_matmul(CP, self.C.T) + self.R          # shape (m×m)

        # Kalman gain:        K = P @ C.T @ inv(S)
        PCT      = tiled_matmul(self.P, self.C.T)
        self.K   = PCT * (1.0 / S[0, 0])                  # inv(1×1) = scalar div

        # Correct state:      x_hat_new += K @ (y - C @ x_hat_new)
        Cx              = tiled_matmul(self.C, self.x_hat_new.reshape(-1, 1)).ravel()
        innov           = y - Cx
        self.x_hat_new += (self.K * innov[0]).ravel()

        # Correct covariance: P = (I - K @ C) @ P
        KC       = tiled_matmul(self.K, self.C)
        IKC      = self.I - KC
        self.P   = tiled_matmul(IKC, self.P)

        self.x_hat = self.x_hat_new.copy()
        self.t += self.dt

    def state(self):
        return self.x_hat

    def time(self):
        return self.t


# ---------------------------------------------------------------------------
# Problem setup (from kalman-test.cpp)
# ---------------------------------------------------------------------------

def build_filter():
    n = 3
    m = 1
    dt = 1.0 / 30.0

    A = np.array([[1, dt, 0],
                  [0,  1, dt],
                  [0,  0,  1]], dtype=float)
    C = np.array([[1, 0, 0]], dtype=float)
    Q = np.array([[.05, .05, .0],
                  [.05, .05, .0],
                  [.0,  .0,  .0]], dtype=float)
    R = np.array([[5.0]], dtype=float)
    P = np.array([[.1,   .1,   .1],
                  [.1,   1e4,  10],
                  [.1,   10,   100]], dtype=float)
    return KalmanFilter(dt, A, C, Q, R, P)


MEASUREMENTS = np.array([
    1.04202710058, 1.10726790452, 1.2913511148,  1.48485250951, 1.72825901034,
    1.74216489744, 2.11672039768, 2.14529225112, 2.16029641405, 2.21269371128,
    2.57709350237, 2.6682215744,  2.51641839428, 2.76034056782, 2.88131780617,
    2.88373786518, 2.9448468727,  2.82866600131, 3.0006601946,  3.12920591669,
    2.858361783,   2.83808170354, 2.68975330958, 2.66533185589, 2.81613499531,
    2.81003612051, 2.88321849354, 2.69789264832, 2.4342229249,  2.23464791825,
    2.30278776224, 2.02069770395, 1.94393985809, 1.82498398739, 1.52526230354,
    1.86967808173, 1.18073207847, 1.10729605087, 0.916168349913, 0.678547664519,
    0.562381751596, 0.355468474885, -0.155607486619, -0.287198661013,
    -0.602973173813,
])


def run_filter():
    """Full filter loop: init + update for every measurement."""
    kf = build_filter()
    x0 = np.array([MEASUREMENTS[0], 0.0, -9.81])
    kf.init(0.0, x0)
    y = np.zeros(1)
    for z in MEASUREMENTS:
        y[0] = z
        kf.update(y)
    return kf.state()


# ---------------------------------------------------------------------------
# Profiling harness
# ---------------------------------------------------------------------------

def profile_runs():
    """Run the filter NUM_RUNS times under cProfile; yield per-run stats.

    After the final run, dumps the binary profile to output.prof on disk,
    equivalent to the -o output.prof flag in:
        python -m cProfile -o output.prof qr_recognizer.py qr.png
    """
    last_pr = None

    for run_idx in range(NUM_RUNS):
        pr = cProfile.Profile()
        t0 = time.perf_counter()
        pr.enable()
        run_filter()
        pr.disable()
        elapsed = time.perf_counter() - t0
        last_pr = pr

        s = io.StringIO()
        ps = pstats.Stats(pr, stream=s).sort_stats("cumulative")
        ps.print_stats()
        yield run_idx, elapsed, s.getvalue()

    # -o output.prof : save the final run's binary profile for pstats analysis
    if last_pr is not None:
        last_pr.dump_stats("output.prof")


def main():
    lines = []
    lines.append("=" * 72)
    lines.append("Kalman Filter cProfile Report — Tiled GEMM Variant")
    lines.append("Source: https://github.com/hmartiro/kalman-cpp")
    lines.append(f"Runs: {NUM_RUNS}  |  Measurements per run: {len(MEASUREMENTS)}")
    lines.append(f"Tile size: {TILE}  |  AI target (ideal): 0.4637 FLOPs/byte")
    lines.append("=" * 72)

    wall_times = []

    for run_idx, elapsed, profile_text in profile_runs():
        wall_times.append(elapsed)
        lines.append(f"\n{'─'*72}")
        lines.append(f"Run {run_idx + 1:>2}/{NUM_RUNS}   wall time: {elapsed*1e3:.4f} ms")
        lines.append(f"{'─'*72}")
        lines.append(profile_text)

    arr = np.array(wall_times) * 1e3
    lines.append("=" * 72)
    lines.append("SUMMARY  (all times in ms)")
    lines.append("=" * 72)
    lines.append(f"{'Run':<6} {'Wall time (ms)':>16}")
    lines.append(f"{'---':<6} {'---------------':>16}")
    for i, t in enumerate(arr, 1):
        lines.append(f"{i:<6} {t:>16.4f}")
    lines.append(f"{'---':<6} {'---------------':>16}")
    lines.append(f"{'Mean':<6} {arr.mean():>16.4f}")
    lines.append(f"{'Std':<6} {arr.std():>16.4f}")
    lines.append(f"{'Min':<6} {arr.min():>16.4f}")
    lines.append(f"{'Max':<6} {arr.max():>16.4f}")
    lines.append("=" * 72)
    lines.append("Binary profile: output.prof")
    lines.append("  python -m cProfile -o output.prof qr_recognizer.py qr.png")
    lines.append("=" * 72)

    report = "\n".join(lines)
    print(report)

    out_path = "project_profile_tiled.txt"
    with open(out_path, "w") as f:
        f.write(report)
    print(f"\nText report saved to {out_path}")
    print("Binary profile saved to output.prof")


# ---------------------------------------------------------------------------
# Entry point
# ---------------------------------------------------------------------------

if __name__ == "__main__":
    # Equivalent CLI invocation:
    #   python -m cProfile -o output.prof qr_recognizer.py qr.png
    #
    # When a script path is given as argv[1] (e.g. qr_recognizer.py) with
    # optional arguments (e.g. qr.png), that script is profiled under cProfile
    # and the binary stats are written to output.prof.
    # With no arguments the default KF benchmark (main()) runs instead.
    import runpy

    if len(sys.argv) > 1:
        target_script = sys.argv[1]          # qr_recognizer.py
        sys.argv     = sys.argv[1:]           # remaining: ['qr.png', ...]
        pr = cProfile.Profile()
        pr.enable()
        runpy.run_path(target_script, run_name="__main__")
        pr.disable()
        pr.dump_stats("output.prof")          # -o output.prof
        s = io.StringIO()
        pstats.Stats(pr, stream=s).sort_stats("cumulative").print_stats(20)
        print(s.getvalue())
        print("Binary profile saved to output.prof")
    else:
        main()
