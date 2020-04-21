#ifndef _STACK_H
#define _STACK_H
#include "tree.h"
#include "util.h"

/**
 * Struktura čvora steka korišćena u implementaciji steka čvorova stabla.
 */
typedef struct node_tree {
    struct node_tree *next;
    Tree *value;
} NodeTree;

/**
 * Struktura čvora steka korišćena u implementaciji operatorskog steka.
 */
typedef struct node_operator {
    struct node_operator *next;
    char value;
} NodeOperator;

/**
 * Struktura čvora steka korišćena u implementaciji operandskog steka.
 */
typedef struct node_operand {
    struct node_operand *next;
    double value;
} NodeOperand;

Result treeStackPush(NodeTree **stack, Tree *value);
Tree *treeStackPop(NodeTree **stack);
Result operatorStackPush(NodeOperator **stack, char value);
char operatorStackPop(NodeOperator **stack);
Result operandStackPush(NodeOperand **stack, double value);
double operandStackPop(NodeOperand **stack);

#endif
