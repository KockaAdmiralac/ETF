#include "input.h"

/**
 * Vraća tip sintakse nekog karaktera.
 * @param {char} input Karakter čiji se tip sintakse proverava
 * @returns {Token} Tip sintakse karaktera
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
        // Podržane su samo konstante 0 i 1 i to isključivo prilikom
        // pojednostabljenja.
        case '0':
        case '1':
            return CONSTANT;
        default:
            if (input >= 'A' && input <= 'Z') {
                return OPERAND;
            }
            if (input >= '0' && input <= '9') {
                return CONSTANT;
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
int inputPriority(char operator) {
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
        case 's':
        case 'c':
        case '_':
        case ',':
        case '(':
            return 6;
        default:
            return -1;
    }
}

/**
 * Dobavljanje stek prioriteta operatora.
 * @param {char} operator Operator za koji se proverava stek prioritet
 * @returns {int} Stek prioritet operatora
 */
int stackPriority(char operator) {
    switch (operator) {
        case '(':
        case 'l':
        case 't':
        case 'm':
        case 's':
        case 'c':
        case '_':
            return 0;
        case '^':
            return 4;
        default:
            return inputPriority(operator);
    }
}

/**
 * Prebacivanje operatora sa steka operatora u stablo.
 * @param {NodeTree**} treeStack Pokazivač na stek iz kojeg se formira stablo
 * @param {NodeOperator**} operatorStack Pokazivač na stek operatora
 * @returns {Result} Uspešnost operacije
 */
Result moveLastOperator(NodeTree **treeStack, NodeOperator **operatorStack) {
    char operator = operatorStackPop(operatorStack);
    Tree *newNode = getNode(operator);
    switch (operator) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
        case 'm':
            newNode->right = treeStackPop(treeStack);
            newNode->left = treeStackPop(treeStack);
            break;
        case '_':
        case 'l':
        case 't':
        case 's':
        case 'c':
            newNode->left = treeStackPop(treeStack);
            break;
        default:
            // Uhh nešto smo zeznuli.
            return OOPS;
    }
    treeStackPush(treeStack, newNode);
    return OK;
}

/**
 * Unos izraza i pretvaranje u stablo.
 * Po propozicijama zadatka, smatra se da je uneti izraz validan.
 * Podržane funkcije su prirodni logaritam (ln), tangens (tg/tan), minimum sa
 * dva parametra (min), sinus (sin) i kosinus (cos).
 * @param {InputVariable[]} variables Podaci o svim mogućim promenljivama
 * @returns {Tree*} Napravljeno stablo, ili NULL ako se desila greška.
 */
Tree *inputExpression(InputVariable variables[26]) {
    char c, prev = '\0';
    Token token, prevToken = UNKNOWN, tempToken;
    NodeTree *treeStack = NULL;
    NodeOperator *operatorStack = NULL;
    Tree *returnValue;
    printf("Unesite izraz: ");
    while ((c = getchar()) != '\n') {
        token = getToken(c);
        switch (token) {
            case OPERAND:
                treeStackPush(&treeStack, getNode(c));
                variables[c - 'A'].present = true;
                break;
            case OPERATOR:
                if (prev == '(' && c == '-') {
                    // Unarno minus.
                    c = '_';
                }
                while (
                    operatorStack != NULL &&
                    inputPriority(c) <= stackPriority(operatorStack->value)
                ) {
                    moveLastOperator(&treeStack, &operatorStack);
                }
                operatorStackPush(&operatorStack, c);
                break;
            case FUNCTION:
                // Funkcije identifikujemo po njihovom prvom karakteru
                // ln -> l, tg -> t, min -> m, s -> sin, c -> cos
                // i stoga preskačemo sve dalje karaktere u imenu funkcije
                if (prevToken == FUNCTION) {
                    continue;
                }
                break;
            case LEFT_BRACE:
                if (prevToken == FUNCTION) {
                    operatorStackPush(&operatorStack, prev);
                } else {
                    operatorStackPush(&operatorStack, '(');
                }
                break;
            case RIGHT_BRACE:
                while (operatorStack != NULL) {
                    tempToken = getToken(operatorStack->value);
                    if (tempToken == FUNCTION || tempToken == LEFT_BRACE) {
                        break;
                    }
                    moveLastOperator(&treeStack, &operatorStack);
                }
                if (tempToken == FUNCTION) {
                    moveLastOperator(&treeStack, &operatorStack);
                } else {
                    operatorStackPop(&operatorStack);
                }
                break;
            case ARGUMENT_SEPARATOR:
                while (
                    operatorStack != NULL &&
                    getToken(operatorStack->value) != FUNCTION
                ) {
                    moveLastOperator(&treeStack, &operatorStack);
                }
                break;
            case SPACE:
                // Namerno ne postavljamo prethodni karakter.
                continue;
            case CONSTANT:
            case UNKNOWN:
            default:
                printf("%c nije validan karakter.\n", c);
                while (treeStack != NULL) {
                    treeStackPop(&treeStack);
                }
                while (operatorStack != NULL) {
                    operatorStackPop(&operatorStack);
                }
                return NULL;
        }
        prev = c;
        prevToken = token;
    }
    while (operatorStack != NULL) {
        moveLastOperator(&treeStack, &operatorStack);
    }
    returnValue = treeStackPop(&treeStack);
    if (treeStack != NULL) {
        printf(
            "Desila se nepoznata greška prilikom parsiranja izraza. Proverite "
            "da li je uneseni izraz ispravan po propozicijama zadatka.\n"
        );
        while (treeStack != NULL) {
            treeStackPop(&treeStack);
        }
        return NULL;
    }
    return returnValue;
}
