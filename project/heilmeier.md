# Answers to Heilmeier Questions
Q1: Improving performance of The Basic Kalman Filter algorithm with deticated hardware.
Q2: When observing the profiling of the The Basic Kalman Filter shown in codefest/cf02/profiling/project_profile.txt, I found that the Computational dominant kernal, kf.update(), that accounts for 2.22% of the run time, uses lots of memory due to its native implmentation of matrrix multiplication causing the AI to into the memory wall.
Q3: I'm creating a deicated cache on the PCIe bus to store excluively the Kalman Filter variables and implementing tiling GEMM into the update kernel software which takes the arithmetic intensity from 0.1155 FLOPs/byte to 0.3702 FLOPs/byte.
