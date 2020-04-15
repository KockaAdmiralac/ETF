#ifndef _TREE_H
#define _TREE_H
#include "util.h"

/**
 * Struktura drveta korišćena u daljoj implementaciji.
 */
typedef struct tree {
    struct tree *left, *right;
    char value;
} Tree;

Tree *getNode(char value);
void freeNode(Tree *node);

#endif
