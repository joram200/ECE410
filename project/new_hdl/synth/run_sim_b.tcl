# run_sim_b.tcl — Behavioral simulation for Option B
# Requires vivado_option_b project to exist (run create_project_b.tcl first)
# Run: vivado -mode batch -source synth/run_sim_b.tcl

set hdl_dir [pwd]

open_project "$hdl_dir/vivado_option_b/vivado_option_b.xpr"
set_property top          tb_option_b    [get_filesets sim_1]
set_property top_lib      xil_defaultlib [get_filesets sim_1]

launch_simulation -mode behavioral -simset [get_filesets sim_1]
run all
close_sim
close_project
puts "INFO: Option B simulation complete."
