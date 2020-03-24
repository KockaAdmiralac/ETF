/**
 * Usvojene pretpostavke:
 * - Dimenzije matrice su jednake (u zadatku se pominje "glavna dijagonala").
 * - Elementi matrice su brojevi koji mogu da stanu u tip 'int'.
 * - Indeksiranje se radi od nule.
 * - Dijagonala koja odvaja podrazumevane od nepodrazumevanih elemenata je
 *   glavna dijagonala.
 * - Podrazumevana vrednost je podrazumevano 0.
 * - Ušteđen prostor se umanjuje za jedan jer nam toliko polja treba za čuvanje
 *   podrazumevane vrednosti.
 */
#include <stdio.h>
#include <stdlib.h>
#define VT100_ESCAPE 27

/**
 * Čišćenje ekrana realizovano korišćenjem VT100 komandi.
 * @see https://www.csie.ntu.edu.tw/~r92094/c++/VT100.html
 */
void clear() {
    printf("%c[2J%c[f", VT100_ESCAPE, VT100_ESCAPE);
}

/**
 * Ispis menija za izbor opcija.
 * @param {int*} option Pokazivač na promenljivu za čuvanje izabrane opcije
 */
void menu(int* option) {
    printf(
        "========================================================\n"
        "Prvi domaći iz Algoritama i struktura podataka 1\n"
        "Student Luka Simić, broj indeksa 368, godina upisa 2019.\n"
        "========================================================\n"
        "Izaberite opciju za svoju narednu operaciju.\n"
        "  1. Stvaranje matrice zadatih dimenzija uz inicijalizaciju "
             "nepodrazumevanim vrednostima\n"
        "  2. Postavljanje podrazumevane vrednosti\n"
        "  3. Dohvatanje zadatog elementa, uz proveru validnosti opsega\n"
        "  4. Postavljanje vrednosti zadatom elementu, uz proveru validnosti "
             "opsega\n"
        "  5. Dohvatanje broja nepodrazumevanih elemenata\n"
        "  6. Ispis matrice (uključujući i elemente podrazumevane vrednosti)\n"
        "  7. Računanje ostvarene uštede memorijskog prostora\n"
        "  8. Brisanje matrice\n"
        "  0. Izlaz iz programa.\n"
    );
    scanf("%d", option);
}

/**
 * Vraća broj nepodrazumevanih elemenata matrice, odnosno veličinu niza.
 * @param {int} dimension Dimenzija matrice čije se vrednosti čuvaju
 */
int vector_size(int dimension) {
    return dimension * (dimension - 1) / 2;
}

/**
 * Vraća pokazivač do nepodrazumevanog elementa u nizu na osnovu njegovih
 * koordinata u matrici, takođe poznata kao adresna funkcija.
 * @param {int*} matrix Matrica iz koje se čita element
 * @param {int} x X koordinata (broj kolone) elementa u matrici
 * @param {int} y Y koordinata (broj vrste) elementa u matrici
 */
int *get_element(int *matrix, int x, int y) {
    return matrix + y * (y - 1) / 2 + x;
}

/**
 * Ulazna tačka za program.
 */
int main(void) {
    int opcija = 0, dimenzija, *matrica = NULL, podrazumevana = 0, x, y, v;
    clear();
    menu(&opcija);
    while (opcija) {
        clear();
        switch (opcija) {
            case 1:
                // Stvaranje matrice
                printf("Unesite dimenziju matrice: ");
                scanf("%d", &dimenzija);
                if (dimenzija <= 0) {
                    printf("Uneta dimenzija nije validna!\n");
                    break;
                }
                if (matrica != NULL) {
                    free(matrica);
                }
                int size = vector_size(dimenzija);
                matrica = malloc((size || 1) * sizeof(int));
                if (size) {
                    printf("Unesite elemente matrice:\n");
                    for (int i = 0; i < size; ++i) {
                        scanf("%d", matrica + i);
                    }
                }
                break;
            case 2:
                // Unos podrazumevane vrednosti
                printf("Unesite podrazumevanu vrednost: ");
                scanf("%d", &podrazumevana);
                break;
            case 3:
                // Dohvatanje zadatog elementa
                if (matrica == NULL) {
                    printf("Matrica nije inicijalizovana!\n");
                    break;
                }
                printf("Unesite koordinate elementa matrice (x, y): ");
                scanf("%d %d", &x, &y);
                if (x >= dimenzija || x < 0 || y >= dimenzija || y < 0) {
                    printf("Nisu unete validne koordinate!\n");
                    break;
                }
                if (x >= y) {
                    printf("%d\n", podrazumevana);
                } else {
                    printf("%d\n", *(get_element(matrica, x, y)));
                }
                break;
            case 4:
                // Postavljanje vrednosti
                if (matrica == NULL) {
                    printf("Matrica nije inicijalizovana!\n");
                    break;
                }
                printf("Unesite koordinate elementa matrice (x, y): ");
                scanf("%d %d", &x, &y);
                if (x >= dimenzija || x < 0 || y >= dimenzija || y < 0) {
                    printf("Nisu unete validne koordinate!\n");
                    break;
                }
                if (x >= y) {
                    printf("Ne može se postaviti podrazumevani element!\n");
                    break;
                }
                printf("Unesite vrednost unetog polja: ");
                scanf("%d", &v);
                *(get_element(matrica, x, y)) = v;
                break;
            case 5:
                // Broj nepodrazumevanih elemenata
                if (matrica == NULL) {
                    printf("Matrica nije inicijalizovana!\n");
                    break;
                }
                printf(
                    "Broj nepodrazumevanih elemenata je %d.\n",
                    vector_size(dimenzija)
                );
                break;
            case 6:
                // Ispis matrice
                if (matrica == NULL) {
                    printf("Matrica nije inicijalizovana!\n");
                    break;
                }
                for (y = 0; y < dimenzija; ++y) {
                    for (x = 0; x < y; ++x) {
                        printf("% 4d ", *(get_element(matrica, x, y)));
                    }
                    for (; x < dimenzija; ++x) {
                        printf("% 4d ", podrazumevana);
                    }
                    printf("\n");
                }
                break;
            case 7:
                // Ušteđeni prostor
                if (matrica == NULL) {
                    printf("Matrica nije inicijalizovana!\n");
                    break;
                }
                int matrix_size = dimenzija * dimenzija,
                    savings = matrix_size - vector_size(dimenzija) - 1;
                printf(
                    "Broj ušteđenih memorijskih prostora: %d\n"
                    "Broj ušteđenih bajtova: %lu\n"
                    "Procenat ušteđenog prostora: %f%%\n",
                    savings,
                    savings * sizeof(int),
                    (double)savings / (double)matrix_size * 100
                );
                break;
            case 8:
                // Brisanje matrice
                if (matrica == NULL) {
                    printf("Matrica nije inicijalizovana!\n");
                    break;
                }
                dimenzija = -1;
                free(matrica);
                matrica = NULL;
                break;
            default:
                // Ništa od navedenog.
                printf("Izabrana opcija nije validna!\n");
        }
        menu(&opcija);
    }
    if (matrica != NULL) {
        free(matrica);
    }
    return 0;
}
