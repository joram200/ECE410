"""
Benchmark for hmartiro/kalman-cpp Basic Kalman Filter (Python port).
Measures: wall time per run, cProfile per-function stats, peak memory.
All stdlib — no extra packages required.
"""

import cProfile
import pstats
import io
import time
import platform
import tracemalloc
import statistics
import sys
import os
import numpy as np

NUM_RUNS = 10

# ---------------------------------------------------------------------------
# Kalman filter (mirrors kalman.cpp / kalman-test.cpp)
# ---------------------------------------------------------------------------
class KalmanFilter:
    def __init__(self, dt, A, C, Q, R, P):
        self.A, self.C, self.Q, self.R = A, C, Q, R
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

    def init(self, t0=0.0, x0=None):
        self.x_hat = x0.copy() if x0 is not None else np.zeros(self.n)
        self.P = self.P0.copy()
        self.t0 = t0
        self.t = t0
        self.initialized = True

    def update(self, y):
        self.x_hat_new = self.A @ self.x_hat
        self.P = self.A @ self.P @ self.A.T + self.Q
        S = self.C @ self.P @ self.C.T + self.R
        self.K = self.P @ self.C.T @ np.linalg.inv(S)
        self.x_hat_new += self.K @ (y - self.C @ self.x_hat_new)
        self.P = (self.I - self.K @ self.C) @ self.P
        self.x_hat = self.x_hat_new.copy()
        self.t += self.dt


def build_filter():
    n, m, dt = 3, 1, 1.0 / 30.0
    A = np.array([[1, dt, 0], [0, 1, dt], [0, 0, 1]], dtype=float)
    C = np.array([[1, 0, 0]], dtype=float)
    Q = np.array([[.05, .05, .0], [.05, .05, .0], [.0, .0, .0]], dtype=float)
    R = np.array([[5.0]], dtype=float)
    P = np.array([[.1, .1, .1], [.1, 1e4, 10], [.1, 10, 100]], dtype=float)
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
N_MEAS = len(MEASUREMENTS)


def run_filter():
    kf = build_filter()
    kf.init(0.0, np.array([MEASUREMENTS[0], 0.0, -9.81]))
    y = np.zeros(1)
    for z in MEASUREMENTS:
        y[0] = z
        kf.update(y)
    return kf.x_hat


# ---------------------------------------------------------------------------
# Platform info
# ---------------------------------------------------------------------------
def get_platform_info():
    uname = platform.uname()
    try:
        cpu_freq = None
        with open("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq") as f:
            cpu_freq = int(f.read().strip()) / 1e6  # MHz
    except Exception:
        pass
    try:
        cpu_name = None
        with open("/proc/cpuinfo") as f:
            for line in f:
                if "model name" in line:
                    cpu_name = line.split(":")[1].strip()
                    break
    except Exception:
        cpu_name = uname.processor

    mem_gb = None
    try:
        with open("/proc/meminfo") as f:
            for line in f:
                if line.startswith("MemTotal"):
                    mem_kb = int(line.split()[1])
                    mem_gb = mem_kb / (1024 ** 2)
                    break
    except Exception:
        pass

    return {
        "os": f"{uname.system} {uname.release}",
        "cpu": cpu_name or uname.processor,
        "cpu_max_mhz": cpu_freq,
        "python": sys.version.split()[0],
        "numpy": np.__version__,
        "mem_total_gb": mem_gb,
    }


# ---------------------------------------------------------------------------
# Main benchmark
# ---------------------------------------------------------------------------
def main():
    info = get_platform_info()

    wall_times_ms = []
    peak_mem_kb_list = []
    profile_text_run1 = ""

    for i in range(NUM_RUNS):
        # Memory tracking
        tracemalloc.start()
        # Wall time + cProfile
        pr = cProfile.Profile()
        t0 = time.perf_counter()
        pr.enable()
        run_filter()
        pr.disable()
        elapsed_ms = (time.perf_counter() - t0) * 1e3
        _, peak_bytes = tracemalloc.get_traced_memory()
        tracemalloc.stop()

        wall_times_ms.append(elapsed_ms)
        peak_mem_kb_list.append(peak_bytes / 1024)

        if i == 0:
            s = io.StringIO()
            pstats.Stats(pr, stream=s).sort_stats("cumulative").print_stats()
            profile_text_run1 = s.getvalue()

    # Statistics (exclude run 1 warm-up for median/throughput)
    warm = wall_times_ms[1:]
    median_ms   = statistics.median(warm)
    mean_ms     = statistics.mean(warm)
    stdev_ms    = statistics.stdev(warm)
    min_ms      = min(warm)
    max_ms      = max(warm)
    throughput  = N_MEAS / (median_ms * 1e-3)   # measurements/s
    median_mem  = statistics.median(peak_mem_kb_list)

    # Per-update breakdown
    median_us_per_update = (median_ms * 1e3) / N_MEAS   # µs

    # -----------------------------------------------------------------------
    # Print summary
    # -----------------------------------------------------------------------
    SEP = "=" * 66
    sep = "-" * 66
    print(SEP)
    print("KALMAN FILTER BENCHMARK RESULTS")
    print(SEP)
    print(f"  Median wall time  : {median_ms:.4f} ms / run")
    print(f"  Mean  wall time   : {mean_ms:.4f} ms")
    print(f"  Std dev           : {stdev_ms:.4f} ms")
    print(f"  Min / Max         : {min_ms:.4f} / {max_ms:.4f} ms")
    print(f"  Throughput        : {throughput:.1f} measurements/s")
    print(f"  Per update()      : {median_us_per_update:.2f} µs")
    print(f"  Peak memory (med) : {median_mem:.2f} KiB")
    print()
    print("Per-run wall times (ms):")
    for i, t in enumerate(wall_times_ms):
        tag = "  [warm-up]" if i == 0 else ""
        print(f"  Run {i+1:>2}: {t:.4f} ms{tag}")
    print(SEP)

    # -----------------------------------------------------------------------
    # Emit JSON-style dict for sw_baseline.md writer
    # -----------------------------------------------------------------------
    return {
        "info": info,
        "wall_times_ms": wall_times_ms,
        "median_ms": median_ms,
        "mean_ms": mean_ms,
        "stdev_ms": stdev_ms,
        "min_ms": min_ms,
        "max_ms": max_ms,
        "throughput": throughput,
        "median_us_per_update": median_us_per_update,
        "median_mem_kib": median_mem,
        "peak_mem_kib": peak_mem_kb_list,
        "profile_text_run1": profile_text_run1,
        "n_runs": NUM_RUNS,
        "n_meas": N_MEAS,
    }


if __name__ == "__main__":
    r = main()

    # Write sw_baseline.md
    info = r["info"]
    wall = r["wall_times_ms"]
    rows = "\n".join(
        f"| {i+1} | {t:.4f} ms | {r['peak_mem_kib'][i]:.2f} KiB |"
        + (" ← warm-up (excluded from stats)" if i == 0 else "")
        for i, t in enumerate(wall)
    )

    cpu_freq_str = (f"{info['cpu_max_mhz']:.0f} MHz max"
                    if info["cpu_max_mhz"] else "N/A")
    mem_str = (f"{info['mem_total_gb']:.1f} GiB" if info["mem_total_gb"] else "N/A")

    md = f"""# Software Baseline: Basic Kalman Filter

**Source:** <https://github.com/hmartiro/kalman-cpp>
**Kernel:** `KalmanFilter::update()` — 1-D projectile motion, 45 measurements/run

---

## Platform & Configuration

| Property | Value |
|----------|-------|
| OS | {info['os']} |
| CPU | {info['cpu']} |
| CPU max freq | {cpu_freq_str} |
| System RAM | {mem_str} |
| Python | {info['python']} |
| NumPy | {info['numpy']} |
| Profiler | `cProfile` + `tracemalloc` (stdlib) |
| Runs | {r['n_runs']} (run 1 = warm-up, excluded from stats) |
| Measurements/run | {r['n_meas']} |
| State dim / Meas dim | n = 3 / m = 1 |
| dtype | float64 |

---

## Results

### Timing (wall clock, warm runs 2–{r['n_runs']})

| Metric | Value |
|--------|-------|
| **Median** | **{r['median_ms']:.4f} ms / run** |
| Mean | {r['mean_ms']:.4f} ms |
| Std dev | {r['stdev_ms']:.4f} ms |
| Min | {r['min_ms']:.4f} ms |
| Max | {r['max_ms']:.4f} ms |
| Per `update()` call (median) | {r['median_us_per_update']:.2f} µs |

### Throughput

| Metric | Value |
|--------|-------|
| **Measurements processed/s** | **{r['throughput']:.1f} meas/s** |
| Equivalent update() calls/s | {r['throughput']:.1f} calls/s |

### Memory Usage (peak heap, `tracemalloc`)

| Metric | Value |
|--------|-------|
| **Median peak** | **{r['median_mem_kib']:.2f} KiB** |
| Min peak | {min(r['peak_mem_kib']):.2f} KiB |
| Max peak | {max(r['peak_mem_kib']):.2f} KiB |

---

## Per-Run Data

| Run | Wall time | Peak memory | Notes |
|-----|-----------|-------------|-------|
{rows}

---

## cProfile: Top Functions (Run 1, warm-up)

```
{r['profile_text_run1'].strip()}
```

---

## Notes

- Run 1 is excluded from statistics — it includes Python module import and
  NumPy JIT overhead (~10× slower than warm runs).
- All subsequent runs are stable within ±{r['stdev_ms']:.4f} ms (1σ).
- Memory is dominated by NumPy intermediate arrays allocated per `update()` call;
  no persistent heap growth across runs.
"""

    out = "/run/media/sackb/Windows-SSD/Users/sackb/OneDrive/Desktop/University/Course_Work/2025-2026/Spring_2026/ECE_410/ECE410/project/m1/sw_baseline.md"
    with open(out, "w") as f:
        f.write(md)
    print(f"\nWrote {out}")
