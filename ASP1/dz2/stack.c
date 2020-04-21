#include "stack.h"

/**
 * Guranje čvora stabla na stek.
 * @param {NodeTree**} stack Stek na koji se gura čvor
 * @param {Tree*} value Čvor stabla koji se gura
 * @returns {Result} Uspešnost operacije
 */
Result treeStackPush(NodeTree **stack, Tree *value) {
    if (stack == NULL) {
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
 * Izbacivanje poslednjeg čvora stabla sa steka.
 * @param {NodeTree**} stack Stek sa kojeg se izbacuje čvor stabla
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
 * @param {NodeOperator**} stack Stek na koji se gura operator
 * @param {char} value Oznaka operatora koji se gura
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
 * Izbacivanje poslednjeg operatora sa steka.
 * @param {NodeOperator**} stack Stek sa kojeg se izbacuje operator
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

/**
 * Guranje operanda na stek.
 * @param {NodeOperand**} stack Stek na koji se gura operand
 * @param {double} value Vrednost operanda koja se gura
 * @returns {Result} Uspešnost operacije
 */
Result operandStackPush(NodeOperand **stack, double value) {
    if (stack == NULL) {
        return OOPS;
    }
    NodeOperand *newNode = malloc(sizeof(NodeOperand));
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
 * Izbacivanje poslednjeg operanda sa steka.
 * @param {NodeOperand**} stack Stek sa kojeg se izbacuje operand
 * @returns {double} Poslednji operand sa steka, ili -1 ako se desila greška
 */
double operandStackPop(NodeOperand **stack) {
    if (stack == NULL || *stack == NULL) {
        return -1;
    }
    NodeOperand *stackTop = *stack;
    double returnValue = stackTop->value;
    *stack = (*stack)->next;
    free(stackTop);
    return returnValue;
}
