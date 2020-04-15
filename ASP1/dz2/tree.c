#include "tree.h"

/**
 * Alocira novi čvor drveta.
 * @param {double} value Početna vrednost čvora
 * @returns {Tree*} Novonapravljeni čvor
 */
Tree *getNode(char value) {
    Tree *node = malloc(sizeof(Tree));
    if (node == NULL) {
        return NULL;
    }
    node->left = NULL;
    node->right = NULL;
    node->value = value;
    return node;
}

/**
 * Oslobađa čvor drveta.
 * @param {Tree*} Čvor drveta za oslobađanje
 */
void freeNode(Tree *node) {
    free(node);
}
