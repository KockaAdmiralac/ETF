#ifndef _INPUT_H
#define _INPUT_H
#include "stack.h"
#include "tree.h"
#include "util.h"

/**
 * Mogući tipovi sintakse u izrazu.
 */
typedef enum {
    // Jedan od podržanih znakova po propozicijama zadatka.
    OPERATOR,
    // Veliko slovo u nazivu operanda.
    OPERAND,
    // Malo slovo u nazivu funkcije. Na steku isključivo prvo slovo.
    FUNCTION,
    // Otvorena zagrada. Na steku isključivo van konteksta funkcije.
    LEFT_BRACE,
    // Zatvorena zagrada, bilo u kontekstu funkcije ili ne.
    RIGHT_BRACE,
    // Razmaci koji se ignorišu.
    SPACE,
    // Zarez koji razdvaja argumente funkcije.
    ARGUMENT_SEPARATOR,
    // Cifra 0 ili 1, isključivo u nepojednostavljenom stablu.
    CONSTANT,
    // Korisnik je uneo glupost.
    UNKNOWN
} Token;

Tree *inputExpression(InputVariable variables[26]);
#endif
