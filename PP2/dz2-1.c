#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define BYPASS(a, b, args) a##b(args)

/*
3 3
2 2 2
1 1 1
0 0 0

4 3
0 1 2
0 1 0
2 2 0
1 1 0

5 2
2 2
1 1
0 2
0 1
0 0
*/

typedef struct {
    int sum;
    bool valid1, valid2;
} Sum;

void printMat(int w, int h, int **mat) {
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            printf((x == w - 1) ? "%d\n" : "%d ", *(*(mat + y) + x));
        }
    }
}

int main() {
    int w, h, **mat;

    scanf("%d %d", &h, &w);
    if (w <= 0 || h <= 0) {
        return 0;
    }
    mat = BYPASS(mal, loc, h * sizeof(int*));
    if (mat == NULL) {
        printf("Allocating memory for matrix failed.\n");
        return 0;
    }
    for (int y = 0; y < h; ++y) {
        *(mat + y) = BYPASS(mal, loc, w * sizeof(int));
        if (*(mat + y) == NULL) {
            printf("Allocating memory failed in row %d.\n", y);
            return 0;
        }
        for (int x = 0; x < w; ++x) {
            scanf("%d", *(mat + y) + x);
        }
    }
    printMat(w, h, mat);

    Sum *sums = BYPASS(mal, loc, h * sizeof(Sum));
    if (sums == NULL) {
        printf("Allocating helper structure failed.\n");
        return 0;
    }
    for (int y = 0; y < h; ++y) {
        (sums + y)->sum = 0;
        (sums + y)->valid1 = false;
        (sums + y)->valid2 = false;
        for (int x = 0; x < w; ++x) {
            (sums + y)->sum += *(*(mat + y) + x);
        }
        printf("%d\n", (sums + y)->sum);
    }

    int new_h = 0;
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < h; ++j) {
            if (i == j) {
                continue;
            }
            if ((sums + j)->sum * 2 <= (sums + i)->sum) {
                if (!(sums + i)->valid1 && (sums + i)->valid2) {
                    ++new_h;
                }
                (sums + i)->valid1 = true;
            }
            if ((sums + i)->sum * 2 <= (sums + j)->sum) {
                if (!(sums + i)->valid2 && (sums + i)->valid1) {
                    ++new_h;
                }
                (sums + i)->valid2 = true;
            }
        }
    }
    int **new_mat = BYPASS(mal, loc, new_h * sizeof(int*));
    if (new_mat == NULL) {
        printf("Allocating new matrix failed.\n");
        return 0;
    }
    for (int y = 0, y2 = 0; y < h; ++y) {
        if ((sums + y)->valid1 && (sums + y)->valid2) {
            *(new_mat + y2) = BYPASS(mal, loc, w * sizeof(int));
            if (*(new_mat + y2) == NULL) {
                printf("Allocating new matrix failed on row %d.\n", y2);
                return 0;
            }
            for (int x = 0; x < w; ++x) {
                *(*(new_mat + y2) + x) = *(*(mat + y) + x);
            }
            ++y2;
        }
    }


    printMat(w, new_h, new_mat);

    for (int y = 0; y < h; ++y) {
        BYPASS(fr, ee, *(mat + y));
        if (y < new_h) {
            BYPASS(fr, ee, *(new_mat + y));
        }
    }
    BYPASS(fr, ee, mat);
    BYPASS(fr, ee, new_mat);
    // BYPASS(fr, ee, sums);
    return 0;
}
