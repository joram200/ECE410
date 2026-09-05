#!/usr/bin/env python3
"""
compute_metrics.py — read per-run metrics.txt files, compute averages,
                     print and write a formatted summary table.

Called by run_profiles.sh after all runs complete:
    python3 scripts/compute_metrics.py \
        --runs 5 \
        --results-dir results \
        --output results/summary.txt \
        --clock-hz 13000000 \
        --total-updates 45 \
        --total-flops 1080

FLOPs breakdown (hardware kernel, per update):
  24 FLOPs = 11 MACs × 2 + 2 extra ops
  (see codefest/cf09/cman_ai_analysis.md for derivation)
  Total for 45 updates: 24 × 45 = 1,080 FLOPs
"""

import argparse
import os
import sys


def read_metrics(path):
    data = {}
    try:
        with open(path) as f:
            for line in f:
                line = line.strip()
                if "=" in line:
                    k, _, v = line.partition("=")
                    data[k.strip()] = v.strip()
    except OSError:
        pass
    return data


def fmt_sci(val, decimals=4):
    return f"{val:.{decimals}e}"


def fmt_f(val, decimals=3):
    return f"{val:.{decimals}f}"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--runs",          type=int,   required=True)
    ap.add_argument("--results-dir",   type=str,   required=True)
    ap.add_argument("--output",        type=str,   required=True)
    ap.add_argument("--clock-hz",      type=float, default=13_000_000)
    ap.add_argument("--total-updates", type=int,   default=45)
    ap.add_argument("--total-flops",   type=int,   default=1_080)
    args = ap.parse_args()

    rows = []
    for i in range(1, args.runs + 1):
        mfile = os.path.join(args.results_dir, f"run_{i}", "metrics.txt")
        d = read_metrics(mfile)
        if not d:
            continue
        try:
            row = {
                "run":           int(d["run"]),
                "cycles":        int(d["cycles_elapsed"]),
                "time_ms":       float(d["time_ms"]),
                "samples_per_s": float(d["samples_per_s"]),
                "gflops":        float(d["gflops"]),
                "heap_bytes":    int(d["heap_bytes"]),
            }
            rows.append(row)
        except (KeyError, ValueError) as e:
            print(f"Warning: skipping run {i} — {e}", file=sys.stderr)

    if not rows:
        print("No valid run data found.", file=sys.stderr)
        sys.exit(1)

    n = len(rows)
    avg = {
        "cycles":        sum(r["cycles"]        for r in rows) / n,
        "time_ms":       sum(r["time_ms"]       for r in rows) / n,
        "samples_per_s": sum(r["samples_per_s"] for r in rows) / n,
        "gflops":        sum(r["gflops"]        for r in rows) / n,
        "heap_bytes":    sum(r["heap_bytes"]    for r in rows) / n,
    }

    hdr = (
        f"{'Run':>4}  {'Cycles':>12}  {'Time(ms)':>9}  "
        f"{'Samples/s':>10}  {'GFLOP/s':>10}  {'Heap(B)':>8}"
    )
    sep = "-" * len(hdr)

    def row_str(label, r):
        return (
            f"{label:>4}  {r['cycles']:>12,.0f}  {fmt_f(r['time_ms']):>9}  "
            f"{fmt_f(r['samples_per_s']):>10}  {fmt_sci(r['gflops']):>10}  "
            f"{r['heap_bytes']:>8.0f}"
        )

    lines = [
        "Kalman HW Accelerator — Performance Summary",
        f"Hardware : SweRV EL2 + Kalman AXI slave, {args.clock_hz/1e6:.0f} MHz core clock, Nexys A7",
        f"Workload : {args.total_updates} measurement-correction updates, 3-state filter",
        f"FLOPs    : {args.total_flops:,} total ({args.total_flops // args.total_updates} per update)",
        f"Runs     : {n} of {args.runs} successful",
        "",
        hdr,
        sep,
    ]

    for r in rows:
        lines.append(row_str(str(r["run"]), r))

    lines += [
        sep,
        row_str("AVG", avg),
        "",
        "Notes:",
        "  Cycles   : mcycle CSR delta across 45 kalman_hw_update() calls",
        f"  Time(ms) : cycles / {args.clock_hz/1e3:.0f}  (clock = {args.clock_hz/1e6:.0f} MHz)",
        f"  Samples/s: {args.total_updates} / time_sec",
        f"  GFLOP/s  : {args.total_flops:,} FLOPs / time_sec / 1e9",
        "  Heap(B)  : bump_top delta — should be ~0 (no dynamic allocation in HW driver)",
        "  FLOPs/update: 138 (114 Eigen predict: 15 x_hat + 99 P_pred; 24 HW correct: 11 MACs×2 + 2)",
    ]

    output = "\n".join(lines) + "\n"
    print(output)

    with open(args.output, "w") as f:
        f.write(output)
    print(f"Summary written to {args.output}")


if __name__ == "__main__":
    main()
