#include "dz5.h"

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
            curr->fields->named.workAddress2,
            curr->fields->named.workAddress,
            curr->fields->named.workCity,
            curr->fields->named.workState,
            curr->fields->named.workZipCode,
            curr->fields->named.workCountry
        );
        if (lastSetWorkAddressField) {
            concatArgs(
                file,
                "adr",
                lastSetWorkAddressField < 2 ?
                    lastSetWorkAddressField :
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
