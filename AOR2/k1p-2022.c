#include <stdio.h>
#include <time.h>

extern int** matpp;

void rotateMatrixClockwiseDumb(int** a, int n) {
    int m = n / 2;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            register int t = a[i][j];
            register int ni = i;
            register int nj = j;
            for (int k = 0; k < 4; k++) {
                register int ti = ni;
                ni = nj;
                nj = n - 1 - ti;
                register int old = a[ni][nj];
                a[ni][nj] = t;
                t = old;
            }
        }
    }
}

void rotateMatrixClockwise(int** mat, int n) {
    const int nHalf = n >> 1;
    for (int blockY = 0; (blockY << 4) < nHalf; ++blockY) {
        // Померај тренутног блока по Y оси
        const int offsetY = blockY << 4;
        for (int blockX = 0; (blockX << 4) < nHalf; ++blockX) {
            // Померај тренутног блока по X оси
            const int offsetX = blockX << 4;
            for (int y = offsetY; y < offsetY + 16 && y < nHalf; ++y) {
                for (int x = offsetX; x < offsetX + 16 && x < nHalf; ++x) {
                    const int idx1x = x;
                    const int idx1y = y;
                    const int idx2x = n - y - 1;
                    const int idx2y = x;
                    const int idx3x = n - x - 1;
                    const int idx3y = n - y - 1;
                    const int idx4x = y;
                    const int idx4y = n - x - 1;
                    const int tmp = mat[idx1y][idx1x];
                    mat[idx1y][idx1x] = mat[idx4y][idx4x];
                    mat[idx4y][idx4x] = mat[idx3y][idx3x];
                    mat[idx3y][idx3x] = mat[idx2y][idx2x];
                    mat[idx2y][idx2x] = tmp;
                }
            }
        }
    }
}

void printMatrix(int** mat, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d\t", mat[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    clock_t start = clock();
    rotateMatrixClockwiseDumb(matpp, 2048);
    clock_t end = clock();
    // printMatrix(matpp, 16);
    printf("%lf", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}
