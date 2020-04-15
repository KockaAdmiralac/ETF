#include "stack.h"

/**
 * Guranje čvora drveta na stek.
 * @param {Node**} stack Stek na koji se gura čvor
 * @param {Tree*} value Čvor drveta koji se gura
 * @returns {Result} Uspešnost operacije
 */
Result treeStackPush(NodeTree **stack, Tree *value) {
    if (stack == NULL || value == NULL) {
        return OOPS;
    }
    NodeTree *newNode = malloc(sizeof(NodeTree));
    if (newNode == NULL) {
        return OOM;
    }
    newNode->value = value;
    if ((*stack) == NULL) {
        *stack = newNode;
        (*stack)->next = NULL;
    } else {
        newNode->next = *stack;
        *stack = newNode;
    }
    return OK;
}

/**
 * Izbacivanje poslednjeg čvora sa steka.
 * @param {Node**} stack Stek sa kojeg se izbacuje čvor
 * @returns {Tree*} Poslednji čvor sa steka, ili NULL ako se desila greška
 */
Tree *treeStackPop(NodeTree **stack) {
    if (stack == NULL || *stack == NULL) {
        return NULL;
    }
    NodeTree *stackTop = *stack;
    Tree *returnValue = stackTop->value;
    *stack = (*stack)->next;
    free(stackTop);
    return returnValue;
}

/**
 * Guranje operatora na stek.
 * @param {Node**} stack Stek na koji se gura čvor
 * @param {char} value Čvor drveta koji se gura
 * @returns {Result} Uspešnost operacije
 */
Result operatorStackPush(NodeOperator **stack, char value) {
    if (stack == NULL) {
        return OOPS;
    }
    NodeOperator *newNode = malloc(sizeof(NodeOperator));
    if (newNode == NULL) {
        return OOM;
    }
    newNode->value = value;
    if ((*stack) == NULL) {
        *stack = newNode;
        (*stack)->next = NULL;
    } else {
        newNode->next = *stack;
        *stack = newNode;
    }
    return OK;
}

/**
 * Izbacivanje poslednji operator sa steka.
 * @param {Node**} stack Stek sa kojeg se izbacuje čvor
 * @returns {char} Poslednji operator sa steka, ili \0 ako se desila greška
 */
char operatorStackPop(NodeOperator **stack) {
    if (stack == NULL || *stack == NULL) {
        return '\0';
    }
    NodeOperator *stackTop = *stack;
    char returnValue = stackTop->value;
    *stack = (*stack)->next;
    free(stackTop);
    return returnValue;
}
