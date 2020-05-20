/**
 * Assumptions made:
 * - All comments should and will be writte in English, for consistency with
 *   the language used in the actual code.
 * - February has 28 days.
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Represents a linked list node.
 */
typedef struct node {
    // Customer name.
    char *name;
    // Type of service.
    char *type;
    // Order status.
    bool status;
    // Day of order.
    int day;
    // Month of order.
    int month;
    // Amount of days for the order to get processed.
    int time;
    // Next node in the linked list.
    struct node *next;
} Node;

/**
 * Reads a string from the standard input, terminated by a newline or a comma.
 * Ignores leading spaces. If memory fails to allocate, terminates the program.
 * @returns {char*} String read from the standard input
 */
char *readString() {
    int length = 0;
    char *word = malloc(sizeof(char)), *tempWord, input;
    if (word == NULL) {
        printf("MEM_GRESKA");
        exit(0);
        return NULL;
    }
    *word = '\0';
    while (true) {
        input = getchar();
        if (length == 0 && input == ' ') {
            continue;
        }
        if (input == ',' || input == '\n') {
            break;
        }
        *(word + length) = input;
        ++length;
        tempWord = realloc(word, (length + 1) * sizeof(char));
        if (tempWord == NULL) {
            free(word);
            printf("MEM_GRESKA");
            exit(0);
            return NULL;
        }
        word = tempWord;
        *(word + length) = '\0';
    }
    return word;
}

/**
 * Reads a single order's information from standard input into a linked list
 * node. If memory fails to allocate, terminates the program.
 * @returns {Node*} Node whose information was read from standard input, or
 *                  NULL if no node information was provided
 */
Node *readNode() {
    Node *ret = malloc(sizeof(Node));
    if (ret == NULL) {
        printf("MEM_GRESKA");
        exit(0);
        return NULL;
    }
    char *name = readString();
    if (*name == '\0') {
        // The only content in the row is a newline.
        free(ret);
        free(name);
        return NULL;
    }
    int tempBool;
    ret->name = name;
    ret->type = readString();
    scanf(" %d, %d.%d., %d", &tempBool, &ret->day, &ret->month, &ret->time);
    ret->status = tempBool;
    // Get rid of last \n.
    getchar();
    ret->next = NULL;
    return ret;
}

/**
 * Reads order information from standard input.
 * @returns {Node*} Last order from standard input, first order in the list
 */
Node *readNodes() {
    Node *currentNode, *lastNode = NULL;
    while ((currentNode = readNode()) != NULL) {
        currentNode->next = lastNode;
        lastNode = currentNode;
    }
    return lastNode;
}

/**
 * Gets amount of days in a specified month.
 * @param {int} month Month whose amount of days should be returned
 * @returns {int} Amount of days in the specified month
 */
int daysInMonth(int month) {
    switch (month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        case 2:
            return 28;
        default:
            return 0;
    }
}

/**
 * Gets the amount of days since the start of the year that an order needs to
 * be done by.
 * @param {Node*} node Order to get the amount of days for
 * @returns {int} Amount of days since the start of the year for the specified
 *                order to be done by
 */
int doneByDate(Node *node) {
    int daysSinceStart = node->day + node->time;
    for (int i = 1; i < node->month; ++i) {
        daysSinceStart += daysInMonth(i);
    }
    return daysSinceStart;
}

/**
 * Checks whether an order should be done by a specified date.
 * @param {Node*} node Order to check
 * @param {int} day Day by which the order should be done
 * @param {int} month Month by which the order should be done
 * @returns {bool} Whether the order should be done by the specified date
 */
bool shouldBeDoneBy(Node *node, int day, int month) {
    Node fakeNode;
    fakeNode.day = day;
    fakeNode.month = month;
    fakeNode.time = 0;
    return doneByDate(node) <= doneByDate(&fakeNode);
}

/**
 * Clones a linked list into another linked list with only orders being those
 * that are not finished and that need to be finished by a specified date.
 * If memory fails to allocate, terminates the program.
 * @param {Node*} list List to be cloned
 * @param {int} day Day by which the orders should be finished
 * @param {int} month Month by which the orders should be finished
 * @returns {Node*} Cloned list
 */
Node *cloneList(Node *list, int day, int month) {
    if (list == NULL) {
        return NULL;
    }
    Node *newList = NULL,
         *curr = list,
         *currNew;
    while (curr != NULL) {
        if (curr->status == 0 && shouldBeDoneBy(curr, day, month)) {
            Node *copiedNode = malloc(sizeof(Node));
            if (copiedNode == NULL) {
                printf("MEM_GRESKA");
                exit(0);
                return NULL;
            }
            *copiedNode = *curr;
            copiedNode->name = malloc((strlen(curr->name) + 1) * sizeof(char));
            if (copiedNode->name == NULL) {
                printf("MEM_GRESKA");
                exit(0);
                return NULL;
            }
            strcpy(copiedNode->name, curr->name);
            copiedNode->type = malloc((strlen(curr->type) + 1) * sizeof(char));
            if (copiedNode->type == NULL) {
                printf("MEM_GRESKA");
                exit(0);
                return NULL;
            }
            strcpy(copiedNode->type, curr->type);
            if (newList == NULL) {
                newList = copiedNode;
                currNew = newList;
            } else {
                currNew->next = copiedNode;
                currNew = currNew->next;
            }
        }
        curr = curr->next;
    }
    return newList;
}

/**
 * Sorts a linked list of orders by date they should be done by in-place.
 * @param {Node*} list List to sort
 */
void sortList(Node *list) {
    if (list == NULL) {
        return;
    }
    Node *curr, *prev;
    int swaps, tmpDayMonthTime, doneByPrev, doneByCurr;
    char *tmpNameType;
    bool tmpStatus;
    do {
        swaps = 0;
        prev = list;
        curr = list->next;
        while (curr != NULL) {
            doneByPrev = doneByDate(prev);
            doneByCurr = doneByDate(curr);
            if (
                doneByPrev > doneByCurr || (
                    doneByPrev == doneByCurr &&
                    prev->time > curr->time
                )
            ) {
                ++swaps;
                // Swap name
                tmpNameType = prev->name;
                prev->name = curr->name;
                curr->name = tmpNameType;
                // Swap type
                tmpNameType = prev->type;
                prev->type = curr->type;
                curr->type = tmpNameType;
                // Swap status
                tmpStatus = prev->status;
                prev->status = curr->status;
                curr->status = tmpStatus;
                // Swap day
                tmpDayMonthTime = prev->day;
                prev->day = curr->day;
                curr->day = tmpDayMonthTime;
                // Swap month
                tmpDayMonthTime = prev->month;
                prev->month = curr->month;
                curr->month = tmpDayMonthTime;
                // Swap time
                tmpDayMonthTime = prev->time;
                prev->time = curr->time;
                curr->time = tmpDayMonthTime;
            }
            prev = curr;
            curr = curr->next;
        }
    } while (swaps > 0);
}

/**
 * Returns a sorted list of orders which should be done by a specified date.
 * @param {Node*} list List to clone and then sort
 * @param {int} day Day by which orders should be done
 * @param {int} month Month by which orders should be done
 * @returns {Node*} A new sorted list
 */
Node *sortedList(Node *list, int day, int month) {
    Node *newList = cloneList(list, day, month);
    sortList(newList);
    return newList;
}

/**
 * Prints out a linked list.
 * @param {Node*} list List to print out
 */
void printList(Node *list) {
    if (list == NULL) {
        return;
    }
    Node *curr = list;
    while (curr != NULL) {
        printf(
            "%s, %s, %d, %02d.%02d., %d\n",
            curr->name,
            curr->type,
            curr->status,
            curr->day,
            curr->month,
            curr->time
        );
        curr = curr->next;
    }
}

/**
 * Deallocates a linked list.
 * @param {Node*} list List to deallocate
 */
void freeList(Node *list) {
    Node *curr = list, *tmp;
    while (curr != NULL) {
        free(curr->name);
        free(curr->type);
        tmp = curr;
        curr = curr->next;
        free(tmp);
    }
}

/**
 * Fights for freedom of all linked lists, not discriminating by their sorting
 * status.
 * @param {Node*} list An unsorted list to be freed
 * @param {Node*} sortedList A sorted list to be freed
 */
void freedomFighters(Node *list, Node *sortedList) {
    freeList(list);
    freeList(sortedList);
}

/**
 * Entry point of the program.
 */
int main() {
    Node *list = readNodes(), *sorted;
    int day, month;
    scanf("%d.%d.", &day, &month);
    printList(list);
    sorted = sortedList(list, day, month);
    printList(sorted);
    freedomFighters(list, sorted);
    return 0;
}
