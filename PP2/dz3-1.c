#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

char *readLine() {
    int length = 0;
    char input, *line = malloc(sizeof(char)), *temp;
    if (line == NULL) {
        return NULL;
    }
    *line = '\0';
    while ((input = getchar()) != '\n') {
        ++length;
        temp = realloc(line, (length + 1) * sizeof(char));
        if (temp == NULL) {
            free(line);
            return NULL;
        }
        line = temp;
        *(line + length - 1) = input;
        *(line + length) = '\0';
    }
    return line;
}

char **readLines(int *n) {
    *n = 0;
    char **lines = NULL, **temp;
    while (true) {
        char *line = readLine();
        if (line == NULL) {
            for (int i = 0; i < (*n); ++i) {
                free(*(lines + i));
            }
            if (lines != NULL) {
                free(lines);
            }
            *n = -1;
            return NULL;
        } else if (*line == '\0') {
            free(line);
            break;
        } else {
            *n += 1;
            temp = realloc(lines, (*n) * sizeof(char*));
            if (temp == NULL) {
                free(line);
                for (int i = 0; i < (*n); ++i) {
                    free(*(lines + i));
                }
                if (lines != NULL) {
                    free(lines);
                }
                *n = -1;
                return NULL;
            }
            lines = temp;
            *(lines + (*n) - 1) = line;
        }
    }
    return lines;
}

char **findAll(char *string, char *pattern, int *n) {
    int i, j, len;
    *n = 0;
    char **patterns = NULL, **tempPatterns, *tempPattern, *currPattern;
    for (i = 0; *(string + i) != '\0'; ++i) {
        currPattern = malloc(sizeof(char));
        if (currPattern == NULL) {
            for (int k = 0; k < (*n); ++k) {
                free(*(patterns + k));
            }
            if (patterns != NULL) {
                free(patterns);
            }
            *n = -1;
            return NULL;
        }
        *currPattern = '\0';
        len = 0;
        for (
            j = 0;
            *(pattern + j) != '\0' && (
                *(string + i + j) == *(pattern + j) ||
                (
                    *(pattern + j) == '%' &&
                    *(string + i + j) != '\0'
                )
            );
            ++j
        ) {
            ++len;
            tempPattern = realloc(currPattern, (len + 1) * sizeof(char));
            if (tempPattern == NULL) {
                free(currPattern);
                for (int k = 0; k < (*n); ++k) {
                    free(*(patterns + k));
                }
                if (patterns != NULL) {
                    free(patterns);
                }
                *n = -1;
                return NULL;
            }
            currPattern = tempPattern;
            *(currPattern + len - 1) = *(string + i + j);
            *(currPattern + len) = '\0';
        }
        if (*(pattern + j) == '\0') {
            *n += 1;
            tempPatterns = realloc(patterns, (*n) * sizeof(char*));
            if (tempPatterns == NULL) {
                free(currPattern);
                for (int k = 0; k < (*n); ++k) {
                    free(*(patterns + k));
                }
                if (patterns != NULL) {
                    free(patterns);
                }
                *n = -1;
                return NULL;
            }
            patterns = tempPatterns;
            *(patterns + (*n) - 1) = currPattern;
            i += j - 1;
        } else {
            free(currPattern);
        }
    }
    return patterns;
}

int main() {
    int n, m;
    char *string = readLine(),
         **patterns = readLines(&n),
         **found;
    if (string == NULL || n == -1) {
        printf("MEM_GRESKA");
    } else if (*string == '\0') {
        printf("GRESKA");
    } else {
        for (int i = 0; i < n; ++i) {
            found = findAll(string, *(patterns + i), &m);
            if (found == NULL) {
                printf("MEM_GRESKA");
                break;
            }
            for (int j = 0; j < m; ++j) {
                printf("%s\n", *(found + j));
                free(*(found + j));
            }
            free(found);
        }
    }
    if (string != NULL) {
        free(string);
    }
    if (patterns != NULL) {
        for (int i = 0; i < n; ++i) {
            free(*(patterns + i));
        }
        free(patterns);
    }
    return 0;
}
