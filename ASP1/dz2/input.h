#ifndef _INPUT_H
#define _INPUT_H
#include "stack.h"
#include "tree.h"
#include "util.h"

/**
 * Mogući tipovi sintakse u izrazu.
 */
typedef enum {
    OPERATOR,
    OPERAND,
    FUNCTION,
    LEFT_BRACE,
    RIGHT_BRACE,
    SPACE,
    ARGUMENT_SEPARATOR,
    UNKNOWN
} Token;

Tree *inputExpression();
#endif
