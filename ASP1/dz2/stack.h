#ifndef _STACK_H
#define _STACK_H
#include "tree.h"
#include "util.h"

/**
 * Struktura čvora steka korišćena u implementaciji.
 */
typedef struct node_tree {
    struct node_tree *next;
    Tree *value;
} NodeTree;

/**
 * Struktura čvora steka korišćena u implementaciji.
 */
typedef struct node_operator {
    struct node_operator *next;
    char value;
} NodeOperator;

Result treeStackPush(NodeTree **stack, Tree *value);
Tree *treeStackPop(NodeTree **stack);
Result operatorStackPush(NodeOperator **stack, char value);
char operatorStackPop(NodeOperator **stack);

#endif
