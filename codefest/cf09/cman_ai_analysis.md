# AI Analysis

## Domminant Kernal

The kernal that is accelerated by the hardware is the basic Kalman Filter measurment correction from the update function for 1D projectile motion from the Software baseline. The state error covariance (P) is a __**3x3 matrix**__, state estimate (x) is a __**3 element vector**__, and __**scaler elements**__ such as the actual measurement (z) and measurement noise covariance (R). All elements are the data type __**64-bit IEEE-754 doubles**__.

## Arithmetic Intensity Calculation

### Performance (FLOPs)

First I'll find the number of MACs and then add any other operations used in the Kalman Update Hardware

The MACs are calculated with N<sup>2</sup> that accounts for the GEMM systolic array adding two MACs from `2.0 - S * x` and `x_reg[i] + K[i]*y_tilde` with the total being __N<sup>2</sup> + 2__. 3<sup>2</sup> + 2 = __11 MACs__  

In terms of total FLOPs, every MAC operation is 2 FLOPs and I only need to add the two extra operations for `x_new = x * (2.0 - S * x)` and `IKH[0,0] = 1 - K[0]` with the total being __2 ⋅ MACs + 2__. 2 ⋅ \(11 MACs\) + 2 = __**24 FLOPs**__  

### Bandwidth (Bytes)

Here is the register map for this accelerator:

```
Register map (via axilite_slave, 8-byte stride):
   0x00  CTRL   R/W  [0]=start, [1]=soft_rst
   0x08  STAT   RO   [0]=done,  [1]=busy
   0x10  z            A_REG[0]  WO
   0x18–0x28  x_in[0:2]  A_REG[1:3]  WO
   0x30–0x40  x_out[0:2] A_REG[4:6]  RO
   0x58–0x98  P_in[0:8]  B_REG[0:8]  WO
   0xA0–0xE0  P_out[0:8] C_REG[0:8]  RO  (all 9 elements)
   0xE8       R          R_REG        R/W (default 5.0)
```

The working set is __no-reuse__ with registers 0x10—0x40 and 0x58—0xE0 stored and loaded applies for every iterations \(R is loaded in at the begaining\). This results in __19 writes__ and __15 reads__ in the accelerator which makes __34 total transactions__. With each transaction being 8 bytes wide we get a total of __**272 Bytes**__

### Final Calculation

Now that the Performance and Bandwidth of the accelerator, I can calculated the Arithmetic Intensity with the formula AI = Performance / Bandwidth.
AI = 24 FLOPs / 272 Bytes = __0.088 FLOP/Byte__.

## Roofline Sketch

![Roofline Sketch]{cman_roofline_sketch.png}

## Bottleneck and Improvements

The limiting factor is the AXI memory bandwidth since tere are 34 memory transactions for each 8 byte register elements. The improvement I would try to implement is AXI burst mode with the registers to reduce the number of transactions on the Bus.
