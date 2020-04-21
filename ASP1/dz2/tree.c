#include "tree.h"

/**
 * Alocira novi čvor stabla.
 * @param {char} value Početna vrednost čvora
 * @returns {Tree*} Novonapravljeni čvor
 */
Tree *getNode(char value) {
    Tree *node = malloc(sizeof(Tree));
    if (node == NULL) {
        return NULL;
    }
    node->left = NULL;
    node->right = NULL;
    node->original = NULL;
    node->value = value;
    return node;
}

/**
 * Dealocira celo stablo iz memorije.
 * @param {Tree*} tree Stablo za dealokaciju
 * @returns {Result} Rezultat operacije
 */
Result freeTree(Tree *tree) {
    if (tree == NULL) {
        return OOPS;
    }
    NodeTree *stack = NULL;
    Tree *currentTree;
    treeStackPush(&stack, tree);
    while (stack != NULL) {
        currentTree = treeStackPop(&stack);
        if (currentTree->left != NULL) {
            treeStackPush(&stack, currentTree->left);
        }
        if (currentTree->right != NULL) {
            treeStackPush(&stack, currentTree->right);
        }
        free(currentTree);
    }
    return OK;
}

/**
 * Oslobađa sva stabla iz memorije.
 * @param {Tree*} Stabla za oslobađanje
 * @returns {Result} Rezultat operacije
 */
Result freeTrees(TreeList *trees) {
    if (trees == NULL) {
        return OOPS;
    }
    TreeList *head = trees->next,
             *treeNode = head,
             *tmp;
    do {
        tmp = treeNode->next;
        freeTree(treeNode->tree);
        free(treeNode->label);
        free(treeNode);
        treeNode = tmp;
    } while (treeNode != head);
    return OK;
}

/**
 * Kopira jedan čvor stabla i postavlja pokazivač na originalni čvor.
 * @param {Tree*} node Čvor koji se kopira
 * @returns {Tree*} Kopirani čvor, ili NULL ukoliko se desila greška
 */
Tree *copyNode(Tree *node) {
    if (node == NULL) {
        return NULL;
    }
    Tree *newNode = getNode(node->value);
    if (newNode == NULL) {
        return NULL;
    }
    newNode->original = node;
    return newNode;
}

/**
 * Kopira celo stablo sa pokazivačima do originalnog stabla u svakom čvoru.
 * @param {Tree*} original Stablo koje se kopira
 * @returns {Tree*} Kopirano stablo, ili NULL ukoliko se desila greška
 */
Tree *copyTree(Tree *original) {
    if (original == NULL) {
        return NULL;
    }
    Tree *newTree = copyNode(original);
    if (newTree == NULL) {
        return NULL;
    }
    NodeTree *stack = NULL;
    Tree *currentNode;
    treeStackPush(&stack, newTree);
    while (stack != NULL) {
        currentNode = treeStackPop(&stack);
        if (currentNode->original->left != NULL) {
            currentNode->left = copyNode(currentNode->original->left);
            if (currentNode->left == NULL) {
                freeTree(newTree);
                while (stack != NULL) {
                    treeStackPop(&stack);
                }
                return NULL;
            }
            treeStackPush(&stack, currentNode->left);
        }
        if (currentNode->original->right != NULL) {
            currentNode->right = copyNode(currentNode->original->right);
            if (currentNode->right == NULL) {
                freeTree(newTree);
                while (stack != NULL) {
                    treeStackPop(&stack);
                }
                return NULL;
            }
            treeStackPush(&stack, currentNode->right);
        }
    }
    return newTree;
}

/**
 * Dodaje stablo u ulančanu listu stabala.
 * @param {TreeList**} trees Ulančana lista stabala
 * @param {Tree*} tree Stablo za dodavanje u ulančanu listu
 * @param {char*} label Oznaka za stablo u meniju za biranje stabla
 * @returns {Result} Uspešnost operacije
 */
Result addTree(TreeList **trees, Tree *tree, char *label) {
    if (trees == NULL) {
        return OOPS;
    }
    TreeList *newTree = malloc(sizeof(TreeList));
    if (newTree == NULL) {
        return OOM;
    }
    newTree->tree = tree;
    newTree->label = label;
    if ((*trees) == NULL) {
        *trees = newTree;
        (*trees)->next = newTree;
    } else {
        newTree->next = (*trees)->next;
        (*trees)->next = newTree;
        *trees = (*trees)->next;
    }
    return OK;
}

/**
 * Proverava da li se čvor sa nekom oznakom nalazi u stablu.
 * @param {Tree*} tree Stablo koje se proverava
 * @param {char} node Oznaka čvora koja se traži
 * @returns {bool} Da li se čvor sa datom oznakom nalazi u stablu
 */
bool containsNode(Tree *tree, char node) {
    if (tree == NULL) {
        return false;
    }
    NodeTree *stack = NULL;
    Tree *currentNode;
    treeStackPush(&stack, tree);
    while (stack != NULL) {
        currentNode = treeStackPop(&stack);
        if (currentNode->value == node) {
            while (stack != NULL) {
                treeStackPop(&stack);
            }
            return true;
        }
        if (currentNode->left != NULL) {
            treeStackPush(&stack, currentNode->left);
        }
        if (currentNode->right != NULL) {
            treeStackPush(&stack, currentNode->right);
        }
    }
    return false;
}
