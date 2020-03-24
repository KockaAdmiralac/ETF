#include <stdio.h>
#define COUNTING 100007

int main() {
    int N, A[1007], max[3], counting[COUNTING], shift, novi[1007], length, t;
    scanf("%d", &N);
    while (N > 2) {
        shift = 0;
        for (int i = 0; i < 3; ++i) {
            max[i] = -1;
        }
        length = 0;
        for (int i = 0; i < COUNTING; ++i) {
            counting[i] = 0;
        }
        for (int i = 0; i < N; ++i) {
            scanf("%d", &A[i]);
            if (counting[A[i]] == 0) {
                counting[A[i]] = 1;
                novi[length++] = A[i];
            }
        }
        for (int i = 0; i < N; ++i) {
            printf("%d ", A[i]);
        }
        printf("\n");
        for (int i = 0; i < length; ++i) {
            printf("%d ", novi[i]);
        }
        for (int i = 0; i < length; ++i) {
            t = -1;
            for (int j = 0; j < 3; ++j) {
                if (novi[i] > max[j]) {
                    t = j;
                } else {
                    break;
                }
            }
            if (t != -1) {
                for (int j = t-1; j >= 0; --j) {
                    max[j] = max[j+1];
                }
                max[t] = novi[i];
            }
        }
        for (int i = 0; i < 3; ++i) {
            printf("%d\n", max[i]);
        }
        for (int i = 2; i >= 0; --i) {
            if (max[i] == -1 || i != 2 && max[i] == max[i+1]) {
                printf("\nx");
            } else {
                printf("\n%d", max[i]);
            }
        }
        scanf("%d", &N);
    }
    return 0;
}
