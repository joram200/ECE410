#!/usr/bin/env bash
# run_profiles.sh — build firmware, run N GDB JTAG profiling sessions,
#                   record execution time / throughput / memory per run,
#                   print averaged summary table.
#
# Usage: ./scripts/run_profiles.sh
# Must be run from project/SoC_Benchmarking/kalman_hw_driver/.
#
# Method: GDB hardware breakpoints at profile_done() symbol; reads
# kf_cycles_start/end and kf_heap_start/end by DWARF symbol name.
# No UART, no gprof arc_table.
#
# Prerequisites:
#   - FPGA programmed with SoC_impl bitstream (which includes the Kalman slave)
#   - OpenOCD not already running on port 3333
#   - pio debug build completed at least once (or run 'pio debug' first)

set -euo pipefail

# ---------------------------------------------------------------------------
# Configuration
# ---------------------------------------------------------------------------
OPENOCD="$HOME/.platformio/packages/tool-openocd-riscv-chipsalliance/bin/openocd"
GDB="$HOME/.platformio/packages/toolchain-riscv/bin/riscv64-unknown-elf-gdb"
NM="$HOME/.platformio/packages/toolchain-riscv/bin/riscv64-unknown-elf-nm"
FIRMWARE=".pio/build/swervolf_nexys/firmware.elf"
OPENOCD_CFG="$HOME/.platformio/packages/framework-wd-riscv-sdk/board/nexys_a7_eh1/swervolf_nexys_eh1_debug.cfg"
METRICS_SCRIPT="$(dirname "$0")/compute_metrics.py"
OUTPUT_DIR="results"

NRUNS=5
CLOCK_HZ=13000000      # SweRV EL2 core clock (measured in RVfpgaEL2_profiling)
CLOCK_KHZ=13000
TOTAL_UPDATES=45       # Kalman update steps per run
HW_FLOPS=1080          # 24 FLOPs/update × 45 updates (hardware kernel FLOPs only)

# ---------------------------------------------------------------------------
# Step 1: Build debug firmware
# ---------------------------------------------------------------------------
echo "=== Building firmware ==="
pio debug --environment swervolf_nexys

# ---------------------------------------------------------------------------
# Step 2: Resolve symbol addresses from ELF
# ---------------------------------------------------------------------------
echo "=== Resolving symbol addresses ==="

PROFILE_DONE_ADDR=$("$NM" "$FIRMWARE" \
    | awk '($2=="T"||$2=="t") && $3=="profile_done" {print "0x"$1}' | head -1)

if [ -z "$PROFILE_DONE_ADDR" ]; then
    echo "ERROR: profile_done symbol not found in $FIRMWARE" >&2
    exit 1
fi
echo "    profile_done() : $PROFILE_DONE_ADDR"

MAIN_ADDR=$("$NM" "$FIRMWARE" \
    | awk '($2=="T"||$2=="t") && $3=="main" {print "0x"$1}' | head -1)
echo "    main()         : $MAIN_ADDR"

# ---------------------------------------------------------------------------
# Step 3: Create output directory
# ---------------------------------------------------------------------------
mkdir -p "$OUTPUT_DIR"

# ---------------------------------------------------------------------------
# Step 4: Start OpenOCD once for all runs
# ---------------------------------------------------------------------------
echo "=== Starting OpenOCD ==="
"$OPENOCD" -f "$OPENOCD_CFG" > "$OUTPUT_DIR/openocd.log" 2>&1 &
OPENOCD_PID=$!
trap 'echo "Killing OpenOCD (PID $OPENOCD_PID)"; kill "$OPENOCD_PID" 2>/dev/null || true; rm -f /tmp/gdb_hw_run_*.gdb' EXIT

sleep 3   # wait for OpenOCD to connect to FPGA

# ---------------------------------------------------------------------------
# Step 5: Run N profiling sessions
# ---------------------------------------------------------------------------
SUCCESSFUL_RUNS=0

for i in $(seq 1 $NRUNS); do
    echo ""
    echo "=== Run $i / $NRUNS ==="
    RUN_DIR="$OUTPUT_DIR/run_$i"
    mkdir -p "$RUN_DIR"

    # ---- 5a: Generate per-run GDB script by substituting tokens ----
    GDB_SCRIPT="/tmp/gdb_hw_run_${i}.gdb"
    sed -e "s|__RUNDIR__|${RUN_DIR}|g" \
        -e "s|__PROFILE_DONE__|${PROFILE_DONE_ADDR}|g" \
        "$(dirname "$0")/gdb_hw.gdb" > "$GDB_SCRIPT"

    # ---- 5b: Run GDB, capture stdout+stderr ----
    GDB_LOG="$RUN_DIR/gdb_output.txt"
    timeout 120 "$GDB" -batch -x "$GDB_SCRIPT" "$FIRMWARE" \
        > "$GDB_LOG" 2>&1 || true

    # ---- 5c: Parse METRIC lines ----
    cycles_start=$(grep "METRIC kf_cycles_start" "$GDB_LOG" | awk '{print $3}' | tr -d '[:space:]')
    cycles_end=$(  grep "METRIC kf_cycles_end"   "$GDB_LOG" | awk '{print $3}' | tr -d '[:space:]')
    heap_start=$(  grep "METRIC kf_heap_start"   "$GDB_LOG" | awk '{print $3}' | tr -d '[:space:]')
    heap_end=$(    grep "METRIC kf_heap_end"     "$GDB_LOG" | awk '{print $3}' | tr -d '[:space:]')

    # ---- 5d: Validate ----
    if [ -z "$cycles_start" ] || [ -z "$cycles_end" ] || [ "$cycles_start" = "0" ]; then
        echo "    Run $i: FAILED — cycle metrics missing or zero (check $GDB_LOG)" >&2
        sleep 2
        continue
    fi

    # ---- 5e: Compute derived metrics ----
    cycles_elapsed=$(( cycles_end - cycles_start ))
    time_ms=$(awk "BEGIN { printf \"%.3f\", $cycles_elapsed / $CLOCK_KHZ }")
    time_sec=$(awk "BEGIN { printf \"%.6f\", $cycles_elapsed / $CLOCK_HZ }")
    samples_per_s=$(awk "BEGIN { printf \"%.2f\", $TOTAL_UPDATES / ($cycles_elapsed / $CLOCK_HZ) }")
    gflops=$(awk "BEGIN { printf \"%.4e\", $HW_FLOPS / ($cycles_elapsed / $CLOCK_HZ) / 1e9 }")
    heap_bytes=$(( heap_end - heap_start ))

    echo "    cycles: $cycles_elapsed  time: ${time_ms} ms  samples/s: $samples_per_s  GFLOP/s: $gflops  heap: ${heap_bytes} B"

    # ---- 5f: Write per-run metrics file ----
    cat > "$RUN_DIR/metrics.txt" <<EOF
run=$i
cycles_start=$cycles_start
cycles_end=$cycles_end
cycles_elapsed=$cycles_elapsed
time_ms=$time_ms
time_sec=$time_sec
samples_per_s=$samples_per_s
gflops=$gflops
heap_start=$heap_start
heap_end=$heap_end
heap_bytes=$heap_bytes
EOF

    SUCCESSFUL_RUNS=$(( SUCCESSFUL_RUNS + 1 ))
    sleep 2
done

# ---------------------------------------------------------------------------
# Step 6: Compute averages and write summary
# ---------------------------------------------------------------------------
echo ""
echo "=== $SUCCESSFUL_RUNS / $NRUNS runs successful ==="

if [ "$SUCCESSFUL_RUNS" -gt 0 ]; then
    python3 "$METRICS_SCRIPT" \
        --runs "$NRUNS" \
        --results-dir "$OUTPUT_DIR" \
        --output "$OUTPUT_DIR/summary.txt" \
        --clock-hz "$CLOCK_HZ" \
        --total-updates "$TOTAL_UPDATES" \
        --total-flops "$HW_FLOPS"
fi

echo ""
echo "=== Done ==="
echo "  Per-run data : $OUTPUT_DIR/run_N/{gdb_output.txt, metrics.txt}"
echo "  Summary      : $OUTPUT_DIR/summary.txt"
echo ""
echo "Copy AVG row from summary.txt into codefest/cf09/benchmarks/benchmark_results.md"
