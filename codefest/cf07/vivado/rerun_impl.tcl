open_project /home/sackb/Documents/Vivado_Projects/ece410sp26/cf07/cf07.xpr

# Add the constraints file if not already in the project
set constrs_files [get_files -of_objects [get_filesets constrs_1]]
set xdc_path "/home/sackb/Documents/Vivado_Projects/ece410sp26/cf07/cf07.srcs/constrs_1/imports/src/crossbar_mac.xdc"
if {[lsearch $constrs_files $xdc_path] < 0} {
    add_files -fileset constrs_1 $xdc_path
}

# Reset and rerun synthesis then implementation
reset_run synth_1
launch_runs synth_1 -jobs 4
wait_on_run synth_1

reset_run impl_1
launch_runs impl_1 -jobs 4
wait_on_run impl_1

# Regenerate reports
open_run impl_1
report_timing_summary -max_paths 10 -report_unconstrained \
    -file /home/sackb/Documents/Vivado_Projects/ece410sp26/cf07/impl_timing_summary.rpt
report_utilization \
    -file /home/sackb/Documents/Vivado_Projects/ece410sp26/cf07/impl_utilization.rpt

puts "Done. Reports written to cf07 directory."
