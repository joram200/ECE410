# run_ooc.tcl — Vivado Out-of-Context synthesis for 'top' (Option B, M4)
# Non-project mode. Reads from rtl/ (3 files: compute_core.sv, interface.sv, top.sv).
# Run from project/m4/ directory:
#   vivado -mode batch -source synth/run_ooc.tcl \
#          -log synth/openlane_run.log -journal reports/ooc.jou
#
# Replaces OpenLane 2 synthesis. Reports go to synth/ to match M4 checklist paths.
# constraints.xdc serves the role of OpenLane's config.json: it specifies the
# target clock period (10 ns / 100 MHz), I/O delays, and part number.

set base [file normalize [pwd]]
set rpt_dir "$base/synth"

# Ensure synth/ directory exists
file mkdir $rpt_dir

# Read RTL (3 files: compute_core → interface → top, dependency order)
read_verilog -sv "$base/rtl/compute_core.sv"
read_verilog -sv "$base/rtl/interface.sv"
read_verilog -sv "$base/rtl/top.sv"

# Synthesize in OOC mode (no I/O buffers; models accelerator as black-box sub-IP)
synth_design -top top \
             -mode out_of_context \
             -part xc7a100tcsg324-1

# Apply timing constraints (matches constraints.xdc)
create_clock -period 10.000 -name clk [get_ports clk]
set_input_delay  2.0 -clock clk [all_inputs]
set_output_delay 2.0 -clock clk [all_outputs]

# Generate checklist reports
report_utilization    -file "$rpt_dir/area_report.txt"
report_timing_summary -file "$rpt_dir/timing_report.txt"
report_timing -max_paths 30 -nworst 1 -path_type full \
              -file "$rpt_dir/critical_paths.txt"
report_power          -file "$rpt_dir/power_report.txt"

puts "INFO: OOC synthesis complete. Reports in $rpt_dir"
puts "INFO: area_report.txt / timing_report.txt / power_report.txt generated."
