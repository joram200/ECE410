# Partition Rationale

![Roofline Model](codefest/cf02/profiling/roofline_project.png)
Check the roofline_project.png in the profiling directory for the model referenced here.

For my project I'll be focusing on the update kernel of the Basic Kalman Filter using this github repository since the profiling of the AI shows it is the most computational dominant of the algorithm. The software baseline for the update kernel according to the AI profile is 230 FLOP/s. With an arithmetic intensity is 0.1969 FLOP/byte assuming the native implementation, This makes the kernel memory-bound meaning it's highest attainable performance is 10.08 GFLOP/s.

My implementation will have to involve changing the kernel code to do tiling in order to reduce the number of memory accesses required although I doesn't think it'll result in changing the kernel's boundness. The rest of the software will remain the same since there's not much more execution time spent in any of the other kernels. I'll also have to add the accelerator to the PCIe interface of the i7-11800H platform since the requied bandwidth is that of the peak bandwidth as shown in interface_selection.md. I have also considered using the RVfpgaEL2 for the NexysA7-DDR so I could actually demonstrate performance gain on separate platform from my laptop and the kernel becoming compute bounded; However, I ultimately decided against it since the computation ceiling was far to low for my liking. My accelerator will probably consist of dedicated cache for the Kalman filter due to the kernel being memory bound. 
