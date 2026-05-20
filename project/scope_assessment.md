# Project Scope Assessment — Week 7
**Date:** 2026-05-19 | **Milestone next due:** M3 (Sun, May 24)

---

## Scope Changes Since M1/M2

This assessment documents a significant scope revision driven by two practical constraints: (1) the original i7-11800H laptop baseline does not reflect a realistic deployment target for a hardware accelerator, and (2) disk space limitations on the host machine prevent installing OpenLane 2 and Docker simultaneously with the existing Vivado installation.

---

## 1. Platform Change: i7-11800H → RVfpgaEL2 (SweRV EL2 on Nexys A7)

### Reason
The original M1/M2 baseline was profiled on a desktop-class x86 CPU. Replacing it with the RVfpgaEL2 FPGA board (SweRV EL2 RISC-V core, Nexys A7) provides a more meaningful comparison point: a chiplet accelerator added to the same AXI bus the SweRV EL2 uses is an architecturally realistic integration target. Speedup measured against a bare-metal RISC-V baseline is directly attributable to the hardware, not compiler or ISA differences.

### New Software Baseline (RVfpgaEL2 Hardware Profiling)
Profiling was conducted on actual hardware using a GDB JTAG memory-dump method (gprof arc-table read directly from SRAM via hardware breakpoints, bypassing UART) across 15 runs.

| Metric | Value |
|---|---|
| **Platform** | SweRV EL2, Nexys A7 FPGA, 320 MHz, rv32imac/ilp32 |
| **Firmware** | Eigen 5.0.0 Kalman filter (C++14, bare-metal, -pg instrumented) |
| **Dominant kernel** | 3×3 matrix-matrix multiplication (GEMM) — Eigen `Matrix<double>` |
| **Measured performance** | **1.38 × 10⁻⁴ GFLOP/s** |
| **Peak achievable** | 1.73 × 10⁻⁴ GFLOP/s |
| **Memory per GEMM call** | 216 bytes |
| **Arithmetic intensity** | **0.21 FLOP/byte** (compute-bound on this core) |

The 3×3 GEMM is dominant because Eigen's Kalman update path (`kf.update()`) performs several 3×3 matrix multiplications per step (innovation, Kalman gain, covariance correction) using dynamically-allocated `Matrix<double, -1, -1>` objects. On the SweRV EL2, which has no FPU, every double-precision operation is emulated in software by the GCC runtime (`__adddf3`, `__muldf3`, etc.), making GEMM the overwhelming bottleneck.

---

## 2. New Compute Core: Systolic Array — 3×3 GEMM Engine or Kalman Filter Update Kernel

### Design Options Under Evaluation
Two candidate designs will be prototyped and compared against both the software baseline **and** the power efficiency of a general-purpose FPU if one were added to the SweRV EL2 core:

**Option A — 3×3 GEMM Systolic Array**
- A 3×3 weight-stationary systolic array performing C = A × B in F64
- Directly targets the identified dominant kernel
- 9 MAC units operating in parallel; one output matrix computed in 3 pipeline cycles (one row of A × each column of B per cycle)
- Area-efficient: fixed 3×3 size matches the Kalman filter's state dimension exactly

**Option B — Kalman Filter Update Kernel ASIC**
- Hardwires the full update step: innovation S, Kalman gain K, state correction x, covariance P
- Reuses the 3×3 GEMM array as the inner compute primitive
- Higher throughput for the end-to-end Kalman step, but less general than a standalone GEMM engine

**Selection criterion:** Whichever option demonstrates better throughput speedup over the 1.38 × 10⁻⁴ GFLOP/s software baseline **and** better energy per operation than a soft FPU (estimated ~40 LUT-equivalent per double-precision multiply on 7-series FPGA at 100 MHz) will be carried into M3 synthesis.

### Precision: F64 (IEEE 754 Double)
The Kalman filter uses `double` throughout. Switching to fixed-point (as in the M2 Q16.16 design) would break numerical compatibility with the Eigen-based software. F64 is required to maintain filter convergence and allow a direct output comparison against the software reference. This is a firm constraint.

---

## 3. Interface Change: PCIe TLP → AXI4-Lite (Veerwolf AXI Interconnect)

### Reason
The M2 PCIe TLP endpoint is not compatible with the SweRV EL2 / Veerwolf SoC. The Veerwolf reference design exposes a standard AXI4 interconnect (`axi_intercon` in the RVfpgaEL2 source tree) that all peripherals attach to. An AXI4-Lite slave interface is directly connectable to this bus without any additional bridge logic, and it matches the bandwidth requirement of the 3×3 GEMM kernel at 100 MHz.

### Bandwidth Justification
- GEMM kernel memory traffic: 216 bytes per 3×3 call at F64
- At 100 MHz AXI4-Lite (32-bit data bus, 4-byte per beat): 400 MB/s theoretical
- Required bandwidth to keep the systolic array fed: 9 × 8 bytes × (100 MHz / 3 cycles) ≈ 2.4 GB/s for continuous streaming — AXI4-Lite is not streaming-capable at this rate
- Practical mitigation: the accelerator will buffer a full 3×3 input matrix (72 bytes at F64) via a register file written over AXI4-Lite before firing the compute; the AXI interface only needs to sustain the load/store rate of the CPU, not the internal MAC rate

The interface is not the bottleneck for the register-file-load model. AXI4-Lite is the correct choice for control-plane access to the accelerator's register map, consistent with how all other Veerwolf peripherals operate.

### New Register Map (draft)
| Offset | Name | Dir | Width | Purpose |
|---|---|---|---|---|
| 0x00 | CTRL | R/W | 32 | [0]=start, [1]=soft_rst |
| 0x04 | STAT | RO | 32 | [0]=done, [1]=busy |
| 0x08–0x47 | A_REG[0..8] | WO | 64 | Input matrix A (9 × F64) |
| 0x48–0x87 | B_REG[0..8] | WO | 64 | Input matrix B (9 × F64) |
| 0x88–0xC7 | C_REG[0..8] | RO | 64 | Output matrix C (9 × F64) |

---

## 4. Verification: Assertions and Coverage

The M2 testbenches verified functional correctness for a single test vector with no structural assertions. For M3, both modules will be re-verified with:

- **SystemVerilog Assertions (SVA):** protocol checks on AXI4-Lite handshake (VALID/READY contract), single-cycle `done` pulse assertion, no output register change while `busy=0`
- **Functional coverage:** cover groups for all AXI transaction types (write A, write B, read C, read STAT), all FSM state transitions in the compute core, and edge cases (back-to-back compute requests, mid-computation soft reset)
- **Reference comparison:** F64 output compared against the software reference matching the chosen design — Eigen `Matrix<double>` output for Option A (3×3 GEMM engine), or `KalmanFilter::update()` from the software baseline for Option B (Kalman Filter update kernel) — on the same inputs, tolerance ≤ 1 ULP rounding error

---

## 5. Synthesis Plan: Two Vivado Runs

OpenLane 2 is specified in the project requirements. However, the host machine does not have sufficient disk space to install OpenLane 2 (requires Docker and ~20 GB of PDK/container images) alongside the existing Vivado 2024.1 installation. As documented in `codefest/cf07/synth/synth_interpretation.md`, Vivado's Out-of-Context synthesis mode was demonstrated to produce ASIC-representative results (no I/O buffers, no clock buffers, full technology-independent timing) for the cf07 crossbar MAC. The same methodology will be applied to the project.

**Run 1 — Out-of-Context (ASIC-like synthesis)**
- `synth_design -mode out_of_context` — removes IBUF/OBUF, no BUFGCTRL
- Produces area (LUT/FF/CARRY4 counts), timing (critical path, WNS, WHS), and power estimates that are technology-independent and directly comparable to OpenLane results at the same process node
- Target: 100 MHz clock constraint (10 ns period), SDC-style I/O delays

**Run 2 — Integrated into Veerwolf SoC AXI Interconnect**
- The compute core + AXI4-Lite interface will be instantiated as a slave on the Veerwolf `axi_intercon`, synthesized as part of the full SoC design targeting the Nexys A7 (xc7a100tcsg324-1)
- This run demonstrates timing closure in the actual deployment context and validates that the AXI slave interface meets the SoC's timing constraints
- Reports: post-implementation timing summary, utilization within the full SoC, and interface-level DRC

---

## 6. Risk Assessment

| Risk | Likelihood | Mitigation |
|---|---|---|
| F64 GEMM too large to close timing at 100 MHz | Medium | If critical path exceeds 10 ns, reduce to 50 MHz; throughput still exceeds software baseline by >100× |
| AXI4-Lite integration breaks Veerwolf timing | Low | Veerwolf peripherals are designed for this bus; interface can be pipelined if needed |
| 3×3 systolic array area too large for Nexys A7 | Low | xc7a100t has 63,400 LUTs; 9 F64 MACs at ~200 LUTs each ≈ 1,800 LUTs (2.8% utilization) |
| Option selection requires both designs to be built | High | Both designs share the same systolic array datapath; Option B wraps Option A |
| Disk space prevents re-running Vivado + Veerwolf together | Medium | Run OOC synthesis on the accelerator alone first; integrate into Veerwolf separately |
