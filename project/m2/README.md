# Milestone 2 — RTL Compute Core & Interface

## Repository layout

```
project/m2/
  rtl/
    compute_core.sv      Kalman-filter compute core (Q16.16 fixed-point, 7-stage FSM)
    interface.sv         PCIe Gen4 TLP endpoint (MWr32/MRd32, 128-bit AXI4-Stream)
  tb/
    tb_compute_core.sv   Self-checking testbench for compute_core
    tb_interface.sv      Self-checking testbench for pcie_tlp_ep
  sim/
    compute_core_run.log Committed simulation log — compute_core (shows PASS)
    interface_run.log    Committed simulation log — interface    (shows PASS)
    tb_compute_core.vcd  VCD waveform — compute_core run
    tb_interface.vcd     VCD waveform — interface run
    tb_compute_core.gtkw GTKWave save file for compute_core waveform
    waveform.png         Annotated GTKWave screenshot (compute_core)
```

---

## Prerequisites

| Tool | Minimum version | Notes |
|------|-----------------|-------|
| Verilator | 5.0 | Requires `--timing` and `--trace` support; tested on 5.046 |
| g++ | 11 | C++20 coroutines (`-fcoroutines`) required by Verilator timing |
| GNU make | any | Invoked automatically by Verilator |
| Python 3 | 3.10 | Only needed to re-run the reference model (`project/profiling/kalman_profile.py`) |

Install on Arch Linux:
```
sudo pacman -S verilator gcc python
```

---

## Build and run — compute_core testbench

All commands run from `project/m2/tb/`.

```bash
# 1. Lint only (no output binary)
verilator --lint-only -sv ../rtl/compute_core.sv tb_compute_core.sv

# 2. Compile simulation binary with VCD tracing
M2=$(pwd)/..
verilator --binary --timing --trace \
    -sv ../rtl/compute_core.sv tb_compute_core.sv \
    -o "$M2/sim/Vtb_compute_core" \
    --Mdir "$M2/sim/verilator_obj"

# 3. Run and capture log
"$M2/sim/Vtb_compute_core" | tee "$M2/sim/compute_core_run.log"
```

Expected last line of output: `PASS`

The VCD is written to `project/m2/sim/tb_compute_core.vcd`.
Open with GTKWave and load `project/m2/sim/tb_compute_core.gtkw` for the
pre-configured signal layout.

---

## Build and run — interface testbench

All commands run from `project/m2/tb/`.

```bash
# 1. Lint only
verilator --lint-only -sv ../rtl/interface.sv tb_interface.sv

# 2. Compile
M2=$(pwd)/..
verilator --binary --timing --trace \
    -sv ../rtl/interface.sv tb_interface.sv \
    -o "$M2/sim/Vtb_interface" \
    --Mdir "$M2/sim/verilator_iface_obj"

# 3. Run and capture log
"$M2/sim/Vtb_interface" | tee "$M2/sim/interface_run.log"
```

Expected last line of output: `PASS`

The three tests exercised:

| Test | Transaction | Assertion |
|------|-------------|-----------|
| 1 | MWr32 → CTRL (0x00) | `dut.reg_ctrl == 0xDEADBEEF` via hierarchical ref |
| 2 | MRd32 ← CTRL (0x00) | Full 128-bit CplD matches expected (completer ID, echoed req_id/tag, read data) |
| 3 | MWr32 → MEAS (0x08) | `core_valid_in` high exactly one cycle; `core_y == 0xCAFEBABE` |

---

## Deviations from the M1 plan

### 1. Arithmetic precision: float64 → Q16.16 fixed-point

**M1 plan** (`sw_baseline.md`): the software baseline runs the Kalman filter in
NumPy float64, giving ~15 significant decimal digits of precision.

**M2 implementation**: `compute_core.sv` uses Q16.16 signed fixed-point
(32-bit word, 16 integer bits, 16 fractional bits).  Resolution is 1/65536 ≈
1.5 × 10⁻⁵; the maximum representable magnitude is 32767.9999847.

**Impact**: for the 45-measurement test vector, the final state estimates match
the Python float64 reference to within 0 LSB (exact match) because the input
measurements and filter constants fit comfortably within the Q16.16 range.
Inputs near the representable limits or with large dynamic range would saturate
or accumulate rounding error.  This is an intentional hardware trade-off
(area/power) accepted at M2.

### 2. Reset scheme differs between the two M2 modules

`compute_core.sv` uses a **synchronous, active-HIGH** reset (`rst`).
`interface.sv` uses an **asynchronous, active-LOW** reset (`rst_n`).

M1 did not specify a reset convention.  The difference is intentional:
the compute core is an interior datapath block where synchronous reset
avoids combinational reset fan-out; the PCIe endpoint is a boundary module
where asynchronous reset is conventional so the interface can be deasserted
before a clock is available.  A real integration would need level-shifters or
a reset synchronizer between the two reset domains.

### 3. PCIe implementation scope: TLP model only, no MAC/PHY

**M1 plan** (`interface_selection.md`): selected PCIe Gen4 to match the
i7-11800H's 51.2 GB/s memory bandwidth requirement identified by profiling.

**M2 implementation**: `interface.sv` implements the **Transaction Layer** only
— it decodes MWr32 and MRd32 TLPs arriving on a 128-bit AXI4-Stream bus and
returns CplD TLPs on the same bus.  There is no Data Link Layer (DLLP, LCRC,
ACK/NAK), no Physical Layer (8b/10b or 128b/130b encoding, lane bonding,
equalization), and no PCIe root complex.

This is appropriate for RTL simulation and FPGA soft-IP integration (e.g.,
Xilinx PCIe Hard IP exposes exactly this AXI4-Stream TLP interface), but a
full-chip ASIC integration would require a hard or soft PCIe PHY sitting
beneath the TLP layer.  The bandwidth claim from M1 (51.2 GB/s) applies to
the full Gen4 ×16 link and is not changed by this scoping decision.
