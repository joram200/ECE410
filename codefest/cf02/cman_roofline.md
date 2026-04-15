# Roofline construction and kernal classification

All of the following assumes P~peak~=10 TFLOPS (FP32) and B~peak~=320 GB/s. Kernal Perfomance will be assumed to be max of their boundness.

## Roofline Model Calculations

The Roofline model plots Performance of GFLOP/s againist arithmetic intensity of FLOP/byte.

The ridge point is the maximum performance between the P~peak~ and B~peak~ which is 10000/320 or 31.25 FLOP/byte.

The compute ceiling would lay at P~peak~ or 10000 GFLOP/s. The bandwidth ceiling is line with slope of B~peak~ or 320 GFLOP/s at 1 FLOP/byte.

![Roofline Model](/codefest/cf02/cman_roofline.png)
The Roofline model can be seen in cman_roofline.png

## Kernal A — Dense GEMM Calculations

This kernal multiplys two FP32 matrices of size 1024*1024.

FLOPs can be calulated by 2\*N^3^ since the one entry of the N\*N product martrix is the sum of every corresponding row entry of the first matrix and the every corresponding column entry of the second matrix.

The number of bytes can be calulated by (3\*N^2)\*4 since the two operand and result N\*N matrix of FP32 values, which are 4 bytes, must be stored in memory.

The arithmetic intensity is 2\*N^3^/((3\*N^2)\*4) which reduces to N/6. For the square dimension of 1024, that would be around 170.67 FLOP/byte which makes this kernal compute-bound. This means Kernal A's highest attainable performance is P~peak~= 10000 GFLOP/s.

Kernal A would benefit from Hardware accelerator that is optimized for doing simple calculations like a GPU.

## Kernal B — Vector addition

This kernal adds two FP32 vectors of length 4194304 element-wise.

FLOPs can be calulated by N since there is each result vector element is the sum of the the operand vectors

The number of bytes can be calculated (3\*N)\*4 since since the two operand and the result N element vector of FP32 values, which are 4 bytes, must be stored in memory.

The arithmetic intensity is N/((3\*N)\*4) which reduces to 1/12 or around .083 FLOP/byte which makes this kernal is memory-bound with its highest attainable performance is 320\*.083 or around 26.67 GFLOP/s.

Kernal B would benefit from a high speed communication like Gen4 PCIe and UCIe.
