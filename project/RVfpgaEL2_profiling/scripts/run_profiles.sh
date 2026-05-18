#!/usr/bin/env bash
# run_profiles.sh — build firmware, start OpenOCD, run GDB to dump arc_table
#                   from SRAM via JTAG, then parse to gmon.out.
#
# Replaces the original UART-based approach, which was not viable because the
# BSP UART FIFO on this bitstream never drains, causing the firmware to hang in
# any busy-wait transmit loop.  Instead, the arc_table populated by _mcount is
# read directly from SRAM over JTAG using hardware breakpoints in GDB.
#
# Usage: ./scripts/run_profiles.sh
# Must be run from the project root directory.
#
# Prerequisites:
#   - FPGA programmed with the correct bitstream
#   - OpenOCD not already running on port 3333
#   - PlatformIO toolchain installed

set -euo pipefail

# ---------------------------------------------------------------------------
# Tool / path configuration
# ---------------------------------------------------------------------------
OPENOCD="$HOME/.platformio/packages/tool-openocd-riscv-chipsalliance/bin/openocd"
GDB="$HOME/.platformio/packages/toolchain-riscv/bin/riscv64-unknown-elf-gdb"
FIRMWARE=".pio/build/swervolf_nexys/firmware.elf"
OPENOCD_CFG="$HOME/.platformio/packages/framework-wd-riscv-sdk/board/nexys_a7_eh1/swervolf_nexys_eh1_debug.cfg"
OUTPUT_DIR="gmon_runs/results"
GDB_SCRIPT="$(dirname "$0")/gdb_dump.gdb"
PARSE_SCRIPT="$(dirname "$0")/parse_arc_table.py"

# ---------------------------------------------------------------------------
# Step 1: Rebuild firmware (debug build, includes -pg instrumentation)
# ---------------------------------------------------------------------------
echo "=== Building firmware ==="
pio debug --environment swervolf_nexys

# ---------------------------------------------------------------------------
# Step 2: Verify addresses match the current build
#
# arc_table is at _end (first byte past BSS).  If the firmware is rebuilt the
# symbol address may shift.  Check with nm and update gdb_dump.gdb if needed.
# ---------------------------------------------------------------------------
echo "=== Verifying arc_table address ==="
NM="$HOME/.platformio/packages/toolchain-riscv/bin/riscv64-unknown-elf-nm"
ARC_TABLE_ADDR=$("$NM" "$FIRMWARE" | awk '/_end$/ {print "0x"$1}')
echo "    arc_table (_end) = $ARC_TABLE_ADDR"
ARC_TABLE_END=$(printf "0x%x" $(( ARC_TABLE_ADDR + 12288 )) 2>/dev/null || echo "?")
echo "    arc_table end    = $ARC_TABLE_END"
echo "    If these differ from 0x375d4/0x3a5d4, update the addresses in gdb_dump.gdb"

# Locate main() ret breakpoint address (first 'ret' / 'jalr x0,x1,0' in main)
MAIN_ADDR=$("$NM" "$FIRMWARE" | awk '/\bmain\b/ {print "0x"$1}' | head -1)
echo "    main() entry     = $MAIN_ADDR"

# ---------------------------------------------------------------------------
# Step 3: Create output directory
# ---------------------------------------------------------------------------
mkdir -p "$OUTPUT_DIR"

# ---------------------------------------------------------------------------
# Step 4: Start OpenOCD in background on port 3333
# ---------------------------------------------------------------------------
echo "=== Starting OpenOCD ==="
"$OPENOCD" -f "$OPENOCD_CFG" &
OPENOCD_PID=$!
trap 'echo "Killing OpenOCD (PID $OPENOCD_PID)"; kill "$OPENOCD_PID" 2>/dev/null || true' EXIT

# Wait for OpenOCD to initialise and connect to the FPGA
sleep 3

# ---------------------------------------------------------------------------
# Step 5: Run GDB session — load firmware, set hardware breakpoints, dump SRAM
#
# The GDB script (gdb_dump.gdb) does:
#   1. monitor reset halt  — stop CPU, clear any stale state
#   2. load               — flash firmware.elf into SRAM
#   3. hbreak *0x88       — hardware BP at main() entry
#   4. hbreak *0x416      — hardware BP at main() ret (after 45 update() calls)
#   5. continue x2        — run through both breakpoints
#   6. dump binary memory — read 12288 bytes of arc_table from SRAM to disk
#   7. quit               — disconnect; OpenOCD trap will kill it
# ---------------------------------------------------------------------------
echo "=== Running GDB arc_table dump ==="
timeout 120 "$GDB" -batch \
    -ex "set confirm off" \
    -ex "set pagination off" \
    -x "$GDB_SCRIPT" \
    "$FIRMWARE" || true
# GDB exits cleanly after 'quit'.  'true' prevents set -e from aborting on
# non-zero exit codes from GDB remote-protocol teardown.

# ---------------------------------------------------------------------------
# Step 6: Parse arc_table.bin -> gmon.out
# ---------------------------------------------------------------------------
ARC_BIN="$OUTPUT_DIR/arc_table.bin"
GMON_OUT="$OUTPUT_DIR/gmon.out"

if [ ! -f "$ARC_BIN" ]; then
    echo "ERROR: $ARC_BIN not produced by GDB dump — check JTAG connection and addresses." >&2
    exit 1
fi

echo "=== Parsing arc_table.bin -> gmon.out ==="
python3 "$PARSE_SCRIPT" "$ARC_BIN" "$GMON_OUT"

# ---------------------------------------------------------------------------
# Step 7: Summary
# ---------------------------------------------------------------------------
echo ""
echo "=== Done ==="
echo "  arc_table binary : $ARC_BIN"
echo "  gmon.out         : $GMON_OUT"
echo "  Run scripts/combine_report.sh to generate the gprof call-graph report."
