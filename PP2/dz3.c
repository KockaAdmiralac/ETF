#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

char *readWord() {
    int length = 0;
    char *word = malloc(sizeof(char)), *tempWord, input;
    if (word == NULL) {
        printf("MEM_GRESKA");
        exit(0);
        return NULL;
    }
    *word = '\0';
    while (true) {
        input = getchar();
        if (input == '\n' || input == ' ') {
            break;
        }
        *(word + length) = input;
        ++length;
        tempWord = realloc(word, (length + 1) * sizeof(char));
        if (tempWord == NULL) {
            free(word);
            return NULL;
        }
        word = tempWord;
        *(word + length) = '\0';
    }
    return word;
}

char **readWords(int *n) {
    *n = 0;
    char **words = NULL, **tempWords;
    while (true) {
        char *newWord = readWord();
        if (newWord == NULL) {
            if (words != NULL) {
                for (int i = 0; i < (*n); ++i) {
                    free(*(words + i));
                }
                free(words);
            }
            printf("MEM_GRESKA");
            exit(0);
            return NULL;
        } else if (*newWord == '\0') {
            free(newWord);
            return words;
        } else {
            *n += 1;
            tempWords = realloc(words, (*n) * sizeof(char*));
            if (tempWords == NULL) {
                if (words != NULL) {
                    for (int i = 0; i < (*n); ++i) {
                        free(*(words + i));
                    }
                    free(words);
                }
                free(newWord);
                printf("MEM_GRESKA");
                exit(0);
                return NULL;
            }
            words = tempWords;
            *(words + (*n) - 1) = newWord;
        }
    }
}

void rotateSentence(char **sentence, int n, int rotate) {
    rotate = rotate % n;
    if (rotate < 0) {
        rotate += n;
    }
    char *prev, *temp;
    for (int i = 0; i < rotate; ++i) {
        prev = *(sentence + n - 1);
        for (int j = 0; j < n; ++j) {
            temp = *(sentence + j);
            *(sentence + j) = prev;
            prev = temp;
        }
    }
}

int main() {
    int n, rotate;
    char **words = readWords(&n);
    scanf("%d", &rotate);
    if (n == 0) {
        printf("GRESKA");
        return 0;
    }
    rotateSentence(words, n, rotate);
    for (int i = 0; i < n; ++i) {
        printf("%s", *(words + i));
        if (i != n - 1) {
            printf(" ");
        }
        free(*(words + i));
    }
    free(words);
    return 0;
}
