#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_N 5007

/*
8
1 2 -2 -3 5 -7 -8 10

8
1 2 -2 -3 5 -7 -8 -1

12
-1 7 -5 8 -8 2 4 -5 -4 5 6 -6

2
1 -1
*/

int a[MAX_N], max[MAX_N];

bool canCross(int from, int to) {
    return ((a[from] < 0) != (a[to] < 0)) && abs(a[from]) < abs(a[to]);
}

int main() {
    int n, i, j, maxAll = 1;
    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    max[0] = 1;
    for (i = 1; i < n; ++i) {
        max[i] = 1;
        for (j = i-1; j >= 0; --j) {
            if (canCross(j, i) && max[j] + 1 > max[i]) {
                max[i] = max[j] + 1;
            }
        }
        if (max[i] > maxAll) {
            maxAll = max[i];
        }
    }
    printf("%d\n", maxAll);
    return 0;
}
