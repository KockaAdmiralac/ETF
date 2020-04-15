#include <stdio.h>
#include <stdlib.h>

/*
3 3
1 2 3 4 5 6 7 8 9

3 4
5 7 11 9
4 3 1 15
2 1 8 2

3 5
-2 7 1 5 6 4 -2 6 1 7 8 2 0 4 -2
*/

void printMat(int w, int h, int **mat) {
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            printf((x == w - 1) ? "%d\n" : "%d ", *(*(mat + x) + y));
        }
    }
}

int main() {
    int w, h;

    scanf("%d %d", &h, &w);
    if (w <= 0 || h <= 0) {
        return 0;
    }
    int **const mat = malloc(w * sizeof(int*));
    if (mat == NULL) {
        printf("Allocating memory for matrix failed.\n");
        return 0;
    }
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            if (y == 0) {
                *(mat + x) = malloc(h * sizeof(int));
                if (*(mat + x) == NULL) {
                    printf("Allocating memory failed in row %d.\n", y);
                    return 0;
                }
            }
            scanf("%d", *(mat + x) + y);
        }
    }
    printMat(w, h, mat);

    int *mins = malloc(w * sizeof(int));
    double sum_mins = 0;
    if (mins == NULL) {
        return 0;
    }
    for (int x = 0; x < w; ++x) {
        *(mins + x) = **(mat + x);
        for (int y = 1; y < h; ++y) {
            if (*(*(mat + x) + y) < *(mins + x)) {
                *(mins + x) = *(*(mat + x) + y);
            }
        }
        printf("%d\n", *(mins + x));
        sum_mins += *(mins + x);
    }

    double mid = sum_mins / w;
    printf("%.2lf\n", mid);

    int tail = 0, new_w = w;
    for (int head = 0; head < w; ++head) {
        if (*(mins + head) > mid) {
            free(*(mat + head));
            --new_w;
        } else {
            *(mat + tail) = *(mat + head);
            ++tail;
        }
    }
    w = new_w;

    printMat(w, h, mat);

    for (int x = 0; x < w; ++x) {
        free(*(mat + x));
    }
    free(mat);
    free(mins);
    return 0;
}
