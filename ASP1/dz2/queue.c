#include "queue.h"

/**
 * Ubacuje čvor i njegov indeks u punom stablu u red.
 * @param {IndexNode**} head Strana reda na koju se ubacuju čvorovi
 * @param {IndexNode**} tail Strana reda sa koje se izbacuju čvorovi
 * @param {Tree*} value Čvor koji se ubacuje u red
 * @param {int} index Indeks čvora u punom stablu
 * @returns {Result} Uspešnost operacije
 */
Result indexQueuePush(IndexNode **head, IndexNode **tail, Tree *value, int index) {
    if (
        head == NULL ||
        tail == NULL ||
        ((*head) == NULL && (*tail) != NULL) ||
        ((*tail) == NULL && (*head) != NULL)
    ) {
        return OOPS;
    }
    IndexNode *newNode = malloc(sizeof(IndexNode));
    if (newNode == NULL) {
        return OOM;
    }
    newNode->value = value;
    newNode->index = index;
    newNode->next = NULL;
    if ((*head) == NULL) {
        *head = newNode;
        *tail = newNode;
    } else {
        (*head)->next = newNode;
        *head = (*head)->next;
    }
    return OK;
}

/**
 * Izbacuje čvor i njegov indeks u punom stablu iz reda.
 * NAPOMENA: Dealokacija ovog čvora se ostavlja korisniku!
 * @param {IndexNode**} head Strana reda na koju se ubacuju čvorovi
 * @param {IndexNode**} tail Strana reda sa koje se izbacuju čvorovi
 * @returns {IndexNode*} Struktura sa čvorom i njegovim indeksom
 */
IndexNode *indexQueuePop(IndexNode **head, IndexNode **tail) {
    if (head == NULL || tail == NULL || (*head) == NULL || (*tail) == NULL) {
        return NULL;
    }
    IndexNode *returnValue = (*tail);
    *tail = (*tail)->next;
    if ((*tail) == NULL) {
        *head = NULL;
    }
    // Oslobađanje se ostavlja korisniku!
    return returnValue;
}
