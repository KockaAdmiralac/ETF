#include "util.h"

/**
 * Čišćenje ekrana realizovano korišćenjem VT100 komandi.
 * @see https://www.csie.ntu.edu.tw/~r92094/c++/VT100.html
 */
void clear() {
    #ifndef DEBUG
    printf("%c[2J%c[f", VT100_ESCAPE, VT100_ESCAPE);
    #endif
}

/**
 * Read a dynamically allocated string from standard input, terminated by a
 * newline.
 * @returns {char*} Dynamically allocated string, or NULL if allocation failed
 */
char *readString() {
    int length = 0;
    int capacity = 1;
    char c;
    char *str = NULL, *tmp;
    while ((c = getchar()) != '\n') {
        ++length;
        if (length == capacity) {
            capacity *= 2;
            tmp = realloc(str, capacity * sizeof(char));
            if (tmp == NULL) {
                free(str);
                return NULL;
            }
            str = tmp;
        }
        *(str + length - 1) = c;
    }
    tmp = realloc(str, (length + 1) * sizeof(char));
    if (tmp == NULL) {
        free(str);
        return NULL;
    }
    str = tmp;
    *(str + length) = '\0';
    return str;
}
