#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **ukrsteneReci(int *m, int *n) {
    char **matrica = malloc(sizeof(char*) * (*n)),
         word[11];
    int x, y;
    bool moze = true;
    if (matrica == NULL) {
        exit(1);
    }
    for (int i = 0; i < (*n); ++i) {
        *(matrica + i) = malloc(sizeof(char) * (*m));
        if (*(matrica + i) == NULL) {
            exit(1);
        }
        for (int j = 0; j < (*m); ++j) {
            if (i == (*n) - 1 || j == (*m) - 1) {
                *(*(matrica + i) + j) = '\0';
            } else {
                *(*(matrica + i) + j) = '#';
            }
        }
    }
    scanf("%s %d %d", word, &y, &x);
    while (x >= 0 && x < (*m) - 1 && y >= 0 && y < (*n) - 1) {
        int len = strlen(word);
        if (x + len >= (*m)) {
            scanf("%s %d %d", word, &y, &x);
            continue;
        }
        moze = true;
        for (int i = 0; i < len; ++i) {
            if (*(*(matrica + y) + x + i) != '#') {
                moze = false;
                break;
            }
        }
        if (moze) {
            for (int i = 0; i < len; ++i) {
                *(*(matrica + y) + x + i) = word[i];
            }
        }
        scanf("%s %d %d", word, &y, &x);
    }
    return matrica;
}

int main() {
    int m, n;
    scanf("%d %d", &n, &m);
    char **matrica = ukrsteneReci(&m, &n);
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < m - 1; ++j) {
            printf("%c", *(*(matrica + i) + j));
        }
        printf("\n");
    }
    for (int j = 0; j < m - 1; ++j) {
        for (int i = 0; i < n - 1; ++i) {
            printf("%c", *(*(matrica + i) + j));
        }
        printf("\n");
    }
    for (int i = 0; i < n; ++i) {
        free(*(matrica + i));
    }
    free(matrica);
    return 0;
}
