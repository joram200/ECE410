# constraints.xdc — Vivado Design Constraints for 'top' (Option B Kalman accelerator)
# Target device: Artix-7 100T (xc7a100tcsg324-1)
# Clock frequency: 100 MHz (10 ns period)
# Replaces the OpenLane 2 config.json for Vivado OOC synthesis.
#
# Usage (non-project OOC mode): constraints applied inline in run_ooc.tcl
# Usage (project mode):         add_files -fileset constrs_1 synth/constraints.xdc

create_clock -period 10.000 -name clk [get_ports clk]
set_input_delay  -clock clk -max 2.0 [all_inputs]
set_output_delay -clock clk -max 2.0 [all_outputs]
