#include "input.h"
#include "options.h"
#include "tree.h"
#include "util.h"

/**
 * Ispis menija za izbor opcija.
 * @param {int*} option Pokazivač na promenljivu za čuvanje izabrane opcije
 */
void menu(int* option) {
    printf(
        "╔══════════════════════════════════════════════════════════╗\n"
        "║ Drugi domaći iz Algoritama i struktura podataka 1        ║\n"
        "║ Student Luka Simić, broj indeksa 368, godina upisa 2019. ║\n"
        "╟──────────────────────────────────────────────────────────╢\n"
        "║ Izaberite opciju za svoju narednu operaciju.             ║\n"
        "║ 1. Ispis izgleda formiranog stabla.                      ║\n"
        "║ 2. Ispis unetog izraza u postfiksnoj notaciji.           ║\n"
        "║ 3. Računanje vrednosti izraza.                           ║\n"
        "║ 4. Diferenciranje izraza po zadatoj promenljivoj.        ║\n"
        "║ 0. Izlaz iz programa.                                    ║\n"
        "╚══════════════════════════════════════════════════════════╝\n"
    );
    scanf("%d", option);
}

/**
 * Ulazna tačka za program.
 */
int main(void) {
    int option;
    // Alociranje niza stabala.
    TreeList *trees = NULL;
    const char *originalLabelConst = "Originalno stablo";
    char *originalLabel = malloc((strlen(originalLabelConst) + 1) * sizeof(char));
    if (originalLabel == NULL) {
        return EXIT_FAILURE;
    }
    strcpy(originalLabel, originalLabelConst);
    // Inicijalizacija promenljivih za evaluaciju.
    InputVariable variables[26];
    for (int i = 0; i < 26; ++i) {
        variables[i].present = false;
        variables[i].value = 0;
    }
    Tree *const inputTree = inputExpression(variables);
    if (inputTree == NULL) {
        // Desila se greška.
        free(originalLabel);
        return EXIT_FAILURE;
    }
    addTree(&trees, inputTree, originalLabel);
    // Glavna petlja.
    Result (*options[])(TreeList**, InputVariable[26]) = {
        printTree,
        printPostfix,
        calculateExpression,
        differentiate
    };
    clear();
    do {
        menu(&option);
        clear();
        if (option > 0 && option < 5) {
            switch (options[option - 1](&trees, variables)) {
                case OK:
                    // Sve je u redu.
                case RTFM:
                    // Očekujemo da će pozivajući kod da ispiše grešku.
                    break;
                case OOM:
                    printf(
                        "Ponestalo je memorije tokom izvršavanja operacije.\n"
                    );
                    break;
                case OOPS:
                default:
                    printf("Desila se nepoznata greška.\n");
                    break;
            }
        } else if (option != 0) {
            printf("Nije izabrana validna opcija.\n");
        }
    } while (option);
    freeTrees(trees);
    return EXIT_SUCCESS;
}
