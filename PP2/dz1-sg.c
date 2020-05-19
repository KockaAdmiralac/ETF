#include <stdio.h>
#include <stdlib.h>
#define MAX_N 10007

/*
Iz zadatka
4
0 5 1
1 7 2
4 4 1
7 15 1

Maksimum unazad
4
0 5 1
1 7 2
4 4 1
7 15 2

Jedan element
1
100 5 1

Nedostižno
3
1 100 1
50 200 1
100 100 1

Ogromna energija u sredini
5
0 100 1
50 100 1
100 1 10000
150 100 1
200 100 1

Ogromno zlato u sredini
4
0 1 1
25 10000 75
175 10000 75
200 1 1
*/

typedef struct {
    long long x, g, d;
} Mine;

Mine mines[MAX_N];

int cmpLower(const void *va, const void *vb) {
    Mine *a = (Mine*) va;
    Mine *b = (Mine*) vb;
    return (a->x - a->d) - (b->x - b->d);
}

int cmpUpper(const void *va, const void *vb) {
    Mine *a = (Mine*) va;
    Mine *b = (Mine*) vb;
    return (b->x + b->d) - (a->x + a->d);
}

int main() {
    long long n;
    scanf("%lld", &n);
    for (long long i = 0; i < n; ++i) {
        scanf("%lld %lld %lld", &mines[i].x, &mines[i].g, &mines[i].d);
    }
    long long firstX = mines[0].x,
              lastX = mines[n-1].x;
    qsort(mines, n, sizeof(Mine), cmpLower);
    long long energy = mines[0].d - (mines[0].x - firstX),
              gold = mines[0].g,
              maxGold = mines[0].g,
              first = firstX,
              last = mines[0].x;
    for (long long i = 1; i < n; ++i) {
        energy += mines[i].d;
        gold += mines[i].g;
        if (last < mines[i].x) {
            energy -= mines[i].x - last;
            last = mines[i].x;
        }
        if (energy < 0) {
            // Reset
            if (mines[i].x - mines[i-1].x <= mines[i].d + mines[i-1].d) {
                --i;
            }
            energy = mines[i].d;
            gold = mines[i].g;
            first = mines[i].x;
            last = first;
        }
        if (maxGold < gold) {
            maxGold = gold;
        }
    }
    qsort(mines, n, sizeof(Mine), cmpUpper);
    energy = mines[0].d - (lastX - mines[0].x);
    gold = mines[0].g;
    first = mines[0].x;
    last = lastX;
    for (long long i = 1; i < n; ++i) {
        energy += mines[i].d;
        gold += mines[i].g;
        if (mines[i].x < first) {
            energy -= first - mines[i].x;
            first = mines[i].x;
        }
        if (energy < 0) {
            // Reset
            if (mines[i-1].x - mines[i].x <= mines[i].d + mines[i-1].d) {
                --i;
            }
            energy = mines[i].d;
            gold = mines[i].g;
            last = mines[i].x;
            first = last;
        }
        if (maxGold < gold) {
            maxGold = gold;
        }
    }
    printf("%lld\n", maxGold);
    return 0;
}
