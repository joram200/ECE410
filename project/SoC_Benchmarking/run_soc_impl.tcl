# run_soc_impl.tcl — Kalman SoC integration: synthesis, implementation, bitstream
#
# Adds the Kalman accelerator (top.sv) to the existing VeeRwolf SoC Vivado project,
# runs the full implementation flow, and copies all reports to SoC_Benchmarking/reports/.
#
# Usage (run from project/SoC_Benchmarking/):
#   vivado -mode batch -source run_soc_impl.tcl \
#          -log reports/vivado_run.log -journal reports/vivado_run.jou
#
# Accelerator address: 0x80010000–0x80011000 (4 KB AXI4-Lite slave)

set script_dir  [file normalize [file dirname [info script]]]
set project_xpr [file join $script_dir SoC_impl SoC_impl.xpr]
set top_sv      [file normalize [file join $script_dir .. post_m3_Minor_Redesign rtl top.sv]]
set rpt_dir     [file join $script_dir reports]

file mkdir $rpt_dir

puts "=== Opening project: $project_xpr ==="
open_project $project_xpr

# Add top.sv (Kalman accelerator) if not already present
if {[llength [get_files -quiet $top_sv]] == 0} {
    add_files -norecurse -fileset [get_filesets sources_1] $top_sv
    set_property file_type SystemVerilog [get_files $top_sv]
    puts "Added Kalman top.sv: $top_sv"
} else {
    puts "Kalman top.sv already in project: $top_sv"
}

# Ensure the synthesis top is rvfpganexys (not the module named 'top')
set_property top rvfpganexys [get_filesets sources_1]
puts "Top module: [get_property top [get_filesets sources_1]]"

# Fix include directories — the .xpr references $PPRDIR/../../ece540_RVfpga which is in the
# ECE540 course directory. The include files are also imported locally into the project.
# Set include_dirs on the fileset and synth run to point to the local copies.
set src_base [file join $script_dir SoC_impl SoC_impl.srcs sources_1 imports src]
set axi_inc  [file join $src_base VeeRwolf Interconnect AxiInterconnect pulp-platform.org__axi_0.25.0 include]
set cc_inc   [file join $src_base OtherSources pulp-platform.org__common_cells_1.20.0 include]
puts "AXI include dir    : $axi_inc"
puts "CommonCells inc dir: $cc_inc"
set_property include_dirs [list $axi_inc $cc_inc] [get_filesets sources_1]

# Force clean re-run from synthesis to pick up RTL changes
reset_run synth_1
reset_run impl_1

# Re-apply include dirs after reset (reset_run clears run-level properties)
set_property include_dirs [list $axi_inc $cc_inc] [get_filesets sources_1]

# ── Synthesis ────────────────────────────────────────────────────────────────
puts "=== Launching synthesis ==="
launch_runs synth_1 -jobs 4
wait_on_run synth_1
set synth_status [get_property STATUS [get_runs synth_1]]
set synth_prog   [get_property PROGRESS [get_runs synth_1]]
puts "Synthesis: status=$synth_status progress=$synth_prog"
if {$synth_prog != "100%"} {
    error "Synthesis did not complete: $synth_status"
}

# Copy synthesis reports
set synth_dir [file join $script_dir SoC_impl SoC_impl.runs synth_1]
foreach f [glob -nocomplain [file join $synth_dir *.rpt]] {
    file copy -force $f $rpt_dir/
    puts "  Copied: [file tail $f]"
}

# ── Implementation ───────────────────────────────────────────────────────────
puts "=== Launching implementation ==="
launch_runs impl_1 -jobs 4
wait_on_run impl_1
set impl_status [get_property STATUS [get_runs impl_1]]
set impl_prog   [get_property PROGRESS [get_runs impl_1]]
puts "Implementation: status=$impl_status progress=$impl_prog"
if {$impl_prog != "100%"} {
    error "Implementation did not complete: $impl_status"
}

# Copy implementation reports
set impl_dir [file join $script_dir SoC_impl SoC_impl.runs impl_1]
foreach f [glob -nocomplain [file join $impl_dir *.rpt]] {
    file copy -force $f $rpt_dir/
    puts "  Copied: [file tail $f]"
}

# ── Bitstream ────────────────────────────────────────────────────────────────
puts "=== Generating bitstream ==="
launch_runs impl_1 -to_step write_bitstream -jobs 4
wait_on_run impl_1
puts "Bitstream complete."

# Final report copy (in case write_bitstream generates additional files)
foreach f [glob -nocomplain [file join $impl_dir *.rpt]] {
    file copy -force $f $rpt_dir/
}

set bit_file [file join $impl_dir rvfpganexys.bit]
if {[file exists $bit_file]} {
    puts "=== SUCCESS ==="
    puts "Bitstream : $bit_file"
} else {
    puts "WARNING: Bitstream file not found at expected path: $bit_file"
}
puts "Reports   : $rpt_dir"
