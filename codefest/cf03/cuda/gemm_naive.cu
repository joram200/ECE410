// gemm_naive.cu
// Naive 1024x1024 FP32 GEMM: one thread per output element.
// Compile: nvcc -O2 -o gemm_naive gemm_naive.cu

#include <cmath>
#include <cuda_runtime.h>
#include <cstdio>
#include <cstdlib>

#define N 1024

// Each thread computes one element of C = A * B.
__global__ void gemm_naive(const float *A, const float *B, float *C, int n)
{
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    int row = blockIdx.y * blockDim.y + threadIdx.y;

    if (row < n && col < n) {
        float sum = 0.0f;
        for (int k = 0; k < n; ++k)
            sum += A[row * n + k] * B[k * n + col];
        C[row * n + col] = sum;
    }
}

static void check(cudaError_t err, const char *msg)
{
    if (err != cudaSuccess) {
        fprintf(stderr, "CUDA error at %s: %s\n", msg, cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }
}

int main(void)
{
    const int n   = N;
    const size_t bytes = (size_t)n * n * sizeof(float);

    // Host allocation
    float *hA = (float *)malloc(bytes);
    float *hB = (float *)malloc(bytes);
    float *hC = (float *)malloc(bytes);

    // Initialize with simple values: A = 1, B = 1 → every C[i][j] == n
    for (int i = 0; i < n * n; ++i) { hA[i] = 1.0f; hB[i] = 1.0f; }

    // Device allocation
    float *dA, *dB, *dC;
    check(cudaMalloc(&dA, bytes), "malloc dA");
    check(cudaMalloc(&dB, bytes), "malloc dB");
    check(cudaMalloc(&dC, bytes), "malloc dC");

    check(cudaMemcpy(dA, hA, bytes, cudaMemcpyHostToDevice), "copy A");
    check(cudaMemcpy(dB, hB, bytes, cudaMemcpyHostToDevice), "copy B");

    // 32×32 threads per block → 32×32 blocks for a 1024×1024 matrix
    const int TILE = 32;
    dim3 block(TILE, TILE);
    dim3 grid((n + TILE - 1) / TILE, (n + TILE - 1) / TILE);

    // Warm-up run (avoids first-launch overhead skewing timing)
    gemm_naive<<<grid, block>>>(dA, dB, dC, n);
    check(cudaDeviceSynchronize(), "warm-up sync");

    // Timed run
    cudaEvent_t t0, t1;
    check(cudaEventCreate(&t0), "event create t0");
    check(cudaEventCreate(&t1), "event create t1");

    check(cudaEventRecord(t0), "event record t0");
    gemm_naive<<<grid, block>>>(dA, dB, dC, n);
    check(cudaGetLastError(),  "kernel launch");
    check(cudaEventRecord(t1), "event record t1");
    check(cudaEventSynchronize(t1), "event sync t1");

    float ms = 0.0f;
    check(cudaEventElapsedTime(&ms, t0, t1), "elapsed time");
    cudaEventDestroy(t0);
    cudaEventDestroy(t1);

    // 2*N^3 FLOPs (one multiply + one add per k-step)
    double flops   = 2.0 * (double)n * n * n;
    double gflops  = flops / (ms * 1e-3) / 1e9;

    check(cudaMemcpy(hC, dC, bytes, cudaMemcpyDeviceToHost), "copy C");

    // Verify: every element should equal n
    int errors = 0;
    for (int i = 0; i < n * n; ++i)
        if (fabsf(hC[i] - (float)n) > 1e-3f) ++errors;

    printf("gemm_naive  (%dx%d): %s  |  time = %.3f ms  |  %.2f GFLOP/s  (%d errors)\n",
           n, n, errors == 0 ? "PASS" : "FAIL", ms, gflops, errors);

    cudaFree(dA); cudaFree(dB); cudaFree(dC);
    free(hA); free(hB); free(hC);
    return errors ? EXIT_FAILURE : EXIT_SUCCESS;
}
