#include "mpi.h"

#define MASTER 0

int main(void) {
    // ...
    int n;
    int rank;
    MPI_Comm_size(MPI_COMM_WORLD, &n);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int x;
    if (rank == MASTER) {
        // Input x
    }
    MPI_Group globalGroup;
    MPI_Comm_group(MPI_COMM_WORLD, &globalGroup);
    MPI_Comm newComm;
    MPI_Group newGroup;
    int ranges[][3] = {{0, n/2, 1}};
    MPI_Group_range_incl(globalGroup, 1, ranges, &newGroup);
    MPI_Comm_create(MPI_COMM_WORLD, newGroup, &newComm);
    if (rank < n/2) {
        MPI_Bcast(&x, 1, MPI_INT, MASTER, newComm);
    }
    // ...
}
