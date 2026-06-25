# create_project_b.tcl — Create Option B Vivado project (sim + OOC synth)
# Run from project/new_hdl/ as working directory:
#   vivado -mode batch -source synth/create_project_b.tcl

set hdl_dir [pwd]

create_project vivado_option_b "$hdl_dir/vivado_option_b" \
    -part xc7a100tcsg324-1 -force

# RTL sources — add one file at a time to avoid NTFS glob-match issues
foreach f [list \
    "$hdl_dir/rtl/f64_mul.sv" \
    "$hdl_dir/rtl/f64_add.sv" \
    "$hdl_dir/rtl/gemm_systolic.sv" \
    "$hdl_dir/rtl/kalman_update.sv" \
    "$hdl_dir/rtl/axilite_slave.sv" \
    "$hdl_dir/rtl/accel_top_b.sv" ] {
    if {[file exists $f]} {
        add_files -fileset [get_filesets sources_1] $f
        puts "INFO: Added source: $f"
    } else {
        puts "WARNING: File not found: $f"
    }
}

set_property top accel_top_b [get_filesets sources_1]

# TB and sim-only files
foreach f [list \
    "$hdl_dir/rtl/clk_gen.sv" \
    "$hdl_dir/tb/veerwolf_bfm.sv" \
    "$hdl_dir/tb/axi_monitor.sv" \
    "$hdl_dir/tb/checker.sv" \
    "$hdl_dir/tb/program_block.sv" \
    "$hdl_dir/tb/tb_option_b.sv" ] {
    if {[file exists $f]} {
        add_files -fileset [get_filesets sim_1] $f
        puts "INFO: Added sim file: $f"
    } else {
        puts "WARNING: File not found: $f"
    }
}

set_property top     tb_option_b    [get_filesets sim_1]
set_property top_lib xil_defaultlib [get_filesets sim_1]

close_project
puts "INFO: vivado_option_b project created."
