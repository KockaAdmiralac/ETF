#include <stdbool.h>
#include <stdio.h>
#define MAX_BR_EL 10007

/*
5
1 0 1 0 1
2
---
1 0 1 0 1
1 0 1 0 1
1 1 1 0 1
-3

8
2 0 2 2 3 1 1 1
1
---
2 0 2 2 3 1 1 1
0 1 1 1
0 0 1 1
3

6
0 4 0 1 0 1
-1
---
0 4 0 1 0 1
0 0 1 0 1
0 1 0 1 0
10
*/

void printArray(int array[MAX_BR_EL], int n) {
    for (int i = 0; i < n; ++i) {
        printf((i == n - 1) ? "%d" : "%d ", array[i]);
    }
    printf("\n");
}

int main() {
    int n, t, final = 0;
    int niz[MAX_BR_EL];
    bool invert = false;
    // Program treba da:
    // 1) Učita dužinu niza, a zatim u novom redu i niz celih brojeva tipa int.
    scanf("%d", &n);
    if (n < 1 || n > MAX_BR_EL) {
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        scanf("%d", &niz[i]);
    }
    // 2) Ispiše učitani niz. Svaki element treba da bude razdvojen tačno
    // jednim blanko znakom. Nakon poslednjeg elementa ne treba da se ispiše
    // blanko znak.
    printArray(niz, n);
    // 3) Ukoloni[sic] iz niza sve elemente koji su različiti od 0 i 1 i ispiše
    // rezultujući niz na prethodno opisani način. Ukoliko rezultujući niz
    // ostane prazan, prekinuti dalju obradu.
    t = 0;
    for (int i = 0; i < n; ++i) {
        niz[t] = niz[i];
        if (niz[i] == 0 || niz[i] == 1) {
            ++t;
        }
    }
    if (t <= 0 || t > 32) {
        return 0;
    }
    n = t;
    printArray(niz, n);
    // 4) Učitava pomeraj i izvrši aritemtičko pomeranje niza binarnih
    // cifara za zadati broj mesta ulevo ili udesno i ispiše rezultujući niz
    // na prethodno opisani način. Negativan pomeraj označava pomeranje ulevo,
    // a pozitivan pomeraj označava pomeraj udesno.
    scanf("%d", &t);
    if (t < 0) {
        for (int i = 0; i < n + t; ++i) {
            niz[i] = niz[i - t];
        }
        for (int i = n + t; i < n; ++i) {
            niz[i] = 0;
        }
    } else if (t > 0) {
        for (int i = n - 1; i >= t; --i) {
            niz[i] = niz[i - t];
        }
        for (int i = 1; i < t; ++i) {
            niz[i] = niz[0];
        }
    }
    printArray(niz, n);
    // 5) Izračuna i ispiše vrednost tako dobijenog broja kao označenog celog
    // broja na onoliko bitova koliko iznosi dužina niza nakon uklanjanja
    // elemenata.
    t = 1;
    for (int i = n - 1; i > 0; --i) {
        if (niz[i] == 1) {
            if (niz[0] == 1) {
                if (!invert) {
                    invert = true;
                    final += t;
                }
            } else {
                final += t;
            }
        } else if (niz[0] == 1 && invert) {
            final += t;
        }
        t *= 2;
    }
    if (niz[0] == 1) {
        final = -final;
    }
    printf("%d\n", final);
    return 0;
}
