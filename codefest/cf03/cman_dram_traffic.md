# CMAN DRAM Analysis

For FP32 matrices NxN where N=32. Writes won't be added to Traffic due to them being negligible.  

## Native triple loop

Due to this approach loading repeated elements, we can estimate the DRAM Reads to A and B is 2\*N^3^ or **65536 loads**  

Adding the Reads and Writes, Total DRAM Traffic is 2\*N^3^\*4 which with N=32 is **256 KB**  

## Tiled loop

Assuming Tile size is T=8 blocked into TxT.  

The DRAM loads is 2\*N^2^ or **2048 loads**  

Total DRAM Traffic is 2\*N^2^\*4 or **8 KB**  

## Tiled Traffic Reduction

There is a 32x reduction in memory traffic which is the exact dimension N due to the Native approach is done N number times over NxN.  

## Execution Time for each case

We will assume DRAM bandwidth is 320 GB/s and compute is 10 TFLOPS which gives a ridge point of 10000 GFLOPS / 320 GB/s = 31.25 FLOP/Byte  

To find fastest possible execution time, we must know it Arithmetic Intensity and Boundness for each case.  

Both operations have the same FLOPs of 2\*N^3^ or 65536  

For the naive case, AI = 65536 FLOPs / 256 KB = 0.25 FLOP/Byte  

For the tiled case, AI = 65536 FLOPs / 8 KB = 8 FLOP/Byte  

Both of these AIs are below the ridge point making them memory-bound  

Since performance is just operations per second, we can inverse it to find the execution time.  

Execution Time for the naive case is 1/(0.25\*320e9) = **12.5 ps**  

Execution Time for the tiled case is 1/(8\*320e9) = **0.390 ps**  
