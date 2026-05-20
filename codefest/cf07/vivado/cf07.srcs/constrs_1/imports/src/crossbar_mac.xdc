# -----------------------------------------------------------------------------
# Out-of-Context (ASIC-style) constraints for crossbar_mac
# No IBUF/OBUF inserted; ports treated as internal signals.
# -----------------------------------------------------------------------------

# Clock: 100 MHz (10 ns period)
create_clock -add -name sys_clk_pin -period 10.00 -waveform {0 5} [get_ports {clk}]

# I/O timing: assume signals arrive/must be ready 2 ns from the clock edge
set_input_delay  -clock sys_clk_pin 2.0 [get_ports {rst we w_val w_row w_col in[*]}]
set_output_delay -clock sys_clk_pin 2.0 [get_ports {out[*]}]
