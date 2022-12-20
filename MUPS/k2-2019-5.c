#include "mpi.h"

#define MASTER 0

int main(void) {
    // ...
    int rank;
    int size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int maxIter;
    if (rank == MASTER) {
        scanf("%d", &maxIter);
    }
    MPI_Bcast(&maxIter, 1, MPI_INT, MASTER, MPI_COMM_WORLD);
    double pi;
    for (int i = rank; i < maxIter; i += rank) {
        pi += ((i & 1) ? -1 : 1)/(2 * i + 1);
    }
    double totalPi;
    MPI_Reduce(&pi, &totalPi, 1, MPI_DOUBLE, MPI_SUM, MASTER, MPI_COMM_WORLD);
    MPI_Bcast(&totalPi, 1, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);
    printf("%lf\n", totalPi);
    // ...
    return 0;
}
