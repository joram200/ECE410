# Answers to Heilmeier Questions
1. Improving performance of The Basic Kalman Filter with deticated hardware.
2. When observing the profling of the The Basic Kalman Filter I found that the Computational dominant kernal, kf.update(), uses lots of memory due to its native impelmentation of matrrix multiplication causing the AI to into the memory wall.
3. I'm creating a deicated cache on the PCIe bus to store excluively the Kalman Filter variables and implementing tiling GEMM into the update kernel software.
