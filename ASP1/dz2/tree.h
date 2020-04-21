#ifndef _TREE_H
#define _TREE_H
#include "util.h"

/**
 * Struktura stabla korišćena u daljoj implementaciji.
 */
typedef struct tree {
    struct tree *left, *right, *original;
    char value;
} Tree;

/**
 * Struktura čvora ulančane liste za čuvanje stabala.
 */
typedef struct tree_list {
    struct tree_list *next;
    char *label;
    Tree *tree;
} TreeList;

Tree *getNode(char value);
Result freeTree(Tree *tree);
Result freeTrees(TreeList *trees);
Tree *copyTree(Tree *original);
Result addTree(TreeList **trees, Tree *tree, char *label);
bool containsNode(Tree *tree, char node);

#include "stack.h"
#endif
