#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **loadMap(int rows)  {
    char **map = malloc(sizeof(char*) * rows);
    for (int i = 0; i < rows; ++i) {
        *(map + i) = malloc(sizeof(char) * 2);
        scanf(" %c %c", *(map + i), (*(map + i) + 1));
    }
    return map;
}

int charToDigit(char c, char **map, int rows) {
    for (int i = 0; i < rows; ++i) {
        if (*(*(map + i)) == c) {
            return *(*(map + i) + 1) - '0';
        }
    }
    return 0;
}

int stringToInt(char *word, char **map, int rows) {
    char *c = word;
    int number = 0;
    while (*c != '\0') {
        number *= 10;
        number += charToDigit(*c, map, rows);
        c++;
    }
    return number;
}

char *readLine() {
    char *line = NULL;
    int size = 0;
    char next = getchar();
    while (next != '\n') {
        line = realloc(line, (size + 1) * sizeof(char));
        *(line + (size++)) = next;
        next = getchar();
    }
    line = realloc(line, (size + 1) * sizeof(char));
    line[size] = '\0';
    return line;
}

int main() {
    int N;
    scanf("%d", &N);
    char **map = loadMap(N);
    getchar();
    char *word1 = readLine(),
         *word2 = readLine(),
         *word3 = readLine();
    if (stringToInt(word1, map, N) + stringToInt(word2, map, N) == stringToInt(word3, map, N)) {
        printf("DA\n");
    } else {
        printf("NE\n");
    }
    for (int i = 0; i < N; ++i) {
        free(*(map + i));
    }
    free(map);
    free(word1);
    free(word2);
    free(word3);
    return 0;
}
