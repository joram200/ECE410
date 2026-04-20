# CMAN DRAM Analysis

For FP32 matrices NxN hwere N=32

## Native triple loop

Due to this approach loading repeated elements, we can estimate the DRAM Reads to A and B is 2\*N^3^ or **65536 loads**

The DRAM Writes are N^2^ due to them not being as frequent

Adding the Reads and Writes, Total DRAM Traffic is 2\*N^3^\*4+N^2^\*4 which with N=32 is **266 KB**

## Tiled loop

Assuming Tile size is T=8 blocked into TxT.

The DRAM loads is 2\*N^2^ or **2048 loads**

The DRAM stores is N^2^ or 1024 stores

Total DRAM Traffic is 3\*N^2^\*4 or **12 KB**

## Tiled Traffic Reduction

There is a 
