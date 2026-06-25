# run_sim_a.tcl — Behavioral simulation for Option A
# Requires vivado_option_a project to exist (run create_project_a.tcl first)
# Run: vivado -mode batch -source synth/run_sim_a.tcl

set hdl_dir [pwd]

open_project "$hdl_dir/vivado_option_a/vivado_option_a.xpr"
set_property top          tb_option_a    [get_filesets sim_1]
set_property top_lib      xil_defaultlib [get_filesets sim_1]

launch_simulation -mode behavioral -simset [get_filesets sim_1]
run all
close_sim
close_project
puts "INFO: Option A simulation complete."
