### Briefing Document: Kalman Filter Hardware Acceleration and Optimization Strategy

#### Executive Summary

The transition of Kalman filter operations from software to specialized hardware acceleration centers on the implementation of the "Option B" Measurement Update Accelerator. While the system successfully passed end-to-end co-simulation—verifying 135/135 elements across 15 data sets with zero failures—the current hardware implementation faces a significant timing bottleneck.The primary technical challenge is a Worst Negative Slack (WNS) of  **\-50.419 ns** , which limits the maximum operating frequency to  **16.6 MHz**  on an Artix-7 100T FPGA, well below the 100 MHz target. This violation is localized to the Newton-Raphson reciprocal loop within the kalman\_update module. Strategically, the system architectural roadmap prioritizes maintaining the Time Update (Predict) phase in software to preserve model flexibility while optimizing the Measurement Update (Correct) phase in hardware. Future development (Milestone 4\) focuses on pipelining the arithmetic datapath and full SoC integration.

#### 1\. Algorithmic Overview: The Kalman Filter Cycle

The Kalman filter is a recursive estimator that minimizes the mean squared error of a process state. As defined in the provided literature, the filter operates in a continuous two-phase cycle:

* **Time Update ("Predict"):**  Responsible for projecting the current state and error covariance ahead in time to obtain  *a priori*  estimates.  
* *Key Equation:*   $P\_k^- \= AP\_{k-1}A^T \+ Q$  
* **Measurement Update ("Correct"):**  Responsible for incorporating new noisy measurements into the  *a priori*  estimate to produce an improved  *a posteriori*  estimate.  
* *Key Equation:*   $P\_k \= (I \- K\_kH)P\_k^-$

##### Tuning Parameters

The filter's performance is governed by two critical noise covariance matrices:

* **$R**$  **(Measurement Noise Covariance):**  Usually determined by offline sample measurements of sensors.  
* **$Q**$  **(Process Noise Covariance):**  Often "injected" as a tuning parameter to account for model uncertainty or changing dynamics.

#### 2\. Hardware Architectural Design (Option B)

The "Option B" accelerator is designed as a specialized corrector, specifically targeting the compute-bound 3x3 General Matrix-Matrix Multiplication (GEMM) kernels found in the correction phase.

##### Module Hierarchy and Functionality

Module,Primary Function  
top,Integration of the AXI4-Lite slave and the Kalman update kernel.  
axilite\_slave,Handles the register map and AXI4-Lite protocol for host communication.  
kalman\_update,"The core FSM that manages the innovation, Newton-Raphson reciprocal, and state correction."  
gemm\_systolic,A 3x3 weight-stationary systolic array for F64 matrix multiplication.  
f64\_mul  /  f64\_add,Purely combinational IEEE-754 double-precision arithmetic units.

##### The Correction Sequence

The hardware Finite State Machine (FSM) executes a series of states to complete the measurement update:

1. **INNOV:**  Latches input measurements ( $z$ ) and prior states ( $x\_{in}, P\_{in}$ ).  
2. **NR0-NR2:**  Executes three Newton-Raphson iterations to compute the reciprocal of the innovation covariance ( $S$ ).  
3. **K\_COMP / X\_CORR:**  Calculates the Kalman Gain and corrects the state vector.  
4. **P\_UPD / WAIT\_P:**  Invokes the systolic array to perform the matrix multiplication  $P \= (I \- KH) \\times P$ .

#### 3\. Performance Analysis and Synthesis Results

Synthesis of the Option B accelerator targeting an Artix-7 100T (xc7a100tcsg324-1) yielded the following metrics:

##### Resource Utilization

The design is characterized by heavy DSP utilization due to the 53x53-bit mantissa multiplications required for F64 arithmetic.| Resource | Used | Available | Utilization || \------ | \------ | \------ | \------ || **Slice LUTs** | 14,642 | 63,400 | 23.09% || **Slice Registers** | 5,535 | 126,800 | 4.37% || **DSP48E1 Tiles** | 126 | 240 | 52.50% || **Block RAM** | 0 | 135 | 0.00% |

##### Timing and Critical Path

The design failed to meet the 100 MHz (10 ns) clock period constraint:

* **Worst Negative Slack (WNS):**  \-50.419 ns  
* **Data Path Delay:**  60.379 ns (92 logic levels)  
* **Max Frequency:**  \~16.6 MHz**Identified Critical Path:**  The path runs through the Newton-Raphson reciprocal update loop. Specifically, it chains two f64\_mul units and one f64\_add unit back-to-back without intermediate pipeline registers. This results in a massive combinational ripple through 6 cascaded DSP48E1 tiles and 43 CARRY4 chains.

#### 4\. Hardware Roadmap and Strategic Recommendations

The current analysis suggests a phased approach to optimization, prioritizing structural fixes over expanding the hardware's functional scope.

##### Prioritizing Correction over Prediction

The Prediction (Time Update) phase is intentionally kept in software for several reasons:

* **I/O Pressure:**  Accelerating the Prediction phase would require 18 additional 64-bit registers for the  $A$  and  $Q$  matrices, which the current axilite\_slave module cannot accommodate.  
* **Model Flexibility:**  Software allows the host CPU to easily update the  $A$  matrix to reflect different time steps ( $dt$ ) or changing physics models (e.g., projectile motion vs. random constant).  
* **Complexity:**  The 3x3 GEMM kernel in the hardware currently targets exactly half of the dominant matrix operations, acting as a "corrector" for the most compute-bound tasks.

##### Near-Term Hardware Improvements

1. **Pipelining the Arithmetic Datapath:**  To achieve the 100 MHz target, pipeline registers must be inserted between the f64\_mul and f64\_add units in the Newton-Raphson chain. This is a prerequisite for making further hardware acceleration viable.  
2. **Dynamic**  **$R**$  **Register:**  Currently, the measurement noise  $R$  is hardcoded as a local parameter (5.0). Adding a programmable 64-bit register for  $R$  would allow for sensor-specific tuning without requiring FPGA resynthesis.  
3. **Resolving**  **$P\_{out}**$  **Truncation:**  The current register map only allows the first 6 of 9 elements of the corrected covariance matrix to be read. Extending the C\_REG window is necessary for full state recovery.

##### Power Estimation

In an Out-of-Context (OOC) synthesis environment, the total on-chip power is estimated at  **358 mW**  (273 mW dynamic, 85 mW static). However, because the Kalman core is expected to sit idle between periodic invocations (e.g., at 100 Hz), the actual average dynamic power is projected to be negligible (\<1 mW).

#### 5\. Conclusion: Milestone 4 Objectives

The next phase of development will transition the verified "Option B" kernel into a functional SoC component. Key objectives include:

* **Timing Closure:**  Adding pipeline registers to eliminate the \-50.419 ns slack.  
* **SoC Integration:**  Mapping the accelerator as an AXI slave at address 0x80010000 on the VeerWolf interconnect.  
* **Benchmarking:**  Measuring the GFLOP/s speedup of the hardware-accelerated path against the bare-metal SweRV EL2 baseline of  $1.38 \\times 10^{-4}$  GFLOP/s.

