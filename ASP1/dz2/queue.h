#ifndef _QUEUE_H
#define _QUEUE_H
#include "tree.h"
#include "util.h"

/**
 * Struktura čvora korišćena u implementaciji reda.
 */
typedef struct index_node {
    struct index_node *next;
    Tree *value;
    int index;
} IndexNode;

Result indexQueuePush(IndexNode **head, IndexNode **tail, Tree *value, int index);
IndexNode *indexQueuePop(IndexNode **head, IndexNode **tail);

#endif
