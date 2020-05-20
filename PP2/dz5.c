#include "dz5.h"

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
