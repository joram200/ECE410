#!/usr/bin/env bash
# run_m3.sh — M3 orchestration script
# Run from project/new_hdl/ directory.
# To halt at any step boundary: touch .STOP
# To resume: rm .STOP
set -euo pipefail
cd "$(dirname "${BASH_SOURCE[0]}")"

STOP_FILE=".STOP"
VIVADO="${VIVADO:-vivado}"

check_stop() {
    if [ -f "$STOP_FILE" ]; then
        echo "Halted before: $1"
        exit 0
    fi
}

# ─── Step 0: Directories ────────────────────────────────────────────────────
check_stop "mkdir"
mkdir -p rtl tb synth reports

# ─── Steps 1–5c: RTL file presence checks ───────────────────────────────────
check_stop "f64_mul"
[ -f rtl/f64_mul.sv ]       || { echo "MISSING: rtl/f64_mul.sv";       exit 1; }

check_stop "f64_add"
[ -f rtl/f64_add.sv ]       || { echo "MISSING: rtl/f64_add.sv";       exit 1; }

check_stop "gemm_systolic"
[ -f rtl/gemm_systolic.sv ] || { echo "MISSING: rtl/gemm_systolic.sv"; exit 1; }

check_stop "kalman_update"
[ -f rtl/kalman_update.sv ] || { echo "MISSING: rtl/kalman_update.sv"; exit 1; }

check_stop "axilite_slave"
[ -f rtl/axilite_slave.sv ] || { echo "MISSING: rtl/axilite_slave.sv"; exit 1; }

check_stop "accel_top_a"
[ -f rtl/accel_top_a.sv ]   || { echo "MISSING: rtl/accel_top_a.sv";   exit 1; }

check_stop "accel_top_b"
[ -f rtl/accel_top_b.sv ]   || { echo "MISSING: rtl/accel_top_b.sv";   exit 1; }

check_stop "clk_gen"
[ -f rtl/clk_gen.sv ]       || { echo "MISSING: rtl/clk_gen.sv";       exit 1; }

# ─── Steps 7–12: TB file presence checks ────────────────────────────────────
check_stop "veerwolf_bfm"
[ -f tb/veerwolf_bfm.sv ]   || { echo "MISSING: tb/veerwolf_bfm.sv";   exit 1; }

check_stop "axi_monitor"
[ -f tb/axi_monitor.sv ]    || { echo "MISSING: tb/axi_monitor.sv";    exit 1; }

check_stop "checker"
[ -f tb/checker.sv ]        || { echo "MISSING: tb/checker.sv";        exit 1; }

check_stop "program_block"
[ -f tb/program_block.sv ]  || { echo "MISSING: tb/program_block.sv";  exit 1; }

check_stop "tb_option_a"
[ -f tb/tb_option_a.sv ]    || { echo "MISSING: tb/tb_option_a.sv";    exit 1; }

check_stop "tb_option_b"
[ -f tb/tb_option_b.sv ]    || { echo "MISSING: tb/tb_option_b.sv";    exit 1; }

# ─── Step 13: Create Option A project (non-fatal; required only for simulation) ─
check_stop "create_project_a"
echo "Creating Vivado Option A project..."
$VIVADO -mode batch -source synth/create_project_a.tcl \
    -log reports/create_a.log -journal reports/create_a.jou \
    && echo "Option A project created." \
    || echo "WARNING: Option A project creation had errors — check reports/create_a.log"

# ─── Step 14: Create Option B project (non-fatal) ───────────────────────────
check_stop "create_project_b"
echo "Creating Vivado Option B project..."
$VIVADO -mode batch -source synth/create_project_b.tcl \
    -log reports/create_b.log -journal reports/create_b.jou \
    && echo "Option B project created." \
    || echo "WARNING: Option B project creation had errors — check reports/create_b.log"

# ─── Step 15: Simulate Option A (non-fatal — OOC synthesis continues regardless) ─
check_stop "run_sim_a"
echo "Running Option A simulation..."
$VIVADO -mode batch -source synth/run_sim_a.tcl \
    -log reports/sim_a.log -journal reports/sim_a.jou \
    && echo "Option A simulation done." \
    || echo "WARNING: Option A simulation had errors — check reports/sim_a.log"

# ─── Step 16: Simulate Option B (non-fatal) ─────────────────────────────────
check_stop "run_sim_b"
echo "Running Option B simulation..."
$VIVADO -mode batch -source synth/run_sim_b.tcl \
    -log reports/sim_b.log -journal reports/sim_b.jou \
    && echo "Option B simulation done." \
    || echo "WARNING: Option B simulation had errors — check reports/sim_b.log"

# ─── Step 17: OOC synthesis Option A ────────────────────────────────────────
check_stop "run_ooc_a"
echo "Running Option A OOC synthesis..."
$VIVADO -mode batch -source synth/run_ooc_a.tcl \
    -log reports/ooc_a.log -journal reports/ooc_a.jou
echo "Option A OOC done — see reports/ooc_a_*.rpt"

# ─── Step 18: OOC synthesis Option B ────────────────────────────────────────
check_stop "run_ooc_b"
echo "Running Option B OOC synthesis..."
$VIVADO -mode batch -source synth/run_ooc_b.tcl \
    -log reports/ooc_b.log -journal reports/ooc_b.jou
echo "Option B OOC done — see reports/ooc_b_*.rpt"

echo ""
echo "=== Run 1 complete. Review reports/ before proceeding to Run 2. ==="
echo "=== Steps 21-23 require manual edits to axi_intercon.sv, axi_intercon.vh,"
echo "=== and the VeerWolf wrapper before running Run 2. ==="
echo ""

# Auto-stop after step 18 so Run 2 is not triggered automatically
touch "$STOP_FILE"

# ─── Steps 20–23: SoC source edits (manual; verified before this point) ─────
check_stop "soc_source_edits"
# If this check_stop is reached, the manual edits have been confirmed done.
# Remove .STOP to continue into Run 2.

# ─── Step 24: SoC integration synthesis ─────────────────────────────────────
check_stop "run_soc_integration"
[ -f synth/run_soc_integration.tcl ] || { echo "MISSING: synth/run_soc_integration.tcl"; exit 1; }
echo "Running SoC integration synthesis..."
$VIVADO -mode batch -source synth/run_soc_integration.tcl \
    -log reports/soc_integration.log -journal reports/soc_integration.jou
echo "SoC integration done — see reports/soc_*.rpt"

echo ""
echo "=== All M3 steps complete (Run 1 + Run 2). ==="
