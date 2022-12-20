#include "mpi.h"

#define MASTER 0

int* find_all_occurences(char* str, char c, int length, int* locSize) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int* loc = malloc(sizeof(int) * length);
    *locSize = 0;
    for (int i = 0; i < length; i++) {
        if (str[i] == c) {
            loc[(*locSize)++] = i + rank * length;
        }
    }
    return loc;
}

int main(void) {
    // ...
    MPI_Status status;
    int size;
    int rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    char *str, c;
    if (rank == MASTER) {
        // Input str, c
    }
    int length = strlen(str);
    int chunk = length / size;
    MPI_Bcast(&chunk, 1, MPI_INT, MASTER, MPI_COMM_WORLD);
    MPI_Bcast(&c, 1, MPI_CHAR, MASTER, MPI_COMM_WORLD);
    char* myStr;
    if (rank == MASTER) {
        myStr = str;
        for (int i = 1; i < size; ++i) {
            MPI_Send(str + i * chunk, chunk, MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }
    } else {
        myStr = malloc(chunk * sizeof(char));
        MPI_Recv(myStr, chunk, MPI_CHAR, MASTER, 0, MPI_COMM_WORLD, &status);
    }
    int locSize = 0;
    int* loc = find_all_occurences(myStr, c, chunk, &locSize);
    if (rank == MASTER) {
        int totalLocSize = locSize;
        loc = realloc(loc, length * sizeof(int));
        for (int i = 1; i < size; ++i) {
            int otherLocSize;
            MPI_Recv(&otherLocSize, 1, MPI_INT, i, 1, MPI_COMM_WORLD, &status);
            MPI_Recv(loc + totalLocSize, otherLocSize, MPI_INT, i, 2, MPI_COMM_WORLD, &status);
            totalLocSize += otherLocSize;
        }
        loc = realloc(loc, (totalLocSize + 1) * sizeof(char));
        loc[totalLocSize] = -1;
    } else {
        MPI_Send(&locSize, 1, MPI_INT, MASTER, 1, MPI_COMM_WORLD);
        MPI_Send(loc, locSize, MPI_INT, MASTER, 2, MPI_COMM_WORLD);
        free(loc);
    }
    free(str);
    // ...
}
