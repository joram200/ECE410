#!/usr/bin/env bash
# combine_report.sh — generate a gprof call-graph report from gmon.out produced
#                     by the arc_table GDB dump workflow.
#
# Replaces the original multi-run merge approach.  The arc_table dump produces
# a single gmon.out (via parse_arc_table.py / extract_gmon.py); this script
# runs gprof against it to produce the human-readable call-graph report.
#
# Usage: ./scripts/combine_report.sh
# Must be run from the project root directory.
# Run scripts/run_profiles.sh first to generate gmon_runs/results/gmon.out.

set -euo pipefail

# ---------------------------------------------------------------------------
# Configuration
# ---------------------------------------------------------------------------
GPROF="$HOME/.platformio/packages/toolchain-riscv/bin/riscv64-unknown-elf-gprof"
FIRMWARE=".pio/build/swervolf_nexys/firmware.elf"
OUTPUT_DIR="gmon_runs/results"
GMON_OUT="$OUTPUT_DIR/gmon.out"

# ---------------------------------------------------------------------------
# Sanity checks
# ---------------------------------------------------------------------------
if [ ! -f "$FIRMWARE" ]; then
    echo "Error: firmware not found at '$FIRMWARE'." >&2
    echo "Run 'pio debug --environment swervolf_nexys' or scripts/run_profiles.sh first." >&2
    exit 1
fi

if [ ! -f "$GMON_OUT" ]; then
    echo "Error: '$GMON_OUT' not found." >&2
    echo "Run scripts/run_profiles.sh first to generate the arc_table dump and gmon.out." >&2
    exit 1
fi

echo "Using gmon.out : $GMON_OUT"
echo "Using firmware : $FIRMWARE"

# ---------------------------------------------------------------------------
# Step 1: Generate flat-profile + call-graph report
# ---------------------------------------------------------------------------
echo "=== Generating call-graph report ==="
"$GPROF" "$FIRMWARE" "$GMON_OUT" > "$OUTPUT_DIR/combined_report.txt"
echo "    Written: $OUTPUT_DIR/combined_report.txt"

# ---------------------------------------------------------------------------
# Step 2: Generate annotated source report
# ---------------------------------------------------------------------------
echo "=== Generating annotated source report ==="
"$GPROF" -A "$FIRMWARE" "$GMON_OUT" > "$OUTPUT_DIR/combined_report_annotated.txt"
echo "    Written: $OUTPUT_DIR/combined_report_annotated.txt"

# ---------------------------------------------------------------------------
# Summary
# ---------------------------------------------------------------------------
echo ""
echo "arc_table binary : $OUTPUT_DIR/arc_table.bin"
echo "gmon.out         : $GMON_OUT"
echo "Flat/call-graph  : $OUTPUT_DIR/combined_report.txt"
echo "Annotated source : $OUTPUT_DIR/combined_report_annotated.txt"
