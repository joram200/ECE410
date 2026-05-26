#!/usr/bin/env bash
# run_m3.sh — M3 submission orchestration for project/m3/ (Option B only)
# Run from project/m3/ directory:
#   cd project/m3 && bash run_m3.sh
#
# Differences from new_hdl/run_m3.sh:
#   - Single combined RTL file (rtl/top.sv) and TB file (tb/tb_top.sv)
#   - Uses xvlog/xelab/xsim in non-project mode for simulation
#     (working directory is project/m3/, so $dumpfile("sim/cosim_waveform.vcd")
#      resolves correctly without Vivado project-dir complications)
#   - Vivado OOC synthesis via synth/run_ooc.tcl (non-project mode)
#   - Synthesis log captured to synth/openlane_run.log (M3 checklist path)
#   - GTKWave PNG export is non-fatal (skipped if gtkwave not installed)
#   - No Option A; no SoC integration step
#
# Checkpoint mechanism: touch .STOP to halt at the next step boundary.
# Remove .STOP to resume.

set -euo pipefail
cd "$(dirname "${BASH_SOURCE[0]}")"

STOP_FILE=".STOP"
VIVADO="${VIVADO:-vivado}"
GTKWAVE="${GTKWAVE:-gtkwave}"
XVLOG="${XVLOG:-xvlog}"
XELAB="${XELAB:-xelab}"
XSIM="${XSIM:-xsim}"

check_stop() {
    if [ -f "$STOP_FILE" ]; then
        echo "Halted before: $1"
        exit 0
    fi
}

# ─── Step 0: Create output directories ──────────────────────────────────────
check_stop "mkdir"
mkdir -p sim synth reports

# ─── Step 1: Check rtl/top.sv ────────────────────────────────────────────────
check_stop "check_rtl"
[ -f rtl/top.sv ] || { echo "MISSING: rtl/top.sv"; exit 1; }
echo "OK: rtl/top.sv found"

# ─── Step 2: Check tb/tb_top.sv ──────────────────────────────────────────────
check_stop "check_tb"
[ -f tb/tb_top.sv ] || { echo "MISSING: tb/tb_top.sv"; exit 1; }
echo "OK: tb/tb_top.sv found"

# ─── Step 3: Check synth/constraints.xdc ────────────────────────────────────
check_stop "check_constraints"
[ -f synth/constraints.xdc ] || { echo "MISSING: synth/constraints.xdc"; exit 1; }
echo "OK: synth/constraints.xdc found"

# ─── Step 4: Compile RTL and TB (xvlog, non-project mode) ───────────────────
check_stop "compile"
echo "Compiling RTL and TB..."
$XVLOG --sv rtl/top.sv tb/tb_top.sv \
    --log reports/compile.log \
    && echo "Compilation OK." \
    || { echo "ERROR: Compilation failed — check reports/compile.log"; exit 1; }

# ─── Step 5: Elaborate simulation snapshot ──────────────────────────────────
check_stop "elaborate"
echo "Elaborating tb_top..."
$XELAB tb_top \
    -s m3_snap \
    -debug typical \
    --log reports/elab.log \
    && echo "Elaboration OK." \
    || { echo "ERROR: Elaboration failed — check reports/elab.log"; exit 1; }

# ─── Step 6: Run simulation — capture log to sim/cosim_run.log ──────────────
check_stop "run_sim"
echo "Running simulation..."
$XSIM m3_snap \
    --runall \
    --log sim/cosim_run.log \
    && echo "Simulation complete — see sim/cosim_run.log" \
    || echo "WARNING: Simulation returned non-zero — check sim/cosim_run.log for PASS/FAIL"

# Echo the verdict line from the log so it appears in the terminal
if grep -q "SIMULATION RESULT:" sim/cosim_run.log 2>/dev/null; then
    grep "SIMULATION RESULT:" sim/cosim_run.log
else
    echo "WARNING: SIMULATION RESULT line not found in cosim_run.log"
fi

# ─── Step 7: Export annotated waveform PNG (non-fatal) ──────────────────────
check_stop "gen_waveform"
if [ -f sim/cosim_waveform.vcd ]; then
    if command -v "$GTKWAVE" &>/dev/null; then
        echo "Exporting annotated waveform PNG..."
        $GTKWAVE sim/cosim_waveform.vcd \
            --script synth/gtkwave_export.tcl \
            -o sim/cosim_waveform.png \
            && echo "Waveform PNG saved to sim/cosim_waveform.png" \
            || echo "WARNING: gtkwave export failed — open sim/cosim_waveform.vcd manually to create sim/cosim_waveform.png"
    else
        echo "WARNING: gtkwave not found in PATH."
        echo "  To create sim/cosim_waveform.png, run:"
        echo "  gtkwave sim/cosim_waveform.vcd --script synth/gtkwave_export.tcl -o sim/cosim_waveform.png"
    fi
else
    echo "WARNING: sim/cosim_waveform.vcd not found — VCD dump may have failed."
    echo "  Check that \$dumpfile(\"sim/cosim_waveform.vcd\") ran in the testbench."
fi

# ─── Step 8: OOC synthesis (Vivado non-project mode) ────────────────────────
check_stop "run_ooc"
echo "Running Vivado OOC synthesis..."
$VIVADO -mode batch \
    -source synth/run_ooc.tcl \
    -log synth/openlane_run.log \
    -journal reports/ooc.jou \
    && echo "OOC synthesis done." \
    || { echo "ERROR: OOC synthesis failed — check synth/openlane_run.log"; exit 1; }

echo ""
echo "=== M3 deliverables ==="
echo "  sim/cosim_run.log          — simulation transcript (check for SIMULATION RESULT: PASS)"
echo "  sim/cosim_waveform.vcd     — raw VCD waveform"
echo "  sim/cosim_waveform.png     — annotated PNG (if gtkwave ran successfully)"
echo "  synth/openlane_run.log     — Vivado OOC synthesis log"
echo "  synth/area_report.txt      — utilisation / area report"
echo "  synth/timing_report.txt    — timing summary (WNS, WHS, critical path)"
echo "  synth/power_report.txt     — power estimate"
echo ""
echo "=== M3 run complete. ==="
