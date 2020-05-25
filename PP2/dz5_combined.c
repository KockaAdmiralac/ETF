#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONTACT_FIELDS 37

typedef struct {
    char *firstName;
    char *lastName;
    char *displayName;
    char *nickname;
    char *primaryEmail;
    char *secondaryEmail;
    char *screenName;
    char *workPhone;
    char *homePhone;
    char *faxNumber;
    char *pagerNumber;
    char *mobileNumber;
    char *homeAddress;
    char *homeAddress2;
    char *homeCity;
    char *homeState;
    char *homeZipCode;
    char *homeCountry;
    char *workAddress;
    char *workAddress2;
    char *workCity;
    char *workState;
    char *workZipCode;
    char *workCountry;
    char *jobTitle;
    char *department;
    char *organization;
    char *webPage1;
    char *webPage2;
    char *birthYear;
    char *birthMonth;
    char *birthDay;
    char *custom1;
    char *custom2;
    char *custom3;
    char *custom4;
    char *notes;
} Fields;

typedef union {
    Fields named;
    char *array[CONTACT_FIELDS];
} FieldsUnion;

typedef struct node {
    FieldsUnion *fields;
    struct node *prev, *next;
} Node;

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
 * @returns {FieldsUnion*} Contact information that was read from the file
 */
FieldsUnion *readContact(FILE *file) {
    FieldsUnion *contact = malloc(sizeof(FieldsUnion));
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
                contact->array[currField++] = value;
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
                    contact->array[currField++] = value;
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
                // Quotation marks can probably appear in a non-complex field.
                addCharToValue(&value, &valueLength, c);
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
    while (true) {
        curr = malloc(sizeof(Node));
        if (curr == NULL) {
            printf("MEM_GRESKA");
            exit(0);
            return NULL;
        }
        curr->fields = readContact(file);
        if (curr->fields == NULL) {
            if (prev != NULL) {
                prev->next = NULL;
            }
            free(curr);
            break;
        }
        curr->prev = prev;
        if (prev == NULL) {
            list = curr;
        } else {
            prev->next = curr;
        }
        prev = curr;
    }
    return list;
}

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

/**
 * Finds the last non-empty string in the passed arguments.
 * @param {int} count Amount of arguments passed
 * @returns {int} Last field that is set (first field is 1)
 */
int lastSetField(int count, ...) {
    va_list arguments;
    va_start(arguments, count);
    int lastField = 0;
    for (int i = 0; i < count; ++i) {
        if (*(va_arg(arguments, char*)) != '\0') {
            lastField = i + 1;
        }
    }
    return lastField;
}

/**
 * Concatenates a variable amount of arguments with semicolons and writes
 * them to the specified file.
 * @param {FILE*} file File to write concatenated arguments to.
 * @param {int} count Amount of arguments to concatenate
 */
void concatArgs(FILE *file, const char *start, int count, ...) {
    va_list arguments;
    va_start(arguments, count);
    fprintf(file, "%s:", start);
    for (int i = 0; i < count; ++i) {
        fprintf(file, "%s", va_arg(arguments, char*));
        if (i != count - 1) {
            fprintf(file, ";");
        }
    }
    fprintf(file, "\n");
}

/**
 * Prints a contact row to a file in case the field isn't empty.
 * @param {FILE*} file File to print the row to
 * @param {char*} start Beginning of the row
 * @param {char*} data Data in the row
 */
void conditionalPrint(FILE *file, const char *start, char *data) {
    if (*data != '\0') {
        fprintf(file, "%s:%s\n", start, data);
    }
}

/**
 * Writes the contact list to a new file.
 * @param {char*} fileName File to write the contact list to
 * @param {Node*} list Contact list to write
 */
void writeToFile(char *fileName, Node *list) {
    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        printf("DAT_GRESKA");
        exit(EXIT_SUCCESS);
        return;
    }
    Node *curr = list;
    while (curr != NULL) {
        if (curr != list) {
            fprintf(file, "\n");
        }
        fprintf(file, "begin:vcard\n");
        conditionalPrint(file, "fn", curr->fields->named.displayName);
        int lastSetNameField = lastSetField(
            2,
            curr->fields->named.lastName,
            curr->fields->named.firstName
        );
        if (lastSetNameField) {
            concatArgs(
                file,
                "n",
                lastSetNameField,
                curr->fields->named.lastName,
                curr->fields->named.firstName
            );
        }
        int lastSetOrganizationField = lastSetField(
            2,
            curr->fields->named.organization,
            curr->fields->named.department
        );
        if (lastSetOrganizationField) {
            concatArgs(
                file,
                "org",
                lastSetOrganizationField,
                curr->fields->named.organization,
                curr->fields->named.department
            );
        }
        int lastSetWorkAddressField = lastSetField(
            6,
            curr->fields->named.workAddress,
            curr->fields->named.workAddress2,
            curr->fields->named.workCity,
            curr->fields->named.workState,
            curr->fields->named.workZipCode,
            curr->fields->named.workCountry
        );
        if (lastSetWorkAddressField) {
            concatArgs(
                file,
                "adr",
                lastSetWorkAddressField + 1,
                // Testing has proven Work Address 2 comes before Work Address.
                curr->fields->named.workAddress2,
                // This is always empty.
                "",
                curr->fields->named.workAddress,
                curr->fields->named.workCity,
                curr->fields->named.workState,
                curr->fields->named.workZipCode,
                curr->fields->named.workCountry
            );
        }
        conditionalPrint(
            file,
            "email;internet",
            curr->fields->named.primaryEmail
        );
        conditionalPrint(file, "title", curr->fields->named.jobTitle);
        conditionalPrint(file, "tel;work", curr->fields->named.workPhone);
        conditionalPrint(file, "tel;fax", curr->fields->named.faxNumber);
        conditionalPrint(file, "tel;pager", curr->fields->named.pagerNumber);
        conditionalPrint(file, "tel;home", curr->fields->named.homePhone);
        conditionalPrint(file, "tel;cell", curr->fields->named.mobileNumber);
        conditionalPrint(file, "note", curr->fields->named.notes);
        conditionalPrint(file, "url", curr->fields->named.webPage1);
        fprintf(file, "version:2.1\nend:vcard\n");
        curr = curr->next;
    }
    fclose(file);
}

/**
 * Entry point of the program.
 * @param {int} argc Amount of command-line arguments specified to the program.
 *                   During a valid invocation may be 3 or 4
 * @param {char**} argv Command-line arguments specified to the program
 * @returns {int} Program exit code
 */
int main(int argc, char **argv) {
    if (argc < 3 || argc > 4) {
        // Wrong amount of arguments.
        printf("ARG_GRESKA");
        return EXIT_SUCCESS;
    }
    if (argc == 4 && strcmp(*(argv + 3), "-reverse")) {
        // Wrong argument type.
        printf("ARG_GRESKA");
        return EXIT_SUCCESS;
    }
    FILE *inputFile = fopen(*(argv + 1), "r");
    if (inputFile == NULL) {
        printf("DAT_GRESKA");
        return EXIT_SUCCESS;
    }
    Node *contacts = readContacts(inputFile);
    if (argc == 4) {
        contacts = reverseList(contacts);
    }
    writeToFile(*(argv + 2), contacts);
    freeMemory(contacts);
    fclose(inputFile);
    return EXIT_SUCCESS;
}
