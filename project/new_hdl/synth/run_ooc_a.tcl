# run_ooc_a.tcl — Out-of-Context ASIC-like synthesis, Option A
# Non-project mode (no .xpr needed). Produces ASIC-representative results.
# Run: vivado -mode batch -source synth/run_ooc_a.tcl

set hdl_dir [pwd]
set rpt_dir    "$hdl_dir/reports"
file mkdir $rpt_dir

read_verilog -sv [list \
    "$hdl_dir/rtl/f64_mul.sv" \
    "$hdl_dir/rtl/f64_add.sv" \
    "$hdl_dir/rtl/gemm_systolic.sv" \
    "$hdl_dir/rtl/axilite_slave.sv" \
    "$hdl_dir/rtl/accel_top_a.sv" ]

synth_design -top accel_top_a \
             -mode out_of_context \
             -part xc7a100tcsg324-1

# Apply timing constraints after synthesis (OOC mode)
create_clock -period 10.000 -name clk [get_ports clk]
# set_input_delay on all_inputs — Vivado auto-ignores the constraint on the clock port
set_input_delay  2.0 -clock clk [all_inputs]
set_output_delay 2.0 -clock clk [all_outputs]

report_utilization    -file "$rpt_dir/ooc_a_utilization.rpt"
report_timing_summary -file "$rpt_dir/ooc_a_timing.rpt"
report_power          -file "$rpt_dir/ooc_a_power.rpt"

puts "INFO: Option A OOC synthesis complete. Reports in $rpt_dir"
