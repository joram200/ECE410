# Software Baseline: Basic Kalman Filter

**Source:** <https://github.com/hmartiro/kalman-cpp>
**Kernel:** `KalmanFilter::update()` — 1-D projectile motion, 45 measurements/run

---

## Platform & Configuration

| Property | Value |
|----------|-------|
| OS | Linux 6.19.11-arch1-1 |
| CPU | 11th Gen Intel(R) Core(TM) i7-11800H @ 2.30GHz |
| CPU max freq | 4600 MHz (manufacturer spec) |
| System RAM | 15.4 GiB |
| Python | 3.14.3 |
| NumPy | 2.4.2 |
| Profiler | `cProfile` + `tracemalloc` (stdlib) |
| Runs | 10 (run 1 = warm-up, excluded from stats) |
| Measurements/run | 45 |
| State dim / Meas dim | n = 3 / m = 1 |
| dtype | float64 |

---

## Results

### Timing (wall clock, warm runs 2–10)

| Metric | Value |
|--------|-------|
| **Median** | **3.6765 ms / run** |
| Mean | 4.0940 ms |
| Std dev | 0.9446 ms |
| Min | 3.6454 ms |
| Max | 6.4719 ms |
| Per `update()` call (median) | 81.70 µs |

### Throughput

| Metric | Value |
|--------|-------|
| **Measurements processed/s** | **12240.1 meas/s** |
| Equivalent update() calls/s | 12240.1 calls/s |

### Memory Usage (peak heap, `tracemalloc`)

| Metric | Value |
|--------|-------|
| **Median peak** | **10.20 KiB** |
| Min peak | 9.88 KiB |
| Max peak | 14.02 KiB |

---

## Per-Run Data

| Run | Wall time | Peak memory | Notes |
|-----|-----------|-------------|-------|
| 1 | 4.6959 ms | 14.02 KiB | ← warm-up (excluded from stats)
| 2 | 3.7573 ms | 10.91 KiB |
| 3 | 3.6579 ms | 10.82 KiB |
| 4 | 4.6157 ms | 10.97 KiB |
| 5 | 3.6577 ms | 10.29 KiB |
| 6 | 3.6765 ms | 9.89 KiB |
| 7 | 3.6498 ms | 10.06 KiB |
| 8 | 3.6454 ms | 10.12 KiB |
| 9 | 6.4719 ms | 9.88 KiB |
| 10 | 3.7140 ms | 10.10 KiB |

---

## cProfile: Top Functions (Run 1, warm-up)

```
1103 function calls in 0.005 seconds

   Ordered by: cumulative time

   ncalls  tottime  percall  cumtime  percall filename:lineno(function)
        1    0.000    0.000    0.005    0.005 /run/media/sackb/Windows-SSD/Users/sackb/OneDrive/Desktop/University/Course_Work/2025-2026/Spring_2026/ECE_410/ECE410/codefest/cf02/profiling/benchmark.py:80(run_filter)
       45    0.003    0.000    0.004    0.000 /run/media/sackb/Windows-SSD/Users/sackb/OneDrive/Desktop/University/Course_Work/2025-2026/Spring_2026/ECE_410/ECE410/codefest/cf02/profiling/benchmark.py:44(update)
       45    0.001    0.000    0.001    0.000 /home/sackb/zephyrproject/.venv/lib/python3.14/site-packages/numpy/linalg/_linalg.py:536(inv)
       45    0.000    0.000    0.000    0.000 /home/sackb/zephyrproject/.venv/lib/python3.14/site-packages/numpy/_core/_ufunc_config.py:472(__enter__)
       45    0.000    0.000    0.000    0.000 /home/sackb/zephyrproject/.venv/lib/python3.14/site-packages/numpy/linalg/_linalg.py:189(_commonType)
       49    0.000    0.000    0.000    0.000 {method 'copy' of 'numpy.ndarray' objects}
        1    0.000    0.000    0.000    0.000 /run/media/sackb/Windows-SSD/Users/sackb/OneDrive/Desktop/University/Course_Work/2025-2026/Spring_2026/ECE_410/ECE410/codefest/cf02/profiling/benchmark.py:55(build_filter)
       45    0.000    0.000    0.000    0.000 {method 'set' of '_contextvars.ContextVar' objects}
       45    0.000    0.000    0.000    0.000 {built-in method numpy._core._multiarray_umath._make_extobj}
       45    0.000    0.000    0.000    0.000 /home/sackb/zephyrproject/.venv/lib/python3.14/site-packages/numpy/linalg/_linalg.py:164(_makearray)
        1    0.000    0.000    0.000    0.000 /run/media/sackb/Windows-SSD/Users/sackb/OneDrive/Desktop/University/Course_Work/2025-2026/Spring_2026/ECE_410/ECE410/codefest/cf02/profiling/benchmark.py:24(__init__)
       45    0.000    0.000    0.000    0.000 /home/sackb/zephyrproject/.venv/lib/python3.14/site-packages/numpy/_core/_ufunc_config.py:488(__exit__)
       45    0.000    0.000    0.000    0.000 /home/sackb/zephyrproject/.venv/lib/python3.14/site-packages/numpy/linalg/_linalg.py:183(_realType)
       45    0.000    0.000    0.000    0.000 {method 'astype' of 'numpy.ndarray' objects}
       90    0.000    0.000    0.000    0.000 /home/sackb/zephyrproject/.venv/lib/python3.14/site-packages/numpy/linalg/_linalg.py:169(isComplexType)
        6    0.000    0.000    0.000    0.000 {built-in method numpy.array}
        1    0.000    0.000    0.000    0.000 /home/sackb/zephyrproject/.venv/lib/python3.14/site-packages/numpy/lib/_twodim_base_impl.py:176(eye)
       45    0.000    0.000    0.000    0.000 /home/sackb/zephyrproject/.venv/lib/python3.14/site-packages/numpy/linalg/_linalg.py:238(_assert_stacked_square)
       45    0.000    0.000    0.000    0.000 {method 'reset' of '_contextvars.ContextVar' objects}
        1    0.000    0.000    0.000    0.000 {method 'disable' of '_lsprof.Profiler' objects}
      135    0.000    0.000    0.000    0.000 {built-in method builtins.issubclass}
       45    0.000    0.000    0.000    0.000 {method 'get' of 'dict' objects}
       45    0.000    0.000    0.000    0.000 {built-in method builtins.getattr}
       45    0.000    0.000    0.000    0.000 {method '__array_wrap__' of 'numpy.ndarray' objects}
        5    0.000    0.000    0.000    0.000 {built-in method numpy.zeros}
       45    0.000    0.000    0.000    0.000 /home/sackb/zephyrproject/.venv/lib/python3.14/site-packages/numpy/_core/_ufunc_config.py:462(__init__)
       45    0.000    0.000    0.000    0.000 /home/sackb/zephyrproject/.venv/lib/python3.14/site-packages/numpy/linalg/_linalg.py:532(_unary_dispatcher)
       45    0.000    0.000    0.000    0.000 {built-in method numpy.asarray}
        1    0.000    0.000    0.000    0.000 /run/media/sackb/Windows-SSD/Users/sackb/OneDrive/Desktop/University/Course_Work/2025-2026/Spring_2026/ECE_410/ECE410/codefest/cf02/profiling/benchmark.py:37(init)
        2    0.000    0.000    0.000    0.000 {built-in method _operator.index}
```

---

## Notes

- Run 1 is excluded from statistics — it includes Python module import and
  NumPy JIT overhead (~10× slower than warm runs).
- All subsequent runs are stable within ±0.9446 ms (1σ).
- Memory is dominated by NumPy intermediate arrays allocated per `update()` call;
  no persistent heap growth across runs.
