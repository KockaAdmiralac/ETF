#include "graph.h"
#include "options.h"
#include "input.h"
#include "util.h"

/**
 * Outputs the menu for option selection.
 * @param {int*} option Pointer to the variable for storing the selected option
 */
void menu(int* option) {
    printf(
        "╔══════════════════════════════════════════════════════════╗\n"
        "║ Treći domaći iz Algoritama i struktura podataka 1        ║\n"
        "║ Student Luka Simić, broj indeksa 368, godina upisa 2019. ║\n"
        "╟──────────────────────────────────────────────────────────╢\n"
        "║ Izaberite opciju za svoju narednu operaciju.             ║\n"
        "║ 1. Unos programskog koda.                                ║\n"
        "║ 2. Ispis grafa.                                          ║\n"
        "║ 3. Određivanje optimalnih rasporeda operacija.           ║\n"
        "║ 4. Određivanje tranzitivnih zavisnosti između operacija. ║\n"
        "║ 0. Izlaz iz programa.                                    ║\n"
        "╚══════════════════════════════════════════════════════════╝\n"
    );
    if (scanf("%d", option) != 1) {
        getchar();
        *option = -1;
    }
}

/**
 * Entry point of the program.
 */
int main() {
    Graph graph;
    Result (*options[])(Graph *) = {
        inputCode,
        outputGraph,
        optimalPath,
        transitiveDependencies
    };
    int option;
    clear();
    createGraph(&graph);
    do {
        menu(&option);
        clear();
        if (option > 0 && option < 5) {
            switch (options[option - 1](&graph)) {
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
    return EXIT_SUCCESS;
}
