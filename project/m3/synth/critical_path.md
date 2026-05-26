# Critical Path Analysis — Option B Kalman Accelerator (`top`)

## Identified Critical Path (from Vivado timing report)

The critical path is the Newton-Raphson reciprocal update loop inside `kalman_update`:

- **Start point:** `u_core/nr_x_reg[61]/C`
  (rising-edge FDCE — one bit of the running NR reciprocal estimate register)
- **End point:** `u_core/nr_x_reg[54]/D`
  (setup input of the same register — the loop feeds back into itself)
- **Slack:** -50.419 ns (VIOLATED at 100 MHz)
- **Data path delay:** 60.379 ns total (logic 31.743 ns, routing 28.636 ns)
- **Logic levels:** 92 stages — CARRY4=43, DSP48E1=6, LUT1=3, LUT2=5, LUT3=5, LUT4=6, LUT5=5, LUT6=19

The maximum achievable clock period for this path is approximately 60.4 ns,
corresponding to a **maximum operating frequency of ~16.6 MHz** on Artix-7 -1.

## Why This Is the Critical Path

The Newton-Raphson step computes `nr_x_new = nr_x * (2.0 - S * nr_x)` entirely
in combinational logic within a single clock cycle. This chains two 53x53-bit
F64 multiplications (`u_nr_mul1`, `u_nr_mul2`) and one F64 subtraction (`u_nr_sub`)
back-to-back with no pipeline registers between them. Vivado infers the mantissa
multiplies as 6 cascaded DSP48E1 tiles, whose unregistered outputs ripple through
43 CARRY4 cells in the exponent normalisation and adder alignment paths before
reaching the `nr_x` register input.

The combinational depth of 92 logic levels at ~0.65 ns/LUT-level yields the
measured 60.4 ns data-path delay — six times longer than the 10 ns clock budget.
Hold slack is met (WHS = 0.256 ns positive), confirming no hold violations.

## What Would Shorten It

1. **Pipeline the NR multiplier chain (recommended for M4):** Insert one register
   stage after `u_nr_mul1` output and another after `u_nr_mul2` output. Each NR
   iteration then takes 3 cycles instead of 1, adding ~6 cycles per Kalman update,
   but the critical path drops from 92 to roughly 30 logic levels, bringing it well
   within the 10 ns budget.

2. **Enable DSP48E1 output registers:** Pass `-no_lc` to `synth_design` and set
   `set_property USE_DSP yes [get_cells u_core/u_nr_mul1/*]`. This absorbs one
   pipeline level into the DSP tile output register at no extra LUT cost, reducing
   logic depth by ~6 levels without changing the RTL.

3. **Reduce clock to 65 MHz (15.4 ns period):** With a 15 ns period constraint,
   the design still violates timing (-45 ns slack). The required period to achieve
   closure without any RTL changes is at least 65 ns (~15 MHz). A 15 MHz clock
   is unattractive for throughput; option 1 is strongly preferred.
