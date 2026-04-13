"""
Python port of hmartiro/kalman-cpp Basic Kalman Filter.
Profiles execution time per loop across NUM_RUNS runs using cProfile.
"""

import cProfile
import pstats
import io
import time
import numpy as np

NUM_RUNS = 10


class KalmanFilter:
    """
    1-D Kalman filter mirroring the C++ implementation at
    https://github.com/hmartiro/kalman-cpp
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
        # Predict
        self.x_hat_new = self.A @ self.x_hat
        self.P = self.A @ self.P @ self.A.T + self.Q
        # Kalman gain
        S = self.C @ self.P @ self.C.T + self.R
        self.K = self.P @ self.C.T @ np.linalg.inv(S)
        # Correct
        self.x_hat_new += self.K @ (y - self.C @ self.x_hat_new)
        self.P = (self.I - self.K @ self.C) @ self.P
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
    n = 3       # number of states
    m = 1       # number of measurements
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
    1.86967808173, 1.18073207847, 1.10729605087, 0.916168349913,0.678547664519,
    0.562381751596,0.355468474885,-0.155607486619,-0.287198661013,-0.602973173813,
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
    wall_times = []

    for run_idx in range(NUM_RUNS):
        pr = cProfile.Profile()
        t0 = time.perf_counter()
        pr.enable()
        run_filter()
        pr.disable()
        elapsed = time.perf_counter() - t0
        wall_times.append(elapsed)

        s = io.StringIO()
        ps = pstats.Stats(pr, stream=s).sort_stats("cumulative")
        ps.print_stats()
        yield run_idx, elapsed, s.getvalue()


def main():
    lines = []
    lines.append("=" * 72)
    lines.append("Kalman Filter cProfile Report")
    lines.append("Source: https://github.com/hmartiro/kalman-cpp")
    lines.append(f"Runs: {NUM_RUNS}  |  Measurements per run: {len(MEASUREMENTS)}")
    lines.append("=" * 72)

    wall_times = []

    for run_idx, elapsed, profile_text in profile_runs():
        wall_times.append(elapsed)
        lines.append(f"\n{'─'*72}")
        lines.append(f"Run {run_idx + 1:>2}/{NUM_RUNS}   wall time: {elapsed*1e3:.4f} ms")
        lines.append(f"{'─'*72}")
        lines.append(profile_text)

    # Summary table
    arr = np.array(wall_times) * 1e3   # convert to ms
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

    report = "\n".join(lines)
    print(report)

    out_path = "profiling/project_profile.txt"
    with open(out_path, "w") as f:
        f.write(report)
    print(f"\nProfile saved to {out_path}")


if __name__ == "__main__":
    main()
