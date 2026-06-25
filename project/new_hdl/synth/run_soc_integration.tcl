# run_soc_integration.tcl — Run 2: integrate winning option into VeerWolf SoC
# Opens project_1.xpr (full RVfpga SoC) and adds accelerator RTL.
# Prerequisites (manual steps before running this script):
#   1. axi_intercon.sv: NoSlaves 2→3, AddrMap add 0x80010000–0x80011000, o_accel_* ports
#   2. axi_intercon.vh: o_accel_* wire declarations added
#   3. VeerWolf wrapper: accel_top_a instantiated with clk_i/rst_ni and o_accel_* wires
# Run: vivado -mode batch -source synth/run_soc_integration.tcl

set script_dir [file normalize [file dirname [info script]]]
set hdl_dir    [file normalize "$script_dir/.."]
set proj_dir   [file normalize "$hdl_dir/../project_1"]
set rpt_dir    "$hdl_dir/reports"
file mkdir $rpt_dir

# Open the existing SoC project (contains VeerWolf, LiteDRAM, board constraints)
open_project "$proj_dir/project_1.xpr"

# Add winning option RTL files to sources_1
# Swap accel_top_b.sv + kalman_update.sv here if Option B wins
add_files -fileset sources_1 [list \
    "$hdl_dir/rtl/f64_mul.sv" \
    "$hdl_dir/rtl/f64_add.sv" \
    "$hdl_dir/rtl/gemm_systolic.sv" \
    "$hdl_dir/rtl/axilite_slave.sv" \
    "$hdl_dir/rtl/accel_top_a.sv" ]

# Ensure SystemVerilog file type is set for any files not auto-detected
set_property file_type {SystemVerilog} \
    [get_files -filter {FILE_TYPE == Verilog} -of_objects [get_filesets sources_1]]

# Reset synthesis and implementation runs to force re-elaboration with new sources
reset_run synth_1
reset_run impl_1

# Run synthesis
launch_runs synth_1 -jobs 4
wait_on_run synth_1
if {[get_property PROGRESS [get_runs synth_1]] != "100%"} {
    error "Synthesis failed — check synth_1 log"
}

# Run implementation (place and route)
launch_runs impl_1 -jobs 4
wait_on_run impl_1
if {[get_property PROGRESS [get_runs impl_1]] != "100%"} {
    error "Implementation failed — check impl_1 log"
}

# Collect post-route reports
open_run impl_1
report_utilization    -file "$rpt_dir/soc_utilization.rpt" -force
report_timing_summary -file "$rpt_dir/soc_timing.rpt"      -force
report_drc            -file "$rpt_dir/soc_drc.rpt"         -force

close_project
puts "INFO: SoC integration complete. Reports in $rpt_dir"
