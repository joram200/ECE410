# run_ooc.tcl — Vivado Out-of-Context synthesis for 'top' (Option B)
# Non-project mode. Reads from rtl/top.sv (single combined file).
# Run from project/m3/ directory:
#   vivado -mode batch -source synth/run_ooc.tcl \
#          -log synth/openlane_run.log -journal reports/ooc.jou
#
# Replaces OpenLane 2 synthesis. Reports go to synth/ to match M3 checklist paths.

set base [file normalize [pwd]]
set rpt_dir "$base/synth"

# Ensure synth/ directory exists
file mkdir $rpt_dir

# Read combined RTL (all modules in one file)
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
report_power          -file "$rpt_dir/power_report.txt"

puts "INFO: OOC synthesis complete. Reports in $rpt_dir"
puts "INFO: area_report.txt / timing_report.txt / power_report.txt generated."
