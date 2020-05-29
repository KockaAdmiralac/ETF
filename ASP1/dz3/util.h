#ifndef _UTIL_H
#define _UTIL_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define VT100_ESCAPE 27
// Isključuje funkcionalnost čišćenja ekrana.
// #define DEBUG

/**
 * Mogući rezultati operacija u programu.
 */
typedef enum {
    // Operacija uspešna.
    OK,
    // Ponestalo je memorije tokom operacije.
    OOM,
    // Greška je do programera.
    OOPS,
    // Greška je do korisnika.
    RTFM
} Result;

void clear();
char *readString();

#endif
