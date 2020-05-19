#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long g, d;
} Cow;

Cow cows[10007];
bool time[10007] = {false};

int cmp(const void *va, const void *vb) {
    Cow *a = (Cow*) va;
    Cow *b = (Cow*) vb;
    return b->g - a->g;
}

int main() {
    long long n, i, j, gold = 0;
    scanf("%lld", &n);
    for (i = 0; i < n; ++i) {
        scanf("%lld %lld", &cows[i].g, &cows[i].d);
    }
    qsort(cows, n, sizeof(Cow), cmp);
    for (i = 0; i < n; ++i) {
        for (j = cows[i].d; j > 0; --j) {
            if (!time[j]) {
                time[j] = true;
                gold += cows[i].g;
                break;
            }
        }
    }
    printf("%lld\n", gold);
    return 0;
}
