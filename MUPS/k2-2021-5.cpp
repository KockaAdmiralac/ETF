#include <cmath>
#include "mpi.h"

double angle_calc(double, double, int, double, double);
double f1_calc(double, double, double, double, double);

#define MASTER 0

double* sin_trans_interpolation(int n, double a, double b, double fa, double fb, double s[], int nx, double x[]) {
    double angle, f1, f2, pi = 3.141592653589793, *value;
    int i, j;
    value = new double[nx];
    for (i = 0; i < nx; i++) {
        f1 = f1_calc(a, b, fa, fb, x[i]); f2 = 0.0;
        for (j = 0; j < n; j++) {
            angle = angle_calc(a, b, j, x[i], pi);
            f2 = f2 + s[j] * sin (angle);
        }
        value[i] = f1 + f2;
    }
    return value;
}

int main(void) {
    // ...
    int size;
    int rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int n, nx = 1;
    double a, b, fa, fb, s[...], x[...];
    if (rank == MASTER) {
        // Input n, a, b, fa, fb, n, nx, s, x
    }
    int ints[] = {n, nx};
    double doubles[] = {a, b, fa, fb};
    MPI_Bcast(ints, 2, MPI_INT, MASTER, MPI_COMM_WORLD);
    MPI_Bcast(doubles, 4, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);
    MPI_Bcast(s, n, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);
    int count = ints[1] / size;
    double* recvX = new double[count];
    MPI_Scatter(x, count, MPI_DOUBLE, recvX, count, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);
    double* value = sin_trans_interpolation(ints[0], doubles[0], doubles[1], doubles[2], doubles[3], s, count, recvX);
    double* recvVal = new double[nx];
    MPI_Gather(value, count, MPI_DOUBLE, recvVal, nx, MPI_DOUBLE, MASTER, MPI_COMM_WORLD);
    delete[] value;
    delete[] recvX;
    // ...
}
