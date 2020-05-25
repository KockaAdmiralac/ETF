#include "dz5.h"

/**
 * Reverses a doubly-linked list.
 * @param {Node*} list Doubly-linked list to reverse
 * @returns {Node*} Reversed list
 */
Node *reverseList(Node *list) {
    Node *curr = list, *prev;
    while (curr != NULL) {
        prev = curr->prev;
        curr->prev = curr->next;
        curr->next = prev;
        curr = curr->prev;
    }
    return prev->prev;
}

/**
 * Frees a doubly-linked list.
 * @param {Node*} list Doubly-linked list to free from memory
 */
void freeMemory(Node *list) {
    Node *curr = list, *tmp;
    while (curr != NULL) {
        tmp = curr->next;
        for (int i = 0; i < CONTACT_FIELDS; ++i) {
            free(curr->fields->array[i]);
        }
        free(curr->fields);
        free(curr);
        curr = tmp;
    }
}
