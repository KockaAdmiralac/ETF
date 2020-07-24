#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 1000

int main() {
    int mat[6][6] = {
        {INF, 7, 3, 10, 8, INF},
        {INF, INF, INF, 22, INF, 1},
        {INF, INF, INF, 5, 2, INF},
        {INF, INF, INF, INF, INF, 12},
        {INF, INF, INF, 1, INF, INF},
        {6, INF, INF, INF, INF, INF}
    }, t[6][6];
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            t[i][j] = 0;
        }
    }
    for (int k = 0; k < 6; ++k) {
        for (int i = 0; i < 6; ++i) {
            if (mat[i][k] < INF) {
                for (int j = 0; j < 6; ++j) {
                    if (mat[i][k] + mat[k][j] < mat[i][j]) {
                        mat[i][j] = mat[i][k] + mat[k][j];
                        t[i][j] = k + 1;
                    }
                }
            }
        }
        printf("{| class=\"wikitable\"\n|+ ''Floyd''-ov algoritam za <math>k = %d</math>\n", k + 1);
        for (int i = 0; i < 6; ++i) {
            printf("|-\n");
            for (int j = 0; j < 6; ++j) {
                if (j == 0) {
                    printf("| ");
                } else {
                    printf(" || ");
                }
                if (mat[i][j] >= INF) {
                    printf("∞");
                } else {
                    printf("%d", mat[i][j]);
                }
            }
            printf("\n");
        }
        printf("|}\n{| class=\"wikitable\"\n|+ Matrica prethodnika za <math>k = %d</math>\n", k + 1);
        for (int i = 0; i < 6; ++i) {
            printf("|-\n");
            for (int j = 0; j < 6; ++j) {
                if (j == 0) {
                    printf("| ");
                } else {
                    printf(" || ");
                }
                printf("%d", t[i][j]);
            }
            printf("\n");
        }
        printf("|}\n");
    }
    return 0;
}
