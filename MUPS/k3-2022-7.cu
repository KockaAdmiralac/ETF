#include <cuda_runtime.h>

__global__ void laplace(float* error, float** A, float** Anew, int n, int m) {
    __shared__ float sA[34][34];
    __shared__ float sAnew[32][32];
    __shared__ float serror[32][32];
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;
    int localX = threadIdx.x + 1;
    int localY = threadIdx.y + 1;
    sA[threadIdx.x+1][threadIdx.y+1] = A[x][y];
    if (threadIdx.x == 0 && x != 0) {
        sA[localX-1][localY] = A[x-1][y];
    }
    if (threadIdx.x == blockDim.x-1 && x != m-1) {
        sA[localX+1][localY] = A[x+1][y];
    }
    if (threadIdx.y == 0 && y != 0) {
        sA[localX][localY-1] = A[x][y-1];
    }
    if (threadIdx.y == blockDim.y-1 && y != n-1) {
        sA[localX][localY+1] = A[x][y+1];
    }
    __syncthreads();
    sAnew[threadIdx.x][threadIdx.y] = (sA[localX-1][localY] + sA[localX+1][localY] + sA[localX][localY-1] + sA[localX][localY+1]) / 4;
    serror[threadIdx.x][threadIdx.y] = abs(sAnew[threadIdx.x][threadIdx.y] - sA[localX][localY]);
    __syncthreads();
    if (threadIdx.x == 0) {
        float maxError = 0.0;
        for (int i = 0; i < blockDim.x; ++i) {
            maxError = max(maxError, serror[i][threadIdx.y]);
        }
        serror[threadIdx.x][threadIdx.y] = maxError;
        if (threadIdx.y == 0) {
            maxError = 0.0;
            for (int i = 0; i < blockDim.y; ++i) {
                maxError = max(maxError, serror[threadIdx.x][i]);
            }
            atomicMax(error, maxError);
        }
    }
    Anew[x][y] = sAnew[threadIdx.x][threadIdx.y];
}

int main() {
    // ...
    while (error < tol && iter < iter_max) {
        // ...
        dim3 dimBlock(32, 32);
        dim3 dimGrid(ceil(m/32), ceil(n/32));
        laplace<<<dimBlock, dimGrid>>>(&gpuError, gpuA, gpuAnew, n, m);
        float** gpuAold = gpuA;
        gpuA = gpuAnew;
        gpuAnew = gpuAold;
        // ...
    }
    // ...
    return 0;
}
