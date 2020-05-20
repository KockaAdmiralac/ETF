#include "dz5.h"

/**
 * Appends a character to a string, given the string's length.
 * @param {char**} Pointer to the string to append the character to
 * @param {int*} valueLength Pointer to the string's length
 * @param {char} newChar Character to append
 */
void addCharToValue(char **value, int *valueLength, char newChar) {
    *valueLength += 1;
    *value = realloc(*value, (*valueLength) * sizeof(char));
    if (*value == NULL) {
        printf("MEM_GRESKA");
        exit(EXIT_SUCCESS);
        return;
    }
    *((*value) + (*valueLength) - 1) = newChar;
}

/**
 * Reads a single contact from the specified file.
 * @param {FILE*} file File to read the contact from
 * @returns {Node*} Contact that was read from the file
 */
Node *readContact(FILE *file) {
    Node *contact = malloc(sizeof(Node));
    if (contact == NULL) {
        printf("MEM_GRESKA");
        exit(EXIT_SUCCESS);
        return NULL;
    }
    bool complexField = false;
    char c, *value = NULL, prev = '\0';
    int currField = 0, valueLength = 0;
    while (fscanf(file, "%c", &c) == 1) {
        if (c == ',') {
            if (complexField) {
                // Read as plain comma.
                addCharToValue(&value, &valueLength, c);
            } else {
                // Read as value separator.
                if (currField == CONTACT_FIELDS) {
                    printf("DAT_GRESKA");
                    exit(EXIT_SUCCESS);
                    return NULL;
                }
                addCharToValue(&value, &valueLength, '\0');
                contact->fields.array[currField++] = value;
                value = NULL;
                valueLength = 0;
            }
        } else if (c == '"') {
            if (prev == '\0' || prev == ',') {
                // Start complex field.
                complexField = true;
            } else if (complexField) {
                int scanfResult = fscanf(file, "%c", &c);
                if (scanfResult != 1 || c == '\n' || c == '\r') {
                    // We hit the end of line.
                    if (c == '\r') {
                        fscanf(file, "%*c");
                    }
                    break;
                }
                if (c == ',') {
                    // We just read both the complex field closing and
                    // value separator.
                    complexField = false;
                    if (currField == CONTACT_FIELDS) {
                        printf("DAT_GRESKA");
                        exit(EXIT_SUCCESS);
                        return NULL;
                    }
                    addCharToValue(&value, &valueLength, '\0');
                    contact->fields.array[currField++] = value;
                    value = NULL;
                    valueLength = 0;
                } else if (c == '"') {
                    // Escaped quotation mark.
                    addCharToValue(&value, &valueLength, c);
                } else {
                    // Unexpected character.
                    printf("DAT_GRESKA");
                    exit(EXIT_SUCCESS);
                    return NULL;
                }
            } else {
                // Quotation marks cannot appear in a non-complex field.
                printf("DAT_GRESKA");
                exit(EXIT_SUCCESS);
                return NULL;
            }
        } else if (c == '\n') {
            break;
        } else if (c == '\r') {
            // This is \r\n. Remove the \n.
            fscanf(file, "%*c");
            break;
        } else {
            addCharToValue(&value, &valueLength, c);
        }
        prev = c;
    }
    if (valueLength != 0 || value != NULL) {
        // There is a value that we haven't finished reading.
        free(value);
        printf("DAT_GRESKA");
        exit(EXIT_SUCCESS);
        return NULL;
    }
    if (currField == 0) {
        // This is an empty line.
        free(contact);
        return NULL;
    }
    if (currField != CONTACT_FIELDS) {
        // There are more values than expected.
        printf("DAT_GRESKA");
        exit(EXIT_SUCCESS);
        return NULL;
    }
    return contact;
}

/**
 * Reads all contacts from the specified file.
 * @param {FILE*} file File to read the contacts from
 * @returns {Node*} Contacts that were read from the file
 */
Node *readContacts(FILE *file) {
    int status;
    char c;
    do {
        status = fscanf(file, "%c", &c);
    } while (c != '\n' && status == 1);
    Node *prev = NULL, *curr, *list;
    do {
        curr = readContact(file);
        if (curr != NULL) {
            curr->prev = prev;
        }
        if (prev == NULL) {
            list = curr;
        } else {
            prev->next = curr;
        }
        prev = curr;
    } while (curr != NULL);
    return list;
}
