#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

const int M = 10, N = 10;
int mat[M][N];
int help[M];

int par_sum() {
    int sum = 0;
    pid_t pids[M];
    for (int i = 0; i < M; ++i) {
        pids[i] = fork();
        if (pids[i] == 0) {
            help[i] = 0;
            for (int j = 0; j < N; ++j) {
                help[i] += mat[i][j];
            }
            exit(0);
        }
    }
    for (int i = 0; i < M; ++i) {
        wait(pids[i]);
        sum += help[i];
    }
    return sum;
}
