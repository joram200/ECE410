# Remaining Tasks Before M4

## 1. Add a state-retention control bit to eliminate P_in / x_in re-writes each iteration

In `axilite_slave` (offset 0x00 CTRL register), add bit[2] as `retain_state`. When set, the FSM
automatically feeds `x_out[0:2]` back into `x_in[0:2]` and `P_out[0:8]` back into `P_in[0:8]`
at the end of DONE_S state using internal wires (already routed in the existing datapath). The CPU
then only needs to write z (1 write) and read x_out/P_out (12 reads) = 13 transactions instead
of 34, reducing per-update MMIO latency from ~87.8 µs to ~33 µs (~2.7× throughput gain).

## 2. Replace 34 individual AXI4-Lite transactions with one AXI4 burst write for the input block

Extend the AXI slave from AXI4-Lite (no burst) to AXI4 with `AWLEN` support for the input
register window (z at 0x10 through P_in[8] at 0x98, 12 consecutive 64-bit registers). Change
`s_awlen` from tied-zero to an 8-bit input in `top.sv`; update the write-state FSM in
`axilite_slave` to accept `WVALID` beats for `wlen+1` cycles before asserting `BVALID`. The
CPU driver writes one `AWADDR=0x10, AWLEN=11` transaction instead of 12 separate handshakes,
eliminating 11 × (AW + B) round-trip latencies (~28 µs savings at 13 MHz).

## 3. Clock the Kalman accelerator at 100 MHz with an async FIFO crossing to the 13 MHz SoC bus

The OOC synthesis achieves WNS = +0.326 ns at 100 MHz. Add a 2-entry async FIFO (Gray-coded
CDC) on the AXI request/response ports between the 13 MHz AXI crossbar clock domain and a
100 MHz accelerator clock domain in `veerwolf_core.v`. The MMIO transaction latency is then
dominated by the CDC crossing overhead (~3 fast cycles ≈ 30 ns) plus the 14-state FSM at
100 MHz (140 ns), reducing compute time from 1.08 µs to 0.17 µs and allowing higher sustained
throughput if multiple accelerator instances are pipelined in the future. The crossing also
enables the standalone 100 MHz accelerator to be reused as a future hard-IP primitive.
