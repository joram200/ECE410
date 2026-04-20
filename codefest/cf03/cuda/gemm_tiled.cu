// gemm_tiled.cu
// Shared-memory tiled 1024x1024 FP32 GEMM with tile size 8.
// Compile: nvcc -O2 -o gemm_tiled gemm_tiled.cu

#include <cmath>
#include <cuda_runtime.h>
#include <cstdio>
#include <cstdlib>

#define N        1024
#define TILE_SIZE 8

// Each thread computes one element of C = A * B using tiled shared memory.
// Block dimensions must match TILE_SIZE × TILE_SIZE.
__global__ void gemm_tiled(const float *A, const float *B, float *C, int n)
{
    // Shared-memory tiles for the current strip of A and B
    __shared__ float tileA[TILE_SIZE][TILE_SIZE];
    __shared__ float tileB[TILE_SIZE][TILE_SIZE];

    int tx  = threadIdx.x;           // column within tile
    int ty  = threadIdx.y;           // row    within tile
    int col = blockIdx.x * TILE_SIZE + tx;  // global column of C
    int row = blockIdx.y * TILE_SIZE + ty;  // global row    of C

    float sum = 0.0f;

    // Sweep over tiles along the K dimension
    int numTiles = (n + TILE_SIZE - 1) / TILE_SIZE;
    for (int t = 0; t < numTiles; ++t) {
        // Load one element of A into shared memory (guard for non-multiple sizes)
        int aCol = t * TILE_SIZE + tx;
        tileA[ty][tx] = (row < n && aCol < n) ? A[row * n + aCol] : 0.0f;

        // Load one element of B into shared memory
        int bRow = t * TILE_SIZE + ty;
        tileB[ty][tx] = (bRow < n && col < n) ? B[bRow * n + col] : 0.0f;

        __syncthreads();

        // Accumulate the partial dot product for this tile
        #pragma unroll
        for (int k = 0; k < TILE_SIZE; ++k)
            sum += tileA[ty][k] * tileB[k][tx];

        __syncthreads();
    }

    if (row < n && col < n)
        C[row * n + col] = sum;
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

    dim3 block(TILE_SIZE, TILE_SIZE);
    dim3 grid((n + TILE_SIZE - 1) / TILE_SIZE, (n + TILE_SIZE - 1) / TILE_SIZE);

    // Warm-up run (avoids first-launch overhead skewing timing)
    gemm_tiled<<<grid, block>>>(dA, dB, dC, n);
    check(cudaDeviceSynchronize(), "warm-up sync");

    // Timed run
    cudaEvent_t t0, t1;
    check(cudaEventCreate(&t0), "event create t0");
    check(cudaEventCreate(&t1), "event create t1");

    check(cudaEventRecord(t0), "event record t0");
    gemm_tiled<<<grid, block>>>(dA, dB, dC, n);
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

    printf("gemm_tiled  (%dx%d, tile=%d): %s  |  time = %.3f ms  |  %.2f GFLOP/s  (%d errors)\n",
           n, n, TILE_SIZE, errors == 0 ? "PASS" : "FAIL", ms, gflops, errors);

    cudaFree(dA); cudaFree(dB); cudaFree(dC);
    free(hA); free(hB); free(hC);
    return errors ? EXIT_FAILURE : EXIT_SUCCESS;
}
