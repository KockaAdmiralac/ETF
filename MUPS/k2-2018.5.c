#include "mpi.h"

#define MASTER 0

int main(void) {
    int width;
    int height;
    int inputImage[1000];
    int outputImage[1000];
    int inputImageRecv[1000];
    int outputImageRecv[1000];
    // ...

    int rank;
    int size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == MASTER) {
        // Input width, height, inputImage.
    }
    int index, n = width * height / size;
    MPI_Bcast(&n, 1, MPI_INT, MASTER, MPI_COMM_WORLD);
    MPI_Scatter(inputImage, n, MPI_INT, inputImageRecv, n, MPI_INT, MASTER, MPI_COMM_WORLD);
    float sum = 0.0, varSum = 0.0, var, svar, std, mean;
    for (index = 0; index < n; index++) sum += (float)(inputImageRecv[index]);
    MPI_Allreduce(&sum, &mean, 1, MPI_FLOAT, MPI_SUM, MPI_COMM_WORLD);
    mean /= (float)(n * size);
    for (index = 0; index < n; index++) {
        svar = (float)(inputImageRecv[index]) - mean;
        varSum += svar * svar;
    }
    MPI_Allreduce(&varSum, &var, 1, MPI_FLOAT, MPI_SUM, MPI_COMM_WORLD);
    var /= (float)(n * size);
    std = sqrtf(var);
    for (index = 0; index < n; index++)
        outputImage[index] = (inputImage[index] - mean)/std;

    MPI_Gather(outputImage, n, MPI_INT, outputImageRecv, n, MPI_INT, MASTER, MPI_COMM_WORLD);
    // ...
}
