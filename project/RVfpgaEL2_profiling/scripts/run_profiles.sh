#!/usr/bin/env bash
# run_profiles.sh — build firmware, run N profiling sessions via GDB JTAG dump,
#                   record execution time / throughput / memory metrics per run,
#                   and print an averaged summary table.
#
# Usage: ./scripts/run_profiles.sh
# Must be run from the project root directory.
#
# Method: GDB hardware breakpoints at main() entry and main() return dump the
# arc_table from SRAM and read cycle-count / heap metrics by symbol name.
# UART is NOT used (BSP FIFO never drains on this bitstream).
#
# Prerequisites:
#   - FPGA programmed with the correct bitstream
#   - OpenOCD not already running on port 3333

set -euo pipefail

# ---------------------------------------------------------------------------
# Configuration
# ---------------------------------------------------------------------------
OPENOCD="$HOME/.platformio/packages/tool-openocd-riscv-chipsalliance/bin/openocd"
GDB="$HOME/.platformio/packages/toolchain-riscv/bin/riscv64-unknown-elf-gdb"
NM="$HOME/.platformio/packages/toolchain-riscv/bin/riscv64-unknown-elf-nm"
GPROF="$HOME/.platformio/packages/toolchain-riscv/bin/riscv64-unknown-elf-gprof"
FIRMWARE=".pio/build/swervolf_nexys/firmware.elf"
OPENOCD_CFG="$HOME/.platformio/packages/framework-wd-riscv-sdk/board/nexys_a7_eh1/swervolf_nexys_eh1_debug.cfg"
PARSE_SCRIPT="$(dirname "$0")/extract_gmon.py"
METRICS_SCRIPT="$(dirname "$0")/compute_metrics.py"
OUTPUT_DIR="results"

NRUNS=5
CLOCK_HZ=13000000      # SweRV EL2 core clock
CLOCK_KHZ=13000        # cycles per millisecond
TOTAL_UPDATES=45       # Kalman update steps per run
TOTAL_FLOPS=10350      # total double-precision FLOPs per run

# Expected arc_table addresses (warn if nm shows something different)
EXPECTED_ARC_START="0x3f1b4"
EXPECTED_ARC_END="0x421b4"     # = EXPECTED_ARC_START + 12288

# ---------------------------------------------------------------------------
# Step 1: Build firmware (debug build, includes -pg instrumentation)
# ---------------------------------------------------------------------------
echo "=== Building firmware ==="
pio debug --environment swervolf_nexys

# ---------------------------------------------------------------------------
# Step 2: Resolve symbol addresses from the built ELF
# ---------------------------------------------------------------------------
echo "=== Resolving symbol addresses ==="

ARC_TABLE_ADDR=$("$NM" "$FIRMWARE" | awk '$3 == "_end" && $2 == "B" {print "0x"$1}')
ARC_TABLE_END=$(printf "0x%x" $(( ARC_TABLE_ADDR + 12288 )))

echo "    arc_table start (_end) : $ARC_TABLE_ADDR  (expected $EXPECTED_ARC_START)"
echo "    arc_table end          : $ARC_TABLE_END   (expected $EXPECTED_ARC_END)"

if [ "$ARC_TABLE_ADDR" != "$EXPECTED_ARC_START" ]; then
    echo "    WARNING: arc_table address shifted — using $ARC_TABLE_ADDR"
fi

# main() entry and return addresses are currently hardcoded in the GDB template.
# Print them so the user can verify if a rebuild changes them.
MAIN_ADDR=$("$NM" "$FIRMWARE" | awk '$3 == "main" && $2 == "T" {print "0x"$1}' | head -1)
echo "    main() entry           : $MAIN_ADDR (hbreak at 0x88 — update gdb_dump.gdb if different)"

# ---------------------------------------------------------------------------
# Step 3: Create output directory structure
# ---------------------------------------------------------------------------
mkdir -p "$OUTPUT_DIR"

# ---------------------------------------------------------------------------
# Step 4: Start OpenOCD once for all runs
# ---------------------------------------------------------------------------
echo "=== Starting OpenOCD ==="
"$OPENOCD" -f "$OPENOCD_CFG" > "$OUTPUT_DIR/openocd.log" 2>&1 &
OPENOCD_PID=$!
trap 'echo "Killing OpenOCD (PID $OPENOCD_PID)"; kill "$OPENOCD_PID" 2>/dev/null || true; rm -f /tmp/gdb_run_*.gdb' EXIT

sleep 3   # wait for OpenOCD to initialise and connect to FPGA

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
    GDB_SCRIPT="/tmp/gdb_run_${i}.gdb"
    sed -e "s|__RUNDIR__|${RUN_DIR}|g" \
        -e "s|__ARC_START__|${ARC_TABLE_ADDR}|g" \
        -e "s|__ARC_END__|${ARC_TABLE_END}|g" \
        "$(dirname "$0")/gdb_dump.gdb" > "$GDB_SCRIPT"

    # ---- 5b: Run GDB, capture all stdout+stderr for metric parsing ----
    GDB_LOG="$RUN_DIR/gdb_output.txt"
    timeout 120 "$GDB" -batch -x "$GDB_SCRIPT" "$FIRMWARE" \
        > "$GDB_LOG" 2>&1 || true

    # ---- 5c: Check arc_table.bin was produced ----
    if [ ! -f "$RUN_DIR/arc_table.bin" ]; then
        echo "    Run $i: FAILED — arc_table.bin not produced (check $GDB_LOG)" >&2
        sleep 2
        continue
    fi

    # ---- 5d: Parse METRIC lines from GDB output ----
    cycles_start=$(grep "METRIC kf_cycles_start" "$GDB_LOG" | awk '{print $3}' | tr -d '[:space:]')
    cycles_end=$(  grep "METRIC kf_cycles_end"   "$GDB_LOG" | awk '{print $3}' | tr -d '[:space:]')
    heap_start=$(  grep "METRIC kf_heap_start"   "$GDB_LOG" | awk '{print $3}' | tr -d '[:space:]')
    heap_end=$(    grep "METRIC kf_heap_end"     "$GDB_LOG" | awk '{print $3}' | tr -d '[:space:]')
    arc_count=$(   grep "METRIC arc_count"       "$GDB_LOG" | awk '{print $3}' | tr -d '[:space:]')

    # Validate — if any metric is empty or 0, flag it
    if [ -z "$cycles_start" ] || [ -z "$cycles_end" ] || [ "$cycles_start" = "0" ]; then
        echo "    Run $i: WARNING — cycle metrics missing or zero (CSR read may have failed)"
        echo "             cycles_start='$cycles_start'  cycles_end='$cycles_end'"
    fi

    # ---- 5e: Compute derived metrics (awk for float arithmetic) ----
    cycles_elapsed=$(( cycles_end - cycles_start ))

    time_ms=$(awk "BEGIN { printf \"%.3f\", $cycles_elapsed / $CLOCK_KHZ }")
    time_sec=$(awk "BEGIN { printf \"%.6f\", $cycles_elapsed / $CLOCK_HZ }")
    samples_per_s=$(awk "BEGIN { printf \"%.2f\", $TOTAL_UPDATES / ($cycles_elapsed / $CLOCK_HZ) }")
    gflops=$(awk "BEGIN { printf \"%.4e\", $TOTAL_FLOPS / ($cycles_elapsed / $CLOCK_HZ) / 1e9 }")
    heap_bytes=$(( heap_end - heap_start ))

    echo "    cycles: $cycles_elapsed  time: ${time_ms} ms  samples/s: $samples_per_s  GFLOP/s: $gflops  heap: ${heap_bytes} B  arcs: $arc_count"

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
arc_count=$arc_count
EOF

    # ---- 5g: Parse arc_table.bin -> gmon.out ----
    if python3 "$PARSE_SCRIPT" "$RUN_DIR/arc_table.bin" "$RUN_DIR/gmon.out" 2>&1 \
            | grep -v "^$" | sed 's/^/    /'; then
        echo "    gmon.out written"
    fi

    # ---- 5h: Generate gprof call-graph report ----
    "$GPROF" "$FIRMWARE" "$RUN_DIR/gmon.out" > "$RUN_DIR/gprof_report.txt" 2>/dev/null || true
    echo "    gprof_report.txt written"

    SUCCESSFUL_RUNS=$(( SUCCESSFUL_RUNS + 1 ))
    sleep 2   # let OpenOCD recover before next GDB session
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
        --total-flops "$TOTAL_FLOPS"
fi

echo ""
echo "=== Done ==="
echo "  Per-run data : $OUTPUT_DIR/run_N/{arc_table.bin, gmon.out, metrics.txt, gprof_report.txt}"
echo "  Summary      : $OUTPUT_DIR/summary.txt"
