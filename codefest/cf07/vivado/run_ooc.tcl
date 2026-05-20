set proj /run/media/sackb/Windows-SSD/Users/sackb/OneDrive/Desktop/University/Course_Work/2025-2026/Spring_2026/ECE_410/ECE410/codefest/cf07/vivado/cf07.xpr
set rpt_dir /run/media/sackb/Windows-SSD/Users/sackb/OneDrive/Desktop/University/Course_Work/2025-2026/Spring_2026/ECE_410/ECE410/codefest/cf07/synth

open_project $proj

# --- Synthesis: set OOC mode ---
set_property -name {STEPS.SYNTH_DESIGN.ARGS.MORE OPTIONS} \
    -value {-mode out_of_context} \
    -objects [get_runs synth_1]

reset_run synth_1
launch_runs synth_1 -jobs 4
wait_on_run synth_1
if {[get_property PROGRESS [get_runs synth_1]] != "100%"} {
    error "Synthesis failed"
}

# --- Implementation ---
reset_run impl_1
launch_runs impl_1 -jobs 4
wait_on_run impl_1
if {[get_property PROGRESS [get_runs impl_1]] != "100%"} {
    error "Implementation failed"
}

# --- Reports ---
open_run impl_1

file mkdir $rpt_dir

report_timing_summary \
    -max_paths 10 \
    -report_unconstrained \
    -file $rpt_dir/timing_summary.rpt

report_utilization \
    -file $rpt_dir/utilization.rpt

report_methodology \
    -file $rpt_dir/methodology.rpt

report_drc \
    -file $rpt_dir/drc.rpt

puts "Done. Reports written to $rpt_dir"
