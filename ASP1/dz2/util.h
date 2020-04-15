#ifndef _UTIL_H
#define _UTIL_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define VT100_ESCAPE 27

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

#endif
