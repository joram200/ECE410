### Kalman Filter Profiling and Hardware Acceleration Analysis

This briefing document synthesizes the profiling data, theoretical foundations, and hardware implementation results for a Kalman Filter project targeting the RVfpgaEL2 (SweRV EL2 core) on a Nexys A7 FPGA.

#### Executive Summary

Deep analysis of the Kalman filter implementation reveals that the 3x3 Matrix-Matrix Multiplication (GEMM) is the dominant computational bottleneck, performing at 1.38e-4 GFLOP/s on the bare-metal SweRV EL2 core. To address this, a hardware accelerator (Option B: Kalman Update Accelerator) was designed and implemented in Milestone 3 (M3).While implementation results confirm the functional correctness of the hardware—achieving a 100% pass rate in co-simulation across 15 iterations—the current RTL design faces significant timing challenges. The synthesis report identifies a Worst Negative Slack (WNS) of \-50.419 ns at 100 MHz, limiting the maximum operating frequency to approximately 16.6 MHz. This timing failure is rooted in the combinational depth of the Newton-Raphson reciprocal update loop. Future development (Milestone 4\) must prioritize pipelining these arithmetic chains to achieve timing closure at 100 MHz and complete full System-on-Chip (SoC) integration.

#### 1\. Theoretical Foundation: The Kalman Filter

The Kalman filter is a recursive mathematical solution used to estimate the state of a discrete-time controlled process. It minimizes the mean of the squared error through a feedback control loop consisting of two primary phases.

##### 1.1 The Two-Step Recursive Cycle

The filter operates in an ongoing cycle of prediction and correction:

* **Time Update ("Predict"):**  These equations project the current state ( $\\hat{x}*{k-1}$ ) and error covariance ( $P*{k-1}$ ) forward in time to obtain  *a priori*  estimates for the next step.  
* **Measurement Update ("Correct"):**  These equations incorporate new noisy measurements into the  *a priori*  estimate to obtain an improved  *a posteriori*  estimate.

##### 1.2 Key Mathematical Components

Component,Description  
Innovation (Residual),The discrepancy between the predicted measurement and the actual measurement ( $z\_k \- H\\hat{x}^-\_k$ ).  
Kalman Gain (  $K$  ),"A blending factor that weights the residual. As measurement error covariance ( $R$ ) approaches zero, the gain trusts the measurement more."  
Error Covariance (  $P$  ),Reflects the variance of the state distribution; it stabilizes quickly under constant conditions.

#### 2\. Software Profiling and Performance Baseline

Profiling was conducted on the Nexys A7 FPGA platform using the SweRV EL2 core. Initial attempts to use UART-based gprof instrumentation were abandoned due to BSP UART FIFO hangs. Successful data was obtained via GDB JTAG memory-dumping.

##### 2.1 Profiling Metrics (Bare-Metal)

* **Dominant Kernel:**  3x3 Matrix-Matrix Multiplication (GEMM).  
* **Arithmetic Intensity:**  0.21 FLOP/byte (categorized as compute-bound).  
* **Performance:**  1.38e-4 GFLOP/s.  
* **Peak Performance observed:**  1.73e-4 GFLOP/s.  
* **Memory Requirement:**  216 bytes per GEMM call.

#### 3\. Hardware Accelerator Architecture (Milestone 3\)

The project moved toward hardware acceleration (Option B) to offload the Kalman update kernel. The design integrates a 3x3 systolic GEMM array and double-precision (F64) arithmetic units.

##### 3.1 RTL Module Hierarchy

1. **f64\_mul**  **:**  Combinational IEEE-754 double-precision multiplier (infers DSP48E1 chains).  
2. **f64\_add**  **:**  Combinational IEEE-754 double-precision adder/subtractor with normalisation and rounding.  
3. **gemm\_systolic**  **:**  A weight-stationary array for 3x3 matrix multiplication.  
4. **kalman\_update**  **:**  The central kernel controlling the update Finite State Machine (FSM).  
5. **axilite\_slave**  **:**  AXI4-Lite register file interface (64-bit data width).  
6. **top**  **:**  Integration module combining the slave interface and the compute core.

##### 3.2 Hardware-Software Interface

The accelerator is accessed via an AXI4-Lite slave port with an 8-byte stride register map:

* **0x00 (CTRL):**  Control register (Bit 0: Start, Bit 1: Soft Reset).  
* **0x08 (STAT):**  Status register (Bit 0: Done, Bit 1: Busy).  
* **0x10-0x50:**  Input registers for measurement ( $z$ ), state ( $x\_{in}$ ), and covariance ( $P\_{in}$ ).  
* **0xA0-0xE0:**  Output registers for corrected state and covariance.

#### 4\. Implementation Results and Performance Analysis

Milestone 3 results provide a detailed view of the accelerator's current capabilities and physical constraints on the Artix-7 100T FPGA.

##### 4.1 Functional Verification

The design successfully passed behavioral co-simulation.

* **Iteration Count:**  15 Kalman iterations.  
* **Result Verification:**  135/135 elements verified against a software reference.  
* **Error Tolerance:**  \< 4 Unit in the Last Place (ULP) for Newton-Raphson convergence.

##### 4.2 Physical Synthesis Metrics

Synthesis was performed in Out-of-Context (OOC) mode targeting the xc7a100tcsg324-1 device at a 100 MHz target.| Resource | Used | Available | Utilization || \------ | \------ | \------ | \------ || **Slice LUTs** | 14,642 | 63,400 | 23.09% || **Slice Registers** | 5,535 | 126,800 | 4.37% || **DSP48E1** | 126 | 240 | 52.50% || **Static Power** | 85 mW | \- | \- || **Total Power** | 358 mW | \- | \- |

##### 4.3 Timing and Critical Path Analysis

The design failed to meet the 10 ns clock period (100 MHz) requirement.

* **Worst Negative Slack (WNS):**  \-50.419 ns.  
* **Data Path Delay:**  60.379 ns.  
* **Logic Levels:**  92 stages.  
* **Identified Critical Path:**  The Newton-Raphson reciprocal update loop in kalman\_update. This path involves chained F64 multiplications and subtractions ( $nr\\\_x\\\_new \= nr\\\_x \* (2.0 \- S \* nr\\\_x)$ ) performed in a single clock cycle.

#### 5\. Identification of Issues and Strategic Plan

##### 5.1 Known Issues

* **Combinational Depth:**  The f64\_mul and f64\_add modules are purely combinational. Chaining them in the Newton-Raphson datapath creates a logic depth that is impossible to close at 100 MHz on the target Artix-7 fabric.  
* **Partial Readback:**  Only 6 of 9 covariance elements ( $P\_{out}$ ) are currently visible via AXI reads due to a 9-element constraint in the axilite\_slave register window.  
* **Resource Intensity:**  DSP utilization is high (52.5%), largely due to the 53x53-bit mantissa products required for F64 arithmetic.

##### 5.2 Future Directives (Milestone 4\)

To transition from a standalone accelerator to a functional SoC component, the following steps are required:

1. **Timing Remediation:**  Implement pipeline registers in the Newton-Raphson datapath. Specifically, adding registers after the u\_nr\_mul1 and u\_nr\_mul2 outputs will reduce the critical path from 92 logic levels to approximately 30\.  
2. **SoC Integration:**  Connect the top module as Slave S3 on the VeerWolf AXI interconnect at address 0x80010000.  
3. **Software Driver Development:**  Write a bare-metal C driver to handle MMIO operations (writing inputs, polling status, and reading results).  
4. **Final Benchmarking:**  Compare the GFLOP/s of the hardware-accelerated path against the software baseline of 1.38e-4 GFLOP/s to determine the final speedup ratio.

