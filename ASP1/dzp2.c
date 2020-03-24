/**
 * Usvojene pretpostavke:
 * - Promenljive koje nisu postavljene imaju vrednost 0.
 * - Izraz koji se unosi nije duži od 2^16 karaktera.
 */
#include <stdbool.h>
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
        "  1. Unos izraza za evaluaciju\n"
        "  2. Postavljanje promenljive za evaluaciju\n"
        "  3. Evaluacija izraza\n"
        "  0. Izlaz iz programa.\n"
    );
    scanf("%d", option);
}

/**
 * Struktura koja opisuje jedan čvor povezane liste.
 */
typedef struct node {
    struct node *next;
    double value;
} Node;

/**
 * Guranje vrednosti na stek.
 * @param {Node**} tail Pokazivač na pokazivač na poslednji element steka
 * @param {double} value Vrednost koja se gura na stek
 */
void stack_push(Node **tail, double value) {
    Node *new_node = malloc(sizeof(Node));
    new_node->value = value;
    if (*tail == NULL) {
        new_node->next = new_node;
        *tail = new_node;
    } else {
        Node *old_next = (*tail)->next;
        (*tail)->next = new_node;
        new_node->next = old_next;
    }
}

/**
 * Izbacuje i izvlači poslednju vrednost sa steka.
 * @param {Node**} tail Pokazivač na pokazivač na poslednji element steka
 * @returns {double} (Bivša) poslednja vrednost sa steka
 */
double stack_pop(Node **tail) {
    double pop_value;
    if (*tail == NULL) {
        // Ovo se nikada neće desiti (izbacivanje iz praznog steka).
        return -1;
    }
    if (*tail == (*tail)->next) {
        // Izbacivanje iz steka s jednim elementom.
        pop_value = (*tail)->value;
        free(*tail);
        *tail = NULL;
    } else {
        Node *new_next = (*tail)->next->next;
        pop_value = (*tail)->next->value;
        free((*tail)->next);
        (*tail)->next = new_next;
    }
    return pop_value;
}

/**
 * Validira postfiksni izraz.
 * @param {char*} expression Izraz za validaciju
 * @returns {bool} Da li je postfiksni izraz validan
 */
bool validate(char *expression) {
    int stack_count = 0, i = 0;
    char next_char;
    while ((next_char = *(expression + (i++))) != '\0') {
        if (
            next_char == '+' ||
            next_char == '-' ||
            next_char == '*' ||
            next_char == '/'
        ) {
            // Operator
            if (--stack_count < 1) {
                return false;
            }
        } else if (next_char >= 'A' && next_char <= 'Z') {
            // Promenljiva
            ++stack_count;
        } else {
            // Nije validan karakter
            return false;
        }
    }
    // Da li stek ima jednu vrednost nakon evaluacije
    return stack_count == 1;
}

/**
 * Evaluira postfiksni izraz sa zadatim vrednostima.
 * @param {char*} expression Izraz za evaluaciju
 * @param {double[]} values Vrednosti izraza za evaluaciju
 * @returns {double} Krajnja vrednost izraza
 */
double evaluate(char *expression, double values[26]) {
    Node *stack = NULL;
    double second_operand;
    int i = 0;
    char next_char;
    while ((next_char = *(expression + (i++))) != '\0') {
        switch(next_char) {
            case '+':
                stack_push(&stack, stack_pop(&stack) + stack_pop(&stack));
                break;
            case '-':
                second_operand = stack_pop(&stack);
                stack_push(&stack, stack_pop(&stack) - second_operand);
                break;
            case '*':
                stack_push(&stack, stack_pop(&stack) * stack_pop(&stack));
                break;
            case '/':
                second_operand = stack_pop(&stack);
                if (second_operand == 0) {
                    printf(
                        "Nije dozvoljeno deljenje nulom! "
                        "Postavite sve delioce u izrazu na ne-nultu "
                        "vrednost.\n"
                    );
                    return 0;
                }
                stack_push(&stack, stack_pop(&stack) / second_operand);
                break;
            default:
                // Promenljiva
                stack_push(&stack, values[next_char - 'A']);
        }
    }
    return stack_pop(&stack);
}

int main(void) {
    char izraz[65536] = "", var_name;
    int option;
    double vrednosti[26] = {0}, var_value;
    clear();
    menu(&option);
    while (option) {
        clear();
        switch (option) {
            case 1:
                // Unos izraza
                printf("Unesite izraz u postfiksnom obliku: ");
                scanf("%s", izraz);
                if (!validate(izraz) || izraz[0] == '\0') {
                    printf("Uneseni izraz nije validan!\n");
                    izraz[0] = '\0';
                }
                break;
            case 2:
                // Unos promenljive
                printf("Unesite naziv promenljive za postavljanje: ");
                scanf(" %c", &var_name);
                if (var_name < 'A' || var_name > 'Z') {
                    printf("Uneto ime promenljive nije validno!\n");
                    break;
                }
                printf("Unesite vrednost promenljive %c: ", var_name);
                scanf("%lf", &var_value);
                vrednosti[var_name - 'A'] = var_value;
                break;
            case 3:
                if (izraz[0] == '\0') {
                    printf("Prvo unesite izraz!\n");
                    break;
                }
                // Evaluacija izraza
                printf(
                    "Rezultat evaluacije unetog izraza: %lf\n",
                    evaluate(izraz, vrednosti)
                );
                break;
            default:
                // Ništa od navedenog.
                printf("Izabrana opcija nije validna!\n");
        }
        menu(&option);
    }
}
