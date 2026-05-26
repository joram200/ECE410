# Project Redesign Plan — M3
**Date:** 2026-05-20 | **Target:** Milestone 3 (due Sun, May 24)

Context: Platform changed from i7-11800H / PCIe TLP to SweRV EL2 / AXI4-Lite
(see `scope_assessment.md`). Dominant kernel is 3×3 F64 GEMM at 1.38e-4
GFLOP/s on bare-metal RISC-V. Two candidate compute cores will be implemented,
verified in simulation, then synthesised; the better-performing option is
carried into the Veerwolf SoC integration run.

All new HDL lives under `project/new_hdl/`. Directory layout:

```
project/new_hdl/
├── rtl/
│   ├── f64_mul.sv                # IEEE-754 F64 combinational multiplier
│   ├── f64_add.sv                # IEEE-754 F64 combinational adder
│   ├── gemm_systolic.sv          # Option A — 3×3 systolic GEMM
│   ├── kalman_update.sv          # Option B — Kalman update kernel (wraps A)
│   ├── axilite_slave.sv          # AXI4-Lite slave register-file interface
│   ├── accel_top_a.sv            # Option A synthesis top (slave + gemm_systolic)
│   ├── accel_top_b.sv            # Option B synthesis top (slave + kalman_update)
│   └── clk_gen.sv                # Clock-generating wrapper (sim-only)
├── tb/
│   ├── veerwolf_bfm.sv           # Behavioral model of VeerWolf / SweRV EL2
│   ├── axi_monitor.sv            # AXI4-Lite protocol monitor + SVAs
│   ├── clk_gen_tb.sv             # Clock-gen instantiation block
│   ├── checker.sv                # F64 output checker (≤ 1 ULP tolerance)
│   ├── program_block.sv          # Test program: replicates RVfpgaEL2 algorithm
│   ├── tb_option_a.sv            # Top-level TB for Option A
│   └── tb_option_b.sv            # Top-level TB for Option B
├── synth/
│   ├── run_ooc_a.tcl             # OOC synthesis script — Option A
│   ├── run_ooc_b.tcl             # OOC synthesis script — Option B
│   └── run_soc_integration.tcl   # Full SoC integration run (winning option)
├── vivado_option_a/              # Vivado project: Option A sim + OOC synth
│   └── vivado_option_a.xpr
├── vivado_option_b/              # Vivado project: Option B sim + OOC synth
│   └── vivado_option_b.xpr
└── reports/
    ├── ooc_a_utilization.rpt     # Option A: LUT/FF/CARRY4 counts
    ├── ooc_a_timing.rpt          # Option A: WNS, WHS, critical path
    ├── ooc_a_power.rpt           # Option A: dynamic + static power
    ├── ooc_b_utilization.rpt     # Option B equivalents
    ├── ooc_b_timing.rpt
    ├── ooc_b_power.rpt
    ├── soc_utilization.rpt       # Post-route SoC utilization
    ├── soc_timing.rpt            # Post-route SoC timing summary
    └── soc_drc.rpt               # Interface-level DRC
```

`reports/` is write-only at runtime — Tcl scripts redirect all `report_*`
commands here. Nothing in `reports/` is committed to git (add to `.gitignore`)
until synthesis is complete and results are reviewed.

---

## 1. Compute Core Option A — 3×3 Systolic GEMM Engine (`gemm_systolic.sv`)

### Description
Weight-stationary systolic array: 9 processing elements arranged in a 3×3
grid. Each PE holds one element of matrix B (stationary weight) and accumulates
`A_row × B_col` products.

### Interface
```systemverilog
module gemm_systolic (
    input  logic        clk,
    input  logic        rst_n,
    input  logic        start,        // pulse: latch A[], B[], begin compute
    input  logic [63:0] A [0:8],      // row-major, F64 IEEE-754
    input  logic [63:0] B [0:8],
    output logic [63:0] C [0:8],
    output logic        done,         // single-cycle pulse when C is valid
    output logic        busy
);
```

### Microarchitecture
- 9 MAC units in parallel, one per output element C[i][j]
- Accumulate over k=0..2 (inner dimension) in 3 pipeline stages
- Each stage: one F64 multiply-accumulate using an IEEE-754 FMA operator
  (or sequential multiply + add if a single-cycle FMA is too large)
- Total latency: 3 cycles compute + pipeline drain; `done` pulses on cycle 4
- Resets all accumulators to zero on `start`

### Precision
All arithmetic is IEEE 754 double (F64). No fixed-point conversion.

---

## 2. Compute Core Option B — Kalman Filter Update Kernel (`kalman_update.sv`)

### Description
Hardwires the full Kalman update step from the profiled firmware:
  1. Innovation: `y_tilde = z - H*x`
  2. Innovation covariance: `S = H*P*H' + R`
  3. Kalman gain: `K = P*H' * inv(S)` (3×1 vector; scalar S simplifies to division)
  4. State correction: `x = x + K*y_tilde`
  5. Covariance update: `P = (I - K*H) * P`

### Interface
```systemverilog
module kalman_update (
    input  logic        clk,
    input  logic        rst_n,
    input  logic        start,
    input  logic [63:0] z,            // scalar measurement
    input  logic [63:0] x_in  [0:2], // prior state (3×1)
    input  logic [63:0] P_in  [0:8], // prior covariance (3×3)
    output logic [63:0] x_out [0:2], // corrected state
    output logic [63:0] P_out [0:8], // corrected covariance
    output logic        done,
    output logic        busy
);
```

### Microarchitecture
- Instantiates `gemm_systolic` as the inner 3×3 GEMM primitive
- Scalar division for `inv(S)` via an iterative Newton-Raphson reciprocal
  (≤ 5 iterations, fully unrolled if timing allows)
- FSM sequences: IDLE → INNOV → S_COMP → K_COMP → X_CORR → P_UPD → DONE
- Latency: ~7–10 GEMM cycles depending on pipeline reuse

---

## 3. AXI4-Lite Slave Interface (`axilite_slave.sv`)

### Description
Synthesisable AXI4-Lite slave that wraps either compute core and exposes the
register map below. Drop-in slave on the Veerwolf `axi_intercon` (64-bit data
bus, 32-bit address). DATA_WIDTH=64 matches the VeerWolf SoC AXI interconnect
natively — each F64 register element maps to exactly one AXI beat.

### Register Map (64-bit data width, 8-byte stride)
| Offset      | Name        | Dir | Width | Purpose                         |
|-------------|-------------|-----|-------|---------------------------------|
| 0x00        | CTRL        | R/W | 64    | [0]=start, [1]=soft_rst         |
| 0x08        | STAT        | RO  | 64    | [0]=done, [1]=busy              |
| 0x10–0x50   | A_REG[0..8] | WO  | 64    | Matrix A (9 × F64, stride 8)    |
| 0x58–0x98   | B_REG[0..8] | WO  | 64    | Matrix B (9 × F64, stride 8)    |
| 0xA0–0xE0   | C_REG[0..8] | RO  | 64    | Output matrix C (9 × F64)       |

Each F64 element maps to exactly one 64-bit AXI beat. No beat-splitting required.
Address decode uses `addr[7:3]` as a register index (8-byte stride).

### Interface (AXI4-Lite subset)
```systemverilog
module axilite_slave #(
    parameter int ADDR_WIDTH = 32,
    parameter int DATA_WIDTH = 64    // 64-bit: one beat per F64 register element
)(
    input  logic                    clk,
    input  logic                    rst_n,
    // Write address channel
    input  logic [ADDR_WIDTH-1:0]   s_awaddr,
    input  logic                    s_awvalid,
    output logic                    s_awready,
    // Write data channel
    input  logic [DATA_WIDTH-1:0]   s_wdata,
    input  logic [DATA_WIDTH/8-1:0] s_wstrb,   // 8-bit strobe for 64-bit bus
    input  logic                    s_wvalid,
    output logic                    s_wready,
    // Write response channel
    output logic [1:0]              s_bresp,
    output logic                    s_bvalid,
    input  logic                    s_bready,
    // Read address channel
    input  logic [ADDR_WIDTH-1:0]   s_araddr,
    input  logic                    s_arvalid,
    output logic                    s_arready,
    // Read data channel
    output logic [DATA_WIDTH-1:0]   s_rdata,
    output logic [1:0]              s_rresp,
    output logic                    s_rvalid,
    input  logic                    s_rready,
    // Core control (to compute core)
    output logic                    core_start,
    output logic                    core_rst_n,
    output logic [63:0]             core_A [0:8],
    output logic [63:0]             core_B [0:8],
    // Core status (from compute core)
    input  logic [63:0]             core_C [0:8],
    input  logic                    core_done,
    input  logic                    core_busy
);
```

### Write Sequencing
1. CPU writes A_REG[0..8] (9 × 64-bit beats) then B_REG[0..8] (9 × 64-bit beats)
2. CPU writes CTRL[0]=1 (start pulse); slave asserts `core_start` for one cycle
3. CPU polls STAT until [0]=done; reads C_REG[0..8] (9 × 64-bit beats)

---

## 3.5 RTL Top Modules (`accel_top_a.sv`, `accel_top_b.sv`)

Each compute core option gets a dedicated RTL top module that instantiates
`axilite_slave` and the corresponding compute core, and wires their internal
control/data ports together. These are the synthesis top modules for all OOC
and SoC integration runs — `axilite_slave` and the compute cores are never
synthesised in isolation.

### Option A Top (`accel_top_a.sv`)

Exposes only the AXI4-Lite bus and `clk`/`rst_n` to the outside world.
All `core_*` signals are internal wires. DATA_WIDTH=64 matches the VeerWolf
SoC AXI interconnect; accel_top connects directly to crossbar output wires.

```systemverilog
module accel_top_a #(
    parameter int ADDR_WIDTH = 32,
    parameter int DATA_WIDTH = 64    // must match SoC AXI interconnect (64-bit)
)(
    input  logic                      clk,
    input  logic                      rst_n,
    // AXI4-Lite slave port (identical to axilite_slave)
    input  logic [ADDR_WIDTH-1:0]     s_awaddr,
    input  logic                      s_awvalid,
    output logic                      s_awready,
    input  logic [DATA_WIDTH-1:0]     s_wdata,
    input  logic [(DATA_WIDTH/8)-1:0] s_wstrb,
    input  logic                      s_wvalid,
    output logic                      s_wready,
    output logic [1:0]                s_bresp,
    output logic                      s_bvalid,
    input  logic                      s_bready,
    input  logic [ADDR_WIDTH-1:0]     s_araddr,
    input  logic                      s_arvalid,
    output logic                      s_arready,
    output logic [DATA_WIDTH-1:0]     s_rdata,
    output logic [1:0]                s_rresp,
    output logic                      s_rvalid,
    input  logic                      s_rready
);
    // Internal core wires
    logic        core_start, core_rst_n, core_done, core_busy;
    logic [63:0] core_A [0:8], core_B [0:8], core_C [0:8];

    axilite_slave #(.ADDR_WIDTH(ADDR_WIDTH), .DATA_WIDTH(DATA_WIDTH)) u_slave (
        .clk(clk), .rst_n(rst_n),
        .s_awaddr(s_awaddr), .s_awvalid(s_awvalid), .s_awready(s_awready),
        .s_wdata(s_wdata),   .s_wstrb(s_wstrb),     .s_wvalid(s_wvalid),   .s_wready(s_wready),
        .s_bresp(s_bresp),   .s_bvalid(s_bvalid),   .s_bready(s_bready),
        .s_araddr(s_araddr), .s_arvalid(s_arvalid), .s_arready(s_arready),
        .s_rdata(s_rdata),   .s_rresp(s_rresp),     .s_rvalid(s_rvalid),   .s_rready(s_rready),
        .core_start(core_start), .core_rst_n(core_rst_n),
        .core_A(core_A),         .core_B(core_B),
        .core_C(core_C),         .core_done(core_done), .core_busy(core_busy)
    );

    gemm_systolic u_core (
        .clk(clk),       .rst_n(core_rst_n),
        .start(core_start),
        .A(core_A),      .B(core_B),      .C(core_C),
        .done(core_done), .busy(core_busy)
    );
endmodule
```

### Option B Top (`accel_top_b.sv`)

Same AXI4-Lite external port list. `axilite_slave` is parameterised or
swapped for an Option-B register map variant that exposes `z`, `x_in`,
`P_in`, `x_out`, `P_out` instead of A/B/C matrices. DATA_WIDTH=64 throughout.

```systemverilog
module accel_top_b #(
    parameter int ADDR_WIDTH = 32,
    parameter int DATA_WIDTH = 64    // must match SoC AXI interconnect (64-bit)
)(
    // Identical AXI4-Lite port list as accel_top_a — omitted for brevity
    input  logic clk,
    input  logic rst_n,
    // ... (same AXI4-Lite ports)
);
    logic        core_start, core_rst_n, core_done, core_busy;
    logic [63:0] core_z;
    logic [63:0] core_x_in  [0:2], core_P_in  [0:8];
    logic [63:0] core_x_out [0:2], core_P_out [0:8];

    axilite_slave_b #(.ADDR_WIDTH(ADDR_WIDTH), .DATA_WIDTH(DATA_WIDTH)) u_slave (
        // AXI4-Lite connections identical to Option A slave
        .core_start(core_start), .core_rst_n(core_rst_n),
        .core_z(core_z),
        .core_x_in(core_x_in),   .core_P_in(core_P_in),
        .core_x_out(core_x_out), .core_P_out(core_P_out),
        .core_done(core_done),   .core_busy(core_busy)
    );

    kalman_update u_core (
        .clk(clk),        .rst_n(core_rst_n),
        .start(core_start),
        .z(core_z),
        .x_in(core_x_in),   .P_in(core_P_in),
        .x_out(core_x_out), .P_out(core_P_out),
        .done(core_done),    .busy(core_busy)
    );
endmodule
```

### Use in Synthesis and Testbenches

- OOC synthesis targets: `accel_top_a` (Run 1A) and `accel_top_b` (Run 1B)
- SoC integration target: winning top module connected to `axi_intercon`
- Testbenches instantiate the top module (`accel_top_a` / `accel_top_b`) directly
  and drive its AXI4-Lite ports from `veerwolf_bfm`, replacing the separate
  `axilite_slave` + compute core instantiation used in simulation

---

## 4. Full SystemVerilog Verification Environment

### 4.1 VeerWolf Core Behavioral Model (`veerwolf_bfm.sv`)

Structural analogue of `Simulators/verilatorSIM_ViDBo/`. The BFM acts as an
AXI4-Lite master and drives the DUT slave interface, replacing the actual SweRV
EL2 pipeline.

```systemverilog
module veerwolf_bfm (
    input  logic        clk,
    input  logic        rst_n,
    // AXI4-Lite master outputs (connect to DUT slave inputs) — 64-bit data
    output logic [31:0] m_awaddr,
    output logic        m_awvalid,
    input  logic        m_awready,
    output logic [63:0] m_wdata,
    output logic [7:0]  m_wstrb,   // 8-bit strobe for 64-bit bus
    output logic        m_wvalid,
    input  logic        m_wready,
    input  logic [1:0]  m_bresp,
    input  logic        m_bvalid,
    output logic        m_bready,
    output logic [31:0] m_araddr,
    output logic        m_arvalid,
    input  logic        m_arready,
    input  logic [63:0] m_rdata,   // 64-bit read data
    input  logic [1:0]  m_rresp,
    input  logic        m_rvalid,
    output logic        m_rready
);
```

Tasks exposed by the BFM:
- `task axi_write(input [31:0] addr, input [63:0] data)` — one 64-bit beat
- `task axi_read(input [31:0] addr, output [63:0] data)` — one 64-bit beat
- `task write_matrix_A(input [63:0] A[0:8])` — 9 × 64-bit beats (base 0x10)
- `task write_matrix_B(input [63:0] B[0:8])` — 9 × 64-bit beats (base 0x58)
- `task read_matrix_C(output [63:0] C[0:8])` — 9 × 64-bit beats (base 0xA0)
- `task fire_and_wait()` — writes CTRL=64'h1, polls STAT[0] until done

### 4.2 AXI Protocol Monitor + SVAs (`axi_monitor.sv`)

Passive module: binds to the AXI4-Lite bus between BFM and DUT; all checks
are concurrent assertions.

Key SVAs:
```systemverilog
// VALID must not deassert before READY (no early withdrawal)
property p_awvalid_stable;
    @(posedge clk) disable iff (!rst_n)
    (s_awvalid && !s_awready) |=> s_awvalid;
endproperty
assert property (p_awvalid_stable) else $error("AW: VALID withdrew before READY");

// Same for WVALID, ARVALID
// BRESP/RRESP must be OKAY (2'b00) for all successful transactions
property p_bresp_okay;
    @(posedge clk) disable iff (!rst_n)
    (s_bvalid && s_bready) |-> (s_bresp == 2'b00);
endproperty
assert property (p_bresp_okay) else $error("Write response: non-OKAY");

// done must not persist more than one cycle
property p_done_pulse;
    @(posedge clk) disable iff (!rst_n)
    $rose(core_done) |=> !core_done;
endproperty
assert property (p_done_pulse) else $error("done did not deassert after one cycle");

// C_REG must not change while busy=0 and done=0 (output stable between runs)
property p_c_stable;
    @(posedge clk) disable iff (!rst_n)
    (!core_busy && !core_done) |=> $stable(core_C);
endproperty
assert property (p_c_stable) else $error("C_REG changed outside compute window");
```

Cover groups:
- All AXI write targets: CTRL, A_REG[0], A_REG[8], B_REG[0], B_REG[8], C_REG reads
- FSM state transitions in the compute core
- Edge cases: soft_rst mid-compute, back-to-back start pulses, read of C while busy

### 4.3 Clock Generator (`clk_gen_tb.sv`)

```systemverilog
module clk_gen #(
    parameter real CLK_PERIOD_NS = 10.0   // 100 MHz default
)(
    output logic clk
);
    initial clk = 0;
    always #(CLK_PERIOD_NS / 2.0) clk = ~clk;
endmodule
```

Instantiated in each top-level TB. Period parameter set to 10 ns (100 MHz) to
match the AXI4-Lite target frequency and the OOC synthesis constraint.

### 4.4 Compute Core Checker (`checker.sv`)

The checker is split into two layers: a **functional output checker** (task-
based, triggered after each compute) and an embedded **checker block** of
concurrent SVAs that monitor compute-core behaviour across every clock cycle.

#### Functional Output Checker (existing)

```systemverilog
module checker #(
    parameter real ULP_TOLERANCE = 1.0    // max allowed ULP error per element
)(
    input logic        clk,
    input logic        check_en,          // assert for one cycle after done
    input logic [63:0] dut_C   [0:8],
    input logic [63:0] ref_C   [0:8],
    // Core internals — needed by checker block assertions below
    input logic        core_start,
    input logic        core_busy,
    input logic        core_done,
    input logic        core_rst_n
);
```

On `check_en`, for each of the 9 elements: compute the absolute ULP distance
between `dut_C[i]` and `ref_C[i]` by comparing the raw 64-bit integer
representations (both positive: `|dut - ref| <= 1`). Report with `$error` if
any element exceeds `ULP_TOLERANCE`.

Reference values for `ref_C` are computed by the `program_block` using the
same F64 arithmetic sequence as the Eigen GEMM path.

#### Checker Block — Compute Core Functional Assertions

A `checker` block inside `checker.sv` holds concurrent SVAs that fire on every
clock edge and verify the compute core's control-path contracts independent of
any particular input stimulus.

```systemverilog
checker compute_core_checker (
    input logic clk,
    input logic core_start,
    input logic core_busy,
    input logic core_done,
    input logic core_rst_n
);
    default clocking cb @(posedge clk); endclocking
    default disable iff (!core_rst_n);

    // 1. start must not be asserted while busy
    //    (the slave must not re-fire before the previous compute finishes)
    property p_no_start_while_busy;
        !( core_start && core_busy );
    endproperty
    assert property (p_no_start_while_busy)
        else $error("CHECKER: start asserted while core is busy");

    // 2. busy must rise within one cycle of start
    property p_busy_follows_start;
        core_start |=> core_busy;
    endproperty
    assert property (p_busy_follows_start)
        else $error("CHECKER: busy did not assert the cycle after start");

    // 3. busy must be HIGH for at least 3 cycles (minimum GEMM latency)
    //    Ensures the core does not spuriously short-circuit the pipeline
    property p_busy_min_duration;
        $rose(core_busy) |-> core_busy [*3];
    endproperty
    assert property (p_busy_min_duration)
        else $error("CHECKER: busy deasserted in fewer than 3 cycles (pipeline underrun)");

    // 4. done must not assert without busy having been HIGH (no phantom done)
    property p_done_requires_busy;
        $rose(core_done) |-> $past(core_busy, 1);
    endproperty
    assert property (p_done_requires_busy)
        else $error("CHECKER: done rose without a preceding busy cycle");

    // 5. busy and done must be mutually exclusive
    property p_busy_done_mutex;
        !(core_busy && core_done);
    endproperty
    assert property (p_busy_done_mutex)
        else $error("CHECKER: busy and done asserted simultaneously");

    // 6. After done pulses, busy must be LOW (core returned to idle)
    property p_idle_after_done;
        $rose(core_done) |=> !core_busy;
    endproperty
    assert property (p_idle_after_done)
        else $error("CHECKER: core still busy after done pulse");

    // 7. done must be a single-cycle pulse (no multi-cycle done)
    property p_done_one_cycle;
        $rose(core_done) |=> !core_done;
    endproperty
    assert property (p_done_one_cycle)
        else $error("CHECKER: done held HIGH for more than one cycle");

    // Cover: a full start → busy → done sequence completes
    cover property ( core_start ##1 core_busy [*1:$] ##1 core_done )
        $display("CHECKER cover: full compute cycle observed");

endchecker
```

The checker block is instantiated once inside each top-level TB (`tb_option_a.sv`,
`tb_option_b.sv`), bound to the same `clk`, `core_*` signals that connect the
`axilite_slave` to the compute core, so all seven properties fire across every
iteration of the 15-run `program_block` sequence.

#### Directory and File Creation Note

`project/new_hdl/tb/` does not yet exist. Before writing `checker.sv`, the
directory must be created:

```
mkdir -p project/new_hdl/tb
mkdir -p project/new_hdl/rtl
mkdir -p project/new_hdl/synth
mkdir -p project/new_hdl/reports
```

All four subdirectories should be created together so the full tree matches
the layout in section 0.

### 4.5 Test Program Block (`program_block.sv`)

Replicates the Kalman filter GEMM sequence observed in `RVfpgaEL2_profiling/`:

```
Dominant kernel:   3×3 matrix-matrix multiply C = A × B
Profiled call:     Eigen Matrix<double> GEMM inside kf.update()
Inputs:            Fixed seed matrices from gprof arc-table capture
Iterations:        15 (matching the 15-run profiling session)
```

The program block:
1. Defines 15 pairs of {A, B} input matrices (hard-coded F64 constants matching
   the profiling session's input domain)
2. For each pair: calls `bfm.write_matrix_A()`, `bfm.write_matrix_B()`,
   `bfm.fire_and_wait()`, `bfm.read_matrix_C()`
3. Computes software reference `ref_C` in SystemVerilog real arithmetic
4. Drives `checker.check_en` to compare hardware vs. reference output
5. At end: reports total pass/fail count and any ULP violations

### 4.6 Top-Level Testbenches

**`tb_option_a.sv`** — instantiates:
- `clk_gen` (CLK_PERIOD_NS=10)
- `veerwolf_bfm`
- `axilite_slave` with `gemm_systolic` bound to core ports
- `axi_monitor` (bind)
- `checker`
- `program_block`

**`tb_option_b.sv`** — same structure with `kalman_update` as the compute core.

### 4.7 Vivado Simulator Runs

Each compute core option gets its own dedicated Vivado project for simulation
and OOC synthesis. These projects contain only the accelerator RTL and TB files
— no RVfpga SoC sources. This keeps elaboration fast and avoids including
synthesis-incompatible tb files in the integration project.

#### Project Layout

```
project/new_hdl/
├── vivado_option_a/
│   └── vivado_option_a.xpr    # Option A sim + OOC project
└── vivado_option_b/
    └── vivado_option_b.xpr    # Option B sim + OOC project
```

#### Creating Each Project (Tcl, non-interactive)

```tcl
# Option A — run from project/new_hdl/
create_project vivado_option_a vivado_option_a \
    -part xc7a100tcsg324-1 -force

# Add RTL sources (synthesis + simulation)
add_files -fileset sources_1 [glob rtl/gemm_systolic.sv]
add_files -fileset sources_1 [glob rtl/axilite_slave.sv]

# Add TB files to simulation fileset only
add_files -fileset sim_1 [glob tb/veerwolf_bfm.sv]
add_files -fileset sim_1 [glob tb/axi_monitor.sv]
add_files -fileset sim_1 [glob tb/clk_gen_tb.sv]
add_files -fileset sim_1 [glob tb/checker.sv]
add_files -fileset sim_1 [glob tb/program_block.sv]
add_files -fileset sim_1 [glob tb/tb_option_a.sv]

set_property top tb_option_a [get_filesets sim_1]
set_property top_lib xil_defaultlib [get_filesets sim_1]
```

Repeat for Option B, substituting `kalman_update.sv` for `gemm_systolic.sv`
and `tb_option_b` as the simulation top.

#### Running the Simulation

```tcl
launch_simulation -mode behavioral
run all
```

#### What to Check Before Synthesis

After `run all` in xsim for each option:

| Check | Expected outcome |
|-------|-----------------|
| No `$error` in Tcl console | All SVA and checker assertions pass |
| `CHECKER cover` printed 15× | Full start→busy→done observed each iteration |
| Waveform: `core_done` single-cycle pulse | Confirm in Wave window |
| Waveform: AXI VALID/READY handshakes | No channel stalls beyond 1 cycle after VALID |
| Simulation exits cleanly | `$finish` reached by `program_block` |

Both options must pass simulation before any synthesis run is launched.

---

## 5. Synthesis Plan

### Run 1 — Out-of-Context ASIC-like Synthesis (both options)

Script: `synth/run_ooc_a.tcl`, `synth/run_ooc_b.tcl`

```tcl
# Example for Option A — run as: vivado -mode batch -source run_ooc_a.tcl
read_verilog -sv [list \
    new_hdl/rtl/f64_mul.sv \
    new_hdl/rtl/f64_add.sv \
    new_hdl/rtl/gemm_systolic.sv \
    new_hdl/rtl/axilite_slave.sv \
    new_hdl/rtl/accel_top_a.sv ]
synth_design -top accel_top_a -mode out_of_context \
             -part xc7a100tcsg324-1
create_clock -period 10.000 -name clk [get_ports clk]
set_input_delay  2.0 -clock clk [all_inputs]
set_output_delay 2.0 -clock clk [all_outputs]
report_utilization    -file new_hdl/reports/ooc_a_utilization.rpt
report_timing_summary -file new_hdl/reports/ooc_a_timing.rpt
report_power          -file new_hdl/reports/ooc_a_power.rpt
```
Option B: same script with `f64_mul`, `f64_add`, `gemm_systolic`, `kalman_update`,
`axilite_slave_b`, `accel_top_b` as sources, and `-top accel_top_b`.

Metrics collected per option:

| Metric | Option A (GEMM) | Option B (Kalman) |
|--------|-----------------|-------------------|
| LUT count | — | — |
| FF count | — | — |
| WNS (ns) | — | — |
| Power (mW) | — | — |
| Latency (cycles) | — | — |

**Selection criterion:** option with higher throughput (GFLOP/s = ops / (latency ×
period)) and better energy per F64-GEMM call (power × latency × period) is
selected for Run 2. If WNS is negative for 100 MHz, reduce clock to 50 MHz for
that option before comparing.

### Run 2 — SoC Integration Synthesis (winning option)

Script: `synth/run_soc_integration.tcl`

Starts from `project/project_1/project_1.xpr`, which already contains the full
RVfpga SoC source tree (LiteDRAM, VeerWolf, AXI interconnect, board constraints
for xc7a100tcsg324-1). The winning compute core and AXI slave are added on top.

```tcl
# Open the existing SoC project — do not create a new one
open_project project/project_1/project_1.xpr

# Add the winning option's RTL to sources_1 (synthesis fileset)
# Replace accel_top_b and kalman_update if Option A wins, or vice versa
add_files -fileset sources_1 [list \
    new_hdl/rtl/f64_mul.sv \
    new_hdl/rtl/f64_add.sv \
    new_hdl/rtl/gemm_systolic.sv \
    new_hdl/rtl/axilite_slave.sv \
    new_hdl/rtl/accel_top_a.sv ]
# Swap accel_top_b.sv + kalman_update.sv above if Option B wins

# Wire axilite_slave as a new slave on axi_intercon:
# - Add a 4 KB address range at 0x8000_0000 in the interconnect wrapper
# - Connect s_awaddr/s_wdata/... ports to the next free slave slot
# (edit done manually in the SoC top-level wrapper before running synth)

synth_design   -top rvfpganexys -part xc7a100tcsg324-1
# accel_top_a (or _b) is instantiated inside the SoC wrapper
opt_design
place_design
route_design

report_utilization    -file new_hdl/reports/soc_utilization.rpt
report_timing_summary -file new_hdl/reports/soc_timing.rpt
report_drc            -file new_hdl/reports/soc_drc.rpt
```

- The existing `constrs_1` fileset in `project_1` already contains the Nexys A7
  pin and timing constraints; no new XDC file is needed for the accelerator
  unless additional I/O is required (it is not — the accelerator is internal)
- Report: post-route timing summary, full-SoC utilization, interface DRC

---

## 6. Deliverables Checklist

- [ ] `rtl/f64_mul.sv` — synthesisable IEEE-754 F64 multiplier
- [ ] `rtl/f64_add.sv` — synthesisable IEEE-754 F64 adder
- [ ] `rtl/gemm_systolic.sv` — synthesisable, passes OOC timing at 100 MHz
- [ ] `rtl/kalman_update.sv` — synthesisable, wraps gemm_systolic
- [ ] `rtl/axilite_slave.sv` — synthesisable AXI4-Lite slave (Option A register map)
- [ ] `rtl/accel_top_a.sv` — Option A synthesis top: slave + gemm_systolic
- [ ] `rtl/accel_top_b.sv` — Option B synthesis top: slave + kalman_update
- [ ] `rtl/clk_gen.sv` — simulation clock generator (non-synthesisable, sim_1 only)
- [ ] `tb/veerwolf_bfm.sv` — behavioral VeerWolf AXI master model
- [ ] `tb/axi_monitor.sv` — protocol monitor with SVAs on all AXI channels
- [ ] `tb/checker.sv` — ≤ 1 ULP F64 output comparator
- [ ] `tb/program_block.sv` — 15-iteration GEMM program matching profiling data
- [ ] `tb/tb_option_a.sv` — top-level TB for Option A, all assertions pass
- [ ] `tb/tb_option_b.sv` — top-level TB for Option B, all assertions pass
- [ ] `synth/run_ooc_a.tcl` + `reports/ooc_a_*.rpt` — OOC synthesis for Option A
- [ ] `synth/run_ooc_b.tcl` + `reports/ooc_b_*.rpt` — OOC synthesis for Option B
- [ ] `synth/run_soc_integration.tcl` + `reports/soc_*.rpt` — SoC integration for winner
- [ ] `reports/` populated and reviewed before option selection

---

## 7. Constraints and Risks

| Risk | Mitigation |
|------|------------|
| F64 FMA critical path > 10 ns | Pipeline the FMA; fall back to 50 MHz if needed |
| Option B latency too high due to Newton-Raphson iterations | Pre-compute `inv(S)` outside the core if S is scalar (it is for n=3, m=1) |
| AXI4-Lite 64-bit bus — one beat per F64 word | DATA_WIDTH=64 throughout; no beat-splitting; direct connection to VeerWolf crossbar |
| Veerwolf AXI interconnect address map conflict | Accelerator placed at 0x80010000–0x80011000 (outside existing IO range 0x80000000–0x80004000) |
| Disk space during SoC run | Run OOC synthesis first, archive OOC project before opening SoC project |
