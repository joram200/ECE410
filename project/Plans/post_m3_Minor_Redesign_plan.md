# post_m3_Minor_Redesign — Implementation Plan

## Overview

Create `project/post_m3_Minor_Redesign/` based on `project/m3/`, with two changes:

1. **Redesigned register map** — A_REG carries the full state lifecycle (z + x_in + x_out);
   B_REG carries P_in (all 9 elements); C_REG carries P_out (all 9 elements, fixing the
   m3 limitation of only 6 visible); R_REG at 0xE8 makes R programmable via AXI.
2. **NR pipeline (Option 1)** — Insert one register stage after `u_nr_mul1` output to break
   the 92-level critical path (WNS = −50.419 ns) into two ~30-level stages, targeting
   WNS ≥ 0 at 100 MHz.

Run through `run_m3.sh`, stopping on errors with `touch .STOP`, fixing, and continuing.

---

## Source Files

| Source (copy from) | Destination |
|--------------------|-------------|
| `m3/rtl/top.sv` | `post_m3_Minor_Redesign/rtl/top.sv` ← **modified** |
| `m3/tb/tb_top.sv` | `post_m3_Minor_Redesign/tb/tb_top.sv` ← **modified** |
| `m3/run_m3.sh` | `post_m3_Minor_Redesign/run_m3.sh` (verbatim copy) |
| `m3/synth/run_ooc.tcl` | `post_m3_Minor_Redesign/synth/run_ooc.tcl` (verbatim copy) |
| `m3/synth/constraints.xdc` | `post_m3_Minor_Redesign/synth/constraints.xdc` (verbatim copy) |
| `m3/synth/gtkwave_export.tcl` | `post_m3_Minor_Redesign/synth/gtkwave_export.tcl` (verbatim copy) |

---

## New Register Map

Address decode: `reg_index = addr[7:3]` (5-bit, 8-byte stride). All F64 values are
IEEE-754 double-precision (64-bit).

| Address | Index | Name | CPU Access | Description |
|---------|-------|------|-----------|-------------|
| 0x00 | 0 | CTRL | R/W | [0]=start one-shot, [1]=soft_rst |
| 0x08 | 1 | STAT | RO | [0]=done (1-cycle pulse), [1]=busy |
| 0x10 | 2 | A_REG[0] | WO | z — measurement scalar |
| 0x18 | 3 | A_REG[1] | WO | x_in[0] — prior state element 0 |
| 0x20 | 4 | A_REG[2] | WO | x_in[1] — prior state element 1 |
| 0x28 | 5 | A_REG[3] | WO | x_in[2] — prior state element 2 |
| 0x30 | 6 | A_REG[4] | RO | x_out[0] — corrected state element 0 |
| 0x38 | 7 | A_REG[5] | RO | x_out[1] — corrected state element 1 |
| 0x40 | 8 | A_REG[6] | RO | x_out[2] — corrected state element 2 |
| 0x48 | 9 | A_REG[7] | — | unused |
| 0x50 | 10 | A_REG[8] | — | unused |
| 0x58 | 11 | B_REG[0] | WO | P_in[0,0] |
| 0x60 | 12 | B_REG[1] | WO | P_in[0,1] |
| 0x68 | 13 | B_REG[2] | WO | P_in[0,2] |
| 0x70 | 14 | B_REG[3] | WO | P_in[1,0] |
| 0x78 | 15 | B_REG[4] | WO | P_in[1,1] |
| 0x80 | 16 | B_REG[5] | WO | P_in[1,2] |
| 0x88 | 17 | B_REG[6] | WO | P_in[2,0] |
| 0x90 | 18 | B_REG[7] | WO | P_in[2,1] |
| 0x98 | 19 | B_REG[8] | WO | P_in[2,2] |
| 0xA0 | 20 | C_REG[0] | RO | P_out[0,0] |
| 0xA8 | 21 | C_REG[1] | RO | P_out[0,1] |
| 0xB0 | 22 | C_REG[2] | RO | P_out[0,2] |
| 0xB8 | 23 | C_REG[3] | RO | P_out[1,0] |
| 0xC0 | 24 | C_REG[4] | RO | P_out[1,1] |
| 0xC8 | 25 | C_REG[5] | RO | P_out[1,2] |
| 0xD0 | 26 | C_REG[6] | RO | P_out[2,0] |
| 0xD8 | 27 | C_REG[7] | RO | P_out[2,1] |
| 0xE0 | 28 | C_REG[8] | RO | P_out[2,2] |
| 0xE8 | 29 | R_REG | R/W | Measurement noise covariance R (default 5.0) |

---

## RTL Changes (`rtl/top.sv`)

All line numbers reference `project/m3/rtl/top.sv`.

### Change 1 — `kalman_update` module: replace hardcoded R with port

**Line 414 — delete:**
```sv
localparam logic [63:0] R_CONST = 64'h4014_0000_0000_0000;
```

**After the `P_in` port line (line 406) — add:**
```sv
    input  logic [63:0] r_val,           // programmable R (from R_REG at 0xE8)
```

**Line 631 — change `R_CONST` → `r_val`:**
```sv
// BEFORE:
f64_add u_scomb  (.a(P_reg[0]),.b(R_CONST),  .result(S_comb));
// AFTER:
f64_add u_scomb  (.a(P_reg[0]),.b(r_val),    .result(S_comb));
```

### Change 2 — `kalman_update` module: NR pipeline (Option 1)

**After `logic [63:0] nr_x;` (line 445) — add two pipeline registers:**
```sv
    logic [63:0] sx_pipe;    // registered output of u_nr_mul1 (S * nr_x)
    logic [63:0] nr_x_pipe;  // nr_x piped one cycle alongside sx_pipe
```

**Lines 464–467 — update combinational NR helpers:**
```sv
// BEFORE:
    logic [63:0] sx, two_minus_sx, nr_x_new;
    f64_mul u_nr_mul1 (.a(S_reg), .b(nr_x),        .result(sx));
    f64_add u_nr_sub  (.a(F64_TWO), .b({~sx[63], sx[62:0]}), .result(two_minus_sx));
    f64_mul u_nr_mul2 (.a(nr_x), .b(two_minus_sx), .result(nr_x_new));

// AFTER:
    logic [63:0] sx, two_minus_sx, nr_x_new;
    // Stage A: mul1 runs on unmodified nr_x (states NR0_A / NR1_A / NR2_A)
    f64_mul u_nr_mul1 (.a(S_reg),    .b(nr_x),         .result(sx));
    // Stage B: sub and mul2 run on registered pipeline values (states NR0_B / NR1_B / NR2_B)
    f64_add u_nr_sub  (.a(F64_TWO),  .b({~sx_pipe[63], sx_pipe[62:0]}), .result(two_minus_sx));
    f64_mul u_nr_mul2 (.a(nr_x_pipe),.b(two_minus_sx), .result(nr_x_new));
```

**New critical paths after this change:**
- Stage A: `nr_x_reg → u_nr_mul1 → sx_pipe_reg` (~30 logic levels)
- Stage B: `sx_pipe_reg → u_nr_sub → u_nr_mul2 → nr_x_reg` (~30 logic levels)

**Lines 421–433 — replace FSM state encoding (11 states → 14 states, still 4-bit):**
```sv
// BEFORE:
    typedef enum logic [3:0] {
        IDLE   = 4'd0,
        INNOV  = 4'd1,
        S_COMP = 4'd2,
        NR0    = 4'd3,
        NR1    = 4'd4,
        NR2    = 4'd5,
        K_COMP = 4'd6,
        X_CORR = 4'd7,
        P_UPD  = 4'd8,
        WAIT_P = 4'd9,
        DONE_S = 4'd10
    } state_t;

// AFTER:
    typedef enum logic [3:0] {
        IDLE   = 4'd0,
        INNOV  = 4'd1,
        S_COMP = 4'd2,
        NR0_A  = 4'd3,   // Stage A: latch sx_pipe, nr_x_pipe
        NR0_B  = 4'd4,   // Stage B: latch nr_x from nr_x_new
        NR1_A  = 4'd5,
        NR1_B  = 4'd6,
        NR2_A  = 4'd7,
        NR2_B  = 4'd8,   // Stage B of last NR iter: latch S_inv only
        K_COMP = 4'd9,
        X_CORR = 4'd10,
        P_UPD  = 4'd11,
        WAIT_P = 4'd12,
        DONE_S = 4'd13
    } state_t;
```

**Lines 490–506 — replace FSM next-state logic for NR states:**
```sv
// BEFORE (NR section):
        NR0:                  state_nxt = NR1;
        NR1:                  state_nxt = NR2;
        NR2:                  state_nxt = K_COMP;
        K_COMP:               state_nxt = X_CORR;
        X_CORR:               state_nxt = P_UPD;
        P_UPD:                state_nxt = WAIT_P;
        WAIT_P: if (gs_done)  state_nxt = DONE_S;

// AFTER:
        NR0_A:                state_nxt = NR0_B;
        NR0_B:                state_nxt = NR1_A;
        NR1_A:                state_nxt = NR1_B;
        NR1_B:                state_nxt = NR2_A;
        NR2_A:                state_nxt = NR2_B;
        NR2_B:                state_nxt = K_COMP;
        K_COMP:               state_nxt = X_CORR;
        X_CORR:               state_nxt = P_UPD;
        P_UPD:                state_nxt = WAIT_P;
        WAIT_P: if (gs_done)  state_nxt = DONE_S;
```

**Lines 521–540 — in the `!rst_n` branch of the main always_ff, add resets for new registers:**
```sv
        sx_pipe   <= 64'h0;
        nr_x_pipe <= 64'h0;
```

**Lines 562–575 — replace NR0/NR1/NR2 datapath cases with the 6 new cases:**
```sv
// BEFORE:
                NR0: begin
                    nr_x <= nr_x_new;
                    S_inv <= nr_x_new;
                end
                NR1: begin
                    nr_x <= nr_x_new;
                    S_inv <= nr_x_new;
                end
                NR2: begin
                    S_inv <= nr_x_new;
                end

// AFTER:
                NR0_A: begin
                    sx_pipe   <= sx;      // latch mul1 result
                    nr_x_pipe <= nr_x;    // keep nr_x available for mul2 in stage B
                end
                NR0_B: begin
                    nr_x  <= nr_x_new;
                    S_inv <= nr_x_new;
                end
                NR1_A: begin
                    sx_pipe   <= sx;
                    nr_x_pipe <= nr_x;
                end
                NR1_B: begin
                    nr_x  <= nr_x_new;
                    S_inv <= nr_x_new;
                end
                NR2_A: begin
                    sx_pipe   <= sx;
                    nr_x_pipe <= nr_x;
                end
                NR2_B: begin
                    S_inv <= nr_x_new;    // final converged reciprocal; nr_x no longer needed
                end
```

**Note on `busy` / `done` (lines 646–647):** No change needed.
```sv
assign done = (state == DONE_S);
assign busy = (state != IDLE) && (state != DONE_S);
```
The `compute_core_checker` SVA `busy [*3]` still passes — the FSM now stays busy for
at least 14 cycles before DONE_S.

### Change 3 — `axilite_slave` module: x_out readback port + R_REG + full P_out

#### 3a. Add new port `core_x_out [0:2]`

After the `core_B` output port (line ~693), add:
```sv
    input  logic [63:0]               core_x_out [0:2],  // x_out readback (returned at A_REG[4:6])
```

#### 3b. Add `reg_R` internal register

In the `Internal registers` block (after `reg_B [0:8]`):
```sv
    logic [63:0] reg_R;
```

#### 3c. Reset `reg_R` in the write-execute `always_ff` block `!rst_n` branch:
```sv
            reg_R <= 64'h4014_0000_0000_0000;   // default R = 5.0
```

#### 3d. Write decode: add R_REG case after `5'd19`

```sv
                    5'd29: reg_R <= w_data_lat;   // 0xE8 — R_REG
```

Writes to indices 6–8 (A_REG[4:6] = x_out) fall to `default: ;` — silently ignored.

#### 3e. Read decode: remap indices 6–8 and 20–28; add 29

The read `case (rd_idx)` block currently has cases 5'd2–5'd28. Replace:

```sv
// BEFORE (selected cases):
                    5'd6:  s_rdata <= reg_A[4];   // was unused A slot
                    5'd7:  s_rdata <= reg_A[5];
                    5'd8:  s_rdata <= reg_A[6];
                    // (5'd9, 5'd10 remain reg_A[7:8])
                    5'd20: s_rdata <= core_C[0];  // was x_out[0]
                    5'd21: s_rdata <= core_C[1];  // was x_out[1]
                    5'd22: s_rdata <= core_C[2];  // was x_out[2]
                    5'd23: s_rdata <= core_C[3];  // was P_out[0]
                    5'd24: s_rdata <= core_C[4];
                    5'd25: s_rdata <= core_C[5];
                    5'd26: s_rdata <= core_C[6];  // was P_out[3]
                    5'd27: s_rdata <= core_C[7];
                    5'd28: s_rdata <= core_C[8];

// AFTER:
                    5'd6:  s_rdata <= core_x_out[0];  // 0x30 — x_out[0]
                    5'd7:  s_rdata <= core_x_out[1];  // 0x38 — x_out[1]
                    5'd8:  s_rdata <= core_x_out[2];  // 0x40 — x_out[2]
                    // (5'd9, 5'd10 remain reg_A[7:8] → return '0 via default)
                    5'd20: s_rdata <= core_C[0];   // 0xA0 — P_out[0,0]
                    5'd21: s_rdata <= core_C[1];   // 0xA8 — P_out[0,1]
                    5'd22: s_rdata <= core_C[2];   // 0xB0 — P_out[0,2]
                    5'd23: s_rdata <= core_C[3];   // 0xB8 — P_out[1,0]
                    5'd24: s_rdata <= core_C[4];   // 0xC0 — P_out[1,1]
                    5'd25: s_rdata <= core_C[5];   // 0xC8 — P_out[1,2]
                    5'd26: s_rdata <= core_C[6];   // 0xD0 — P_out[2,0]
                    5'd27: s_rdata <= core_C[7];   // 0xD8 — P_out[2,1]
                    5'd28: s_rdata <= core_C[8];   // 0xE0 — P_out[2,2]
                    5'd29: s_rdata <= reg_R;        // 0xE8 — R_REG
```

#### 3f. Add `core_R` output and `core_x_out` wire

Near the other `assign` statements at the bottom of `axilite_slave`:
```sv
    output logic [63:0] core_R,         // R_REG driven to kalman_update
```
(add to port list)

```sv
    assign core_R = reg_R;
```

### Change 4 — `top` module: rewire all ports

#### 4a. Remove old x_out→slave_C mapping; update slave_C to full P_out

```sv
// BEFORE (lines 989–997):
    assign slave_C[0] = x_out[0];
    assign slave_C[1] = x_out[1];
    assign slave_C[2] = x_out[2];
    assign slave_C[3] = P_out[0];
    assign slave_C[4] = P_out[1];
    assign slave_C[5] = P_out[2];
    assign slave_C[6] = P_out[3];
    assign slave_C[7] = P_out[4];
    assign slave_C[8] = P_out[5];

// AFTER:
    // C_REG[0:8] = P_out[0:8] (all 9 covariance output elements)
    generate
        for (genvar gi = 0; gi < 9; gi++) begin : gen_slave_c
            assign slave_C[gi] = P_out[gi];
        end
    endgenerate
```

#### 4b. Add `r_wire` and `x_out` as named internal signals

In the internal wires section (after `slave_C`):
```sv
    logic [63:0] r_wire;        // R register value → kalman_update.r_val
    // x_out is already declared as `logic [63:0] x_out [0:2]`
    // (no change needed there)
```

#### 4c. Update `axilite_slave` instantiation — add new ports

```sv
        .core_x_out (x_out),      // x_out readback at A_REG[4:6] (0x30–0x40)
        .core_R     (r_wire),     // R_REG at 0xE8
```

#### 4d. Update `kalman_update` instantiation — add `r_val`

```sv
        .r_val (r_wire),
```

---

## Testbench Changes (`tb/tb_top.sv`)

### TB Change 1 — BFM: add `read_matrix_A_xout` task

In `veerwolf_bfm`, after `read_matrix_C`, add:
```sv
    // Read x_out from A_REG[4:6] (0x30, 0x38, 0x40)
    task automatic read_xout(output logic [63:0] xo [0:2]);
        for (int i = 0; i < 3; i++) begin
            axi_read(32'h30 + (i * 8), xo[i]);
        end
    endtask
```

### TB Change 2 — BFM: update `write_matrix_A`

The existing `write_matrix_A` writes 9 elements starting at 0x10. Slots [4:6]
(0x30–0x40) are now x_out (read-only); writes are ignored by the slave. No functional
change needed — can leave the task writing zeros to [4:8] as before.

### TB Change 3 — `axi_monitor`: update coverage, add R_REG bin

In `axi_write_targets` covergroup, add:
```sv
            bins r_reg   = {5'd29};   // 0xE8
```

### TB Change 4 — `result_checker`: extend to 12 elements (3 x_out + 9 P_out)

Change the module signature and internal loop from 9 to 12:
```sv
module result_checker #(
    parameter real ULP_TOLERANCE = 1.0
)(
    input logic        clk,
    input logic        check_en,
    input logic [63:0] dut_xo  [0:2],   // x_out from A_REG[4:6]
    input logic [63:0] ref_xo  [0:2],
    input logic [63:0] dut_P   [0:8],   // P_out from C_REG[0:8]
    input logic [63:0] ref_P   [0:8],
    input logic        core_start,
    input logic        core_busy,
    input logic        core_done,
    input logic        core_rst_n
);
```

Internal check loop (replace the single 9-element loop with two loops):
```sv
    always @(posedge clk) begin
        if (check_en) begin
            // Check x_out (3 elements)
            for (int i = 0; i < 3; i++) begin
                automatic logic [63:0] d = ulp_dist(dut_xo[i], ref_xo[i]);
                if (d > $realtobits(ULP_TOLERANCE)) begin
                    $error("CHECKER: x_out[%0d] ULP=%0d dut=%h ref=%h", i, d, dut_xo[i], ref_xo[i]);
                    fail_count++;
                end else pass_count++;
            end
            // Check P_out (9 elements)
            for (int i = 0; i < 9; i++) begin
                automatic logic [63:0] d = ulp_dist(dut_P[i], ref_P[i]);
                if (d > $realtobits(ULP_TOLERANCE)) begin
                    $error("CHECKER: P_out[%0d] ULP=%0d dut=%h ref=%h", i, d, dut_P[i], ref_P[i]);
                    fail_count++;
                end else pass_count++;
            end
        end
    end
```

Total comparisons: 15 iterations × 12 elements = 180 (was 135).

### TB Change 5 — `tb_top`: update `kalman_ref` signature

```sv
    function automatic void kalman_ref(
        input  logic [63:0] x_in    [0:2],
        input  logic [63:0] P_in    [0:8],
        output logic [63:0] x_out   [0:2],
        output logic [63:0] P_out   [0:8]   // full 9-element P output
    );
        // ... (computation unchanged)
        // Pack into outputs — no longer need the mixed C_out packing:
        for (int i = 0; i < 3; i++) x_out[i]  = $realtobits(x_new[i]);
        for (int i = 0; i < 9; i++) P_out[i]  = $realtobits(P_new[i]);
    endfunction
```

### TB Change 6 — `tb_top`: update main test sequence

```sv
    logic [63:0] dut_xo  [0:2];
    logic [63:0] ref_xo  [0:2];
    logic [63:0] dut_P   [0:8];
    logic [63:0] ref_P   [0:8];
    // (remove dut_C [0:8], ref_C [0:8])

    initial begin
        check_en = 1'b0;
        for (int i = 0; i < 3; i++) x_iter[i] = 64'h0;

        wait (rst_n === 1'b1);
        repeat (3) @(posedge clk);

        // ── Write R = 5.0 to R_REG (0xE8) once before the loop ──
        u_bfm.axi_write(32'hE8, 64'h4014_0000_0000_0000);

        for (int iter = 0; iter < 15; iter++) begin
            $display("TB_TOP: Starting iteration %0d", iter);

            // Write z, x_in into A_REG[0:3]; P_in into B_REG[0:8]
            A_in[0] = $realtobits(Z_MEAS);
            for (int i = 0; i < 3; i++) A_in[1+i] = x_iter[i];
            for (int i = 4; i < 9; i++) A_in[i] = 64'h0;
            u_bfm.write_matrix_A(A_in);
            u_bfm.write_matrix_B(B_pairs[iter]);

            u_bfm.fire_and_wait();

            // Read x_out from A_REG[4:6] (0x30–0x40)
            u_bfm.read_xout(dut_xo);
            // Read P_out from C_REG[0:8] (0xA0–0xE0)
            u_bfm.read_matrix_C(dut_P);

            // Compute reference
            kalman_ref(x_iter, B_pairs[iter], ref_xo, ref_P);

            // Update x for next iteration
            for (int i = 0; i < 3; i++) x_iter[i] = ref_xo[i];

            // Trigger checker
            @(posedge clk);
            check_en = 1'b1;
            @(posedge clk);
            check_en = 1'b0;

            $display("TB_TOP: Iteration %0d complete", iter);
        end

        repeat (10) @(posedge clk);
        $display("TB_TOP: All 15 iterations complete.");
        $finish;
    end
```

### TB Change 7 — `result_checker` instantiation in `tb_top`

```sv
    result_checker #(.ULP_TOLERANCE(4.0)) u_chk (
        .clk        (clk),
        .check_en   (check_en),
        .dut_xo     (dut_xo),
        .ref_xo     (ref_xo),
        .dut_P      (dut_P),
        .ref_P      (ref_P),
        .core_start (core_start),
        .core_busy  (core_busy),
        .core_done  (core_done),
        .core_rst_n (core_rst_n)
    );
```

---

## Execution: `run_m3.sh` Flow

Run from `project/post_m3_Minor_Redesign/`:
```bash
cd project/post_m3_Minor_Redesign && bash run_m3.sh
```

Steps (mirrored from m3):
1. `mkdir -p sim synth reports`
2. Check `rtl/top.sv`
3. Check `tb/tb_top.sv`
4. Check `synth/constraints.xdc`
5. `xvlog --sv rtl/top.sv tb/tb_top.sv --log reports/compile.log`
6. `xelab tb_top -s m3_snap -debug typical --log reports/elab.log`
7. `xsim m3_snap --runall --log sim/cosim_run.log`
8. GTKWave PNG export (non-fatal)
9. `vivado -mode batch -source synth/run_ooc.tcl -log synth/openlane_run.log`

**On any step failure:** `touch .STOP` halts at next checkpoint. Fix the error,
remove `.STOP`, re-run `bash run_m3.sh`.

**Expected simulation result:** `SIMULATION RESULT: PASS` — 180/180 element comparisons
(15 iterations × 12 elements), all ≤ 4.0 ULP. The +3 cycle latency from NR pipelining
is well within the 2 µs timeout watchdog.

**Expected synthesis result:** WNS ≥ 0 ns — the NR pipeline splits the 92-level
combinational path into two ~30-level stages, each fitting within the 10 ns clock budget.

---

## Verification Checklist

- [ ] `grep "SIMULATION RESULT:" sim/cosim_run.log` → `PASS`
- [ ] `grep "CHECKER summary:" sim/cosim_run.log` → `180 elements passed, 0 failed`
- [ ] `grep "WNS" synth/timing_report.txt` → value ≥ 0.000 ns
- [ ] R_REG read at 0xE8 returns 5.0 (`64'h4014_0000_0000_0000`) before any write
- [ ] P_out[6:8] (0xD0–0xE0) now readable — fixes the m3 limitation of only 6/9 P elements
