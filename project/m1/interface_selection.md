Calculating for the required bandwidth for the update kernel is the throughput times the data width which is 8 bytes (FP64).

87 GFLOP/s \* 8 B = 696 GB/s

Since the titled kernel hits the memory wall it's required bandwidth would be that of **the i7-11800 hardware platform** memory specifications which is __51.2 GB/s__

I shall use PCIe Gen4 interface the processor uses since it matches the same bandwidth that kernel needs which is **51.2 GB/s**.
