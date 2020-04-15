#include "input.h"

/**
 * Vraća tip sintakse nekog karaktera.
 */
Token getToken(char input) {
    switch (input) {
        case ' ': return SPACE;
        case '(': return LEFT_BRACE;
        case ')': return RIGHT_BRACE;
        case ',': return ARGUMENT_SEPARATOR;
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
        // Specijalni karakter za unarni minus.
        case '_':
            return OPERATOR;
        default:
            if (input >= 'A' && input <= 'Z') {
                return OPERATOR;
            }
            if (input >= 'a' && input <= 'z') {
                return FUNCTION;
            }
            return UNKNOWN;
    }
}

/**
 * Dobavljanje ulaznog prioriteta operatora.
 * @param {char} operator Operator za koji se proverava ulazni prioritet
 * @returns {int} Ulazni prioritet operatora
 */
int getInputPriority(char operator) {
    switch (operator) {
        case ')':
            return 1;
        case '+':
        case '-':
            return 2;
        case '*':
        case '/':
            return 3;
        case '^':
            return 5;
        case 'l':
        case 't':
        case 'm':
            return 6;
        case ',':
        case '(':
            return 7;
        default:
            return -1;
    }
}

/**
 * Dobavljanje stek prioriteta operatora.
 * @param {char} operator Operator za koji se proverava stek prioritet
 * @returns {int} Stek prioritet operatora
 */
int getStackPriority(char operator) {
    switch (operator) {
        case '(': return 0;
        case '^': return 4;
        default: return getInputPriority(operator);
    }
}

/**
 * Unos izraza i pretvaranje u stablo.
 * Po propozicijama zadatka, smatra se da je uneti izraz validan.
 * Podržane funkcije su prirodni logaritam, tangens i minimum sa dva parametra.
 * @returns {Tree*} Napravljeno drvo, ili NULL ako se desila greška.
 */
Tree *inputExpression() {
    char c, prev = '\0';
    Token token, prevToken = UNKNOWN;
    NodeTree *treeStack = NULL;
    NodeOperator *operatorStack = NULL;
    while ((c = getchar()) != '\n') {
        token = getToken(c);
        switch (token) {
            case OPERAND:
                treeStackPush(&treeStack, getNode(c));
                break;
            case OPERATOR:
                if (prev == '(' && c == '-') {
                    // Unarno minus.s
                    c = '_';
                }
                while (getInputPriority(c) <= getStackPriority(operatorStack->value)) {
                    // 
                }
                operatorStackPush(&operatorStack, c);
                break;
            case FUNCTION:
                // Funkcije identifikujemo po njihovom prvom karakteru
                // ln -> l, tg -> t, min -> m
                // i stoga preskačemo sve dalje karaktere u imenu funkcije
                if (prevToken == FUNCTION) {
                    continue;
                }
                break;
            case LEFT_BRACE:
                if (prevToken == FUNCTION) {
                    // Pozivamo funkciju.
                    operatorStackPush(&operatorStack, prev);
                } else {
                    operatorStackPush(&operatorStack, '(');
                }
                break;
            case RIGHT_BRACE:
            case ARGUMENT_SEPARATOR:
                break;
            case SPACE:
                // Namerno ne postavljamo prethodni karakter.
                continue;
            case UNKNOWN:
            default:
                printf("%c nije validan karakter.\n", c);
                return NULL;
        }
        prev = c;
        prevToken = token;
    }
    return NULL;
}
