# Code Review

I decided to choose the LLMs claude Sonnet 4.6 and gpt-5.4 thorugh each of their respective CLI.

## System Verilog Code Generation

The following prompt was entered into both LLMs:  
```
Implement a System Verilog Module with the specifications below.

Module name: mac
Inputs: clk (1-bit), rst (1-bit, active-high synchronous reset), a (8-bit signed), b (8-bit
signed)
Output: out (32-bit signed accumulator)
Behavior: On each rising clock edge: if rst is high, set out to 0; else add a×b to out.
Constraints: Synthesizable SystemVerilog only. No initial blocks, no $display, no delays
(#). Use always_ff.

Make sure that the final result is stored into a register that is connectted to out
```
Claude hdl is `mac_llm_A.v` while gpt is `mac_llm_B.v`  

## Verilator Compile

The command `verilator --lint-only --language 1800-2023` hadn't produced any errors by either LLM HDL.

## Testbench and Simulation

The testbench `mac_tb.v` was first linted with `verilator --lint-only`, then compiled and simulated using `verilator --binary --timing` against each LLM's implementation separately (both modules share the name `mac`).

```
verilator --lint-only mac_llm_A.v mac_tb.v   # no errors
verilator --lint-only mac_llm_B.v mac_tb.v   # no errors
```

The testbench applies `[a=3, b=4]` for 3 cycles, asserts `rst` for 1 cycle, then applies `[a=-5, b=2]` for 2 cycles (preceded by a reset cycle at startup).

**mac_llm_A simulation output:**
```
Cycle 1 | rst=1 a=0  b=0 | out=0
Cycle 2 | rst=0 a=3  b=4 | out=12
Cycle 3 | rst=0 a=3  b=4 | out=24
Cycle 4 | rst=0 a=3  b=4 | out=36
Cycle 5 | rst=1 a=3  b=4 | out=0
Cycle 6 | rst=0 a=-5 b=2 | out=-10
Cycle 7 | rst=0 a=-5 b=2 | out=-20
```

**mac_llm_B simulation output:**
```
Cycle 1 | rst=1 a=0  b=0 | out=0
Cycle 2 | rst=0 a=3  b=4 | out=12
Cycle 3 | rst=0 a=3  b=4 | out=24
Cycle 4 | rst=0 a=3  b=4 | out=36
Cycle 5 | rst=1 a=3  b=4 | out=0
Cycle 6 | rst=0 a=-5 b=2 | out=-10
Cycle 7 | rst=0 a=-5 b=2 | out=-20
```

Both implementations produce identical, correct output. No lint errors or simulation warnings.

## Issues

### Issue 1 — Missing `timescale` directive (both files)

**(a) Offending lines:**
```verilog
// mac_llm_A.v line 1
module mac (

// mac_llm_B.v line 1
module mac (
```
Neither file has a `` `timescale `` directive before the module declaration.

**(b) Why it is wrong:**  
Without a `` `timescale ``, the time unit and precision of the module are undefined. When compiled alongside a testbench that declares `` `timescale 1ns/1ps ``, verilator raised a `TIMESCALEMOD` warning and exited with an error — the testbench had to have its own timescale removed as a workaround. In a multi-module project, a DUT without a timescale inherits whatever the simulator picks, making delay-sensitive behaviour tool-dependent and non-portable.

**(c) Corrected version:**
```verilog
`timescale 1ns/1ps
module mac (
    ...
```

---

### Issue 2 — `out` is directly inferred as a flip-flop (mac_llm_A.v)

**(a) Offending lines:**
```verilog
output logic signed [31:0] out
...
always_ff @(posedge clk) begin
    if (rst)
        out <= 32'sd0;
    else
        out <= out + (a * b);
end
```

**(b) Why it is wrong:**  
The prompt explicitly required "the final result is stored into a register that is **connected to** `out`" — meaning a separate internal register that drives the port. Driving the output port directly from `always_ff` makes `out` itself the flip-flop storage element rather than a wire connected to one. This violates the spec's intent and is also problematic in synthesis: output ports inferred as registers complicate I/O timing constraints, and most RTL coding guidelines prohibit registering directly on output ports.

**(c) Corrected version:**
```verilog
logic signed [31:0] acc_reg;

always_ff @(posedge clk) begin
    if (rst)
        acc_reg <= 32'sd0;
    else
        acc_reg <= acc_reg + (a * b);
end

assign out = acc_reg;
```

---

### Issue 3 — `output logic` driven by continuous `assign` (mac_llm_B.v)

**(a) Offending lines:**
```verilog
output logic signed [31:0] out
...
assign out = acc_reg;
```

**(b) Why it is wrong:**  
In SystemVerilog, `logic` is a **variable** type (4-state), whereas continuous assignment (`assign`) is intended for **net** types (`wire`). Driving a `logic` port with `assign` is permitted by the IEEE 1800 standard at the module boundary, but it mixes variable and net semantics in a way that is non-idiomatic and flagged as ambiguous by strict lint tools. If another `always` block were ever added to also drive `out`, the tool would silently accept multiple drivers on a `logic` variable rather than raising the multiple-driver error that a `wire` would correctly produce. The port should be declared as `output wire` to match the continuous-assignment driver.

**(c) Corrected version:**
```verilog
output wire signed [31:0] out   // net type, consistent with assign
...
assign out = acc_reg;           // unchanged — now type-consistent
```

## Simulation Log of `mac_correct.v`

Compiled with `verilator --lint-only mac_correct.v mac_tb.v` — no warnings or errors.

Simulated with `verilator --binary --timing`:

```
Cycle 1 | rst=1 a=0  b=0 | out=0
Cycle 2 | rst=0 a=3  b=4 | out=12
Cycle 3 | rst=0 a=3  b=4 | out=24
Cycle 4 | rst=0 a=3  b=4 | out=36
Cycle 5 | rst=1 a=3  b=4 | out=0
Cycle 6 | rst=0 a=-5 b=2 | out=-10
Cycle 7 | rst=0 a=-5 b=2 | out=-20
```

All cycles produce the expected values. Simulation completed at 66ns with no errors.

