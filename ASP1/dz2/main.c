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
    Tree *const tree = inputExpression();
    if (tree == NULL) {
        // Desila se greška.
        return EXIT_FAILURE;
    }
    int option = 1;
    Result (*options[])(Tree*) = {
        printTree,
        printPostfix,
        calculateExpression,
        differentiate
    };
    clear();
    while (option) {
        menu(&option);
        clear();
        if (option > 0 && option < 5) {
            switch (options[option - 1](tree)) {
                case OK: break;
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
        } else {
            printf("Nije izabrana validna opcija.\n");
        }
    }
    return EXIT_SUCCESS;
}
