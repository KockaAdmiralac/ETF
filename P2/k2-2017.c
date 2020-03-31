#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **podeli(char *str) {
    char *p1 = str + 1, *p2 = p1, **podela = NULL;
    int size = 0;
    while (*(p2++) != '\0') {
        if (isdigit(*p2) || (*p2) == '\0') {
            int len = p2 - p1;
            if ((*(p1 - 1) - '0') >= len) {
                podela = realloc(podela, (size + 1) * sizeof(char*));
                podela[size] = malloc((len + 1) * sizeof(char));
                memcpy(podela[size], p1, len);
                *(*(podela + size) + len) = '\0';
                ++size;
            }
            p1 = p2 + 1;
        }
    }
    podela = realloc(podela, (size + 1) * sizeof(char*));
    podela[size] = NULL;
    return podela;
}

int main() {
    char c;
    char *str;
    int size;
    while (true) {
        size = 0;
        str = NULL;
        while ((c = getchar()) != '\n') {
            str = realloc(str, (size + 1) * sizeof(char));
            str[size++] = c;
        }
        if (size == 0) {
            break;
        } else {
            char **podeljeno = podeli(str);
            int i = 0;
            while (*(podeljeno + i) != NULL) {
                printf("%s\n", *(podeljeno + i));
                free(*(podeljeno + i));
                ++i;
            }
            free(podeljeno);
            free(str);
        }
    }
    return 0;
}
