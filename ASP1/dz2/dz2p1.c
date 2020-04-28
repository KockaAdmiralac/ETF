/**
 * Usvojene pretpostavke:
 * - Program se može kompajlirati preko GCC. (Kompatibilnost sa
 *   Majkrosoftovim razlikama od normalnih C kompajlera nije testirana.)
 *   Konkretna verzija GCC korišćena za kompilaciju jeste
 *   "gcc (Arch Linux 9.3.0-1) 9.3.0"
 * - Stabla nikada neće biti duboka preko log2(sizeof(long long)).
 * - U skladu sa odgovorom profesora Mišića na mejl poslat 21. aprila,
 *   usvajaju se sledeće pretpostavke u vezi sa funkcijom za minimum:
 *   - Funkcija za minimum se gubi nakon prvog izvoda tako što se od korisnika
 *     traži da unese vrednosti kojima se određuje koja funkcija se izvodi.
 *   - Prvi izvod funkcije za minimum sadrži podstabla za sve četiri funkcije,
 *     f(x), g(x), f'(x) i g'(x), kako bi se evaluacija ovog izraza, kao i
 *     drugi izvod, mogli sprovoditi. Ovo stablo može izgledati kao što je
 *     u gorepomenutom mejlu navedeno:
 *              min
 *            /    \
 *         ?          ?
 *       /  \      /    \
 *     f(x) g(x)  f'(x) g'(x) *
 *     Za ove potrebe uveden je kvazi-operator '?'.
 * Korisni test primeri:
 * - (A+B)/C*D
 * - ln(A+B)^(C*D-E)
 * - min((A+ln(A*B))/min(tg(-C), D)-E, ln(tg(-F)))
 *
 * Domaći je, barem delimično, proveren Valgrind-om protiv curenja memorije.
 */
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define VT100_ESCAPE 27
// Isključuje funkcionalnost čišćenja ekrana.
// #define DEBUG
// Uklonite ovu definiciju ako želite da vidite kako izgleda stablo izraza
// pre pojednostavljivanja.
#define POJEDNOSTABLJENJE

/**
 * Mogući rezultati operacija u programu.
 */
typedef enum {
    // Operacija uspešna.
    OK,
    // Ponestalo je memorije tokom operacije.
    OOM,
    // Greška je do programera.
    OOPS,
    // Greška je do korisnika.
    RTFM
} Result;

/**
 * Predstava vrednosti jednog operanda u izrazu.
 */
typedef struct {
    // Da li se promenljiva nalazi u izrazu.
    bool present;
    // Vrednost promenljive.
    double value;
} InputVariable;

/**
 * Struktura stabla korišćena u daljoj implementaciji.
 */
typedef struct tree {
    struct tree *left, *right, *original;
    char value;
} Tree;

/**
 * Struktura čvora steka korišćena u implementaciji steka čvorova stabla.
 */
typedef struct node_tree {
    struct node_tree *next;
    Tree *value;
} NodeTree;

/**
 * Struktura čvora steka korišćena u implementaciji operatorskog steka.
 */
typedef struct node_operator {
    struct node_operator *next;
    char value;
} NodeOperator;

/**
 * Struktura čvora steka korišćena u implementaciji operandskog steka.
 */
typedef struct node_operand {
    struct node_operand *next;
    double value;
} NodeOperand;

/**
 * Struktura čvora ulančane liste za čuvanje stabala.
 */
typedef struct tree_list {
    struct tree_list *next;
    char *label;
    Tree *tree;
} TreeList;

/**
 * Struktura čvora korišćena u implementaciji reda.
 */
typedef struct index_node {
    struct index_node *next;
    Tree *value;
    int index;
} IndexNode;

/**
 * Mogući tipovi sintakse u izrazu.
 */
typedef enum {
    // Jedan od podržanih znakova po propozicijama zadatka.
    OPERATOR,
    // Veliko slovo u nazivu operanda.
    OPERAND,
    // Malo slovo u nazivu funkcije. Na steku isključivo prvo slovo.
    FUNCTION,
    // Otvorena zagrada. Na steku isključivo van konteksta funkcije.
    LEFT_BRACE,
    // Zatvorena zagrada, bilo u kontekstu funkcije ili ne.
    RIGHT_BRACE,
    // Razmaci koji se ignorišu.
    SPACE,
    // Zarez koji razdvaja argumente funkcije.
    ARGUMENT_SEPARATOR,
    // Cifra 0 ili 1, isključivo u nepojednostavljenom stablu.
    CONSTANT,
    // Korisnik je uneo glupost.
    UNKNOWN
} Token;

/**
 * Čišćenje ekrana realizovano korišćenjem VT100 komandi.
 * @see https://www.csie.ntu.edu.tw/~r92094/c++/VT100.html
 */
void clear() {
    #ifndef DEBUG
    printf("%c[2J%c[f", VT100_ESCAPE, VT100_ESCAPE);
    #endif
}

// Definicije potrebne za rad stabala.
Result treeStackPush(NodeTree **stack, Tree *value);
Tree *treeStackPop(NodeTree **stack);

/**
 * Alocira novi čvor stabla.
 * @param {char} value Početna vrednost čvora
 * @returns {Tree*} Novonapravljeni čvor
 */
Tree *getNode(char value) {
    Tree *node = malloc(sizeof(Tree));
    if (node == NULL) {
        return NULL;
    }
    node->left = NULL;
    node->right = NULL;
    node->original = NULL;
    node->value = value;
    return node;
}

/**
 * Dealocira celo stablo iz memorije.
 * @param {Tree*} tree Stablo za dealokaciju
 * @returns {Result} Rezultat operacije
 */
Result freeTree(Tree *tree) {
    if (tree == NULL) {
        return OOPS;
    }
    NodeTree *stack = NULL;
    Tree *currentTree;
    treeStackPush(&stack, tree);
    while (stack != NULL) {
        currentTree = treeStackPop(&stack);
        if (currentTree->left != NULL) {
            treeStackPush(&stack, currentTree->left);
        }
        if (currentTree->right != NULL) {
            treeStackPush(&stack, currentTree->right);
        }
        free(currentTree);
    }
    return OK;
}

/**
 * Oslobađa sva stabla iz memorije.
 * @param {Tree*} Stabla za oslobađanje
 * @returns {Result} Rezultat operacije
 */
Result freeTrees(TreeList *trees) {
    if (trees == NULL) {
        return OOPS;
    }
    TreeList *head = trees->next,
             *treeNode = head,
             *tmp;
    do {
        tmp = treeNode->next;
        freeTree(treeNode->tree);
        free(treeNode->label);
        free(treeNode);
        treeNode = tmp;
    } while (treeNode != head);
    return OK;
}

/**
 * Kopira jedan čvor stabla i postavlja pokazivač na originalni čvor.
 * @param {Tree*} node Čvor koji se kopira
 * @returns {Tree*} Kopirani čvor, ili NULL ukoliko se desila greška
 */
Tree *copyNode(Tree *node) {
    if (node == NULL) {
        return NULL;
    }
    Tree *newNode = getNode(node->value);
    if (newNode == NULL) {
        return NULL;
    }
    newNode->original = node;
    return newNode;
}

/**
 * Kopira celo stablo sa pokazivačima do originalnog stabla u svakom čvoru.
 * @param {Tree*} original Stablo koje se kopira
 * @returns {Tree*} Kopirano stablo, ili NULL ukoliko se desila greška
 */
Tree *copyTree(Tree *original) {
    if (original == NULL) {
        return NULL;
    }
    Tree *newTree = copyNode(original);
    if (newTree == NULL) {
        return NULL;
    }
    NodeTree *stack = NULL;
    Tree *currentNode;
    treeStackPush(&stack, newTree);
    while (stack != NULL) {
        currentNode = treeStackPop(&stack);
        if (currentNode->original->left != NULL) {
            currentNode->left = copyNode(currentNode->original->left);
            if (currentNode->left == NULL) {
                freeTree(newTree);
                while (stack != NULL) {
                    treeStackPop(&stack);
                }
                return NULL;
            }
            treeStackPush(&stack, currentNode->left);
        }
        if (currentNode->original->right != NULL) {
            currentNode->right = copyNode(currentNode->original->right);
            if (currentNode->right == NULL) {
                freeTree(newTree);
                while (stack != NULL) {
                    treeStackPop(&stack);
                }
                return NULL;
            }
            treeStackPush(&stack, currentNode->right);
        }
    }
    return newTree;
}

/**
 * Dodaje stablo u ulančanu listu stabala.
 * @param {TreeList**} trees Ulančana lista stabala
 * @param {Tree*} tree Stablo za dodavanje u ulančanu listu
 * @param {char*} label Oznaka za stablo u meniju za biranje stabla
 * @returns {Result} Uspešnost operacije
 */
Result addTree(TreeList **trees, Tree *tree, char *label) {
    if (trees == NULL) {
        return OOPS;
    }
    TreeList *newTree = malloc(sizeof(TreeList));
    if (newTree == NULL) {
        return OOM;
    }
    newTree->tree = tree;
    newTree->label = label;
    if ((*trees) == NULL) {
        *trees = newTree;
        (*trees)->next = newTree;
    } else {
        newTree->next = (*trees)->next;
        (*trees)->next = newTree;
        *trees = (*trees)->next;
    }
    return OK;
}

/**
 * Proverava da li se čvor sa nekom oznakom nalazi u stablu.
 * @param {Tree*} tree Stablo koje se proverava
 * @param {char} node Oznaka čvora koja se traži
 * @returns {bool} Da li se čvor sa datom oznakom nalazi u stablu
 */
bool containsNode(Tree *tree, char node) {
    if (tree == NULL) {
        return false;
    }
    NodeTree *stack = NULL;
    Tree *currentNode;
    treeStackPush(&stack, tree);
    while (stack != NULL) {
        currentNode = treeStackPop(&stack);
        if (currentNode->value == node) {
            while (stack != NULL) {
                treeStackPop(&stack);
            }
            return true;
        }
        if (currentNode->left != NULL) {
            treeStackPush(&stack, currentNode->left);
        }
        if (currentNode->right != NULL) {
            treeStackPush(&stack, currentNode->right);
        }
    }
    return false;
}

/**
 * Guranje čvora stabla na stek.
 * @param {NodeTree**} stack Stek na koji se gura čvor
 * @param {Tree*} value Čvor stabla koji se gura
 * @returns {Result} Uspešnost operacije
 */
Result treeStackPush(NodeTree **stack, Tree *value) {
    if (stack == NULL) {
        return OOPS;
    }
    NodeTree *newNode = malloc(sizeof(NodeTree));
    if (newNode == NULL) {
        return OOM;
    }
    newNode->value = value;
    if ((*stack) == NULL) {
        *stack = newNode;
        (*stack)->next = NULL;
    } else {
        newNode->next = *stack;
        *stack = newNode;
    }
    return OK;
}

/**
 * Izbacivanje poslednjeg čvora stabla sa steka.
 * @param {NodeTree**} stack Stek sa kojeg se izbacuje čvor stabla
 * @returns {Tree*} Poslednji čvor sa steka, ili NULL ako se desila greška
 */
Tree *treeStackPop(NodeTree **stack) {
    if (stack == NULL || *stack == NULL) {
        return NULL;
    }
    NodeTree *stackTop = *stack;
    Tree *returnValue = stackTop->value;
    *stack = (*stack)->next;
    free(stackTop);
    return returnValue;
}

/**
 * Guranje operatora na stek.
 * @param {NodeOperator**} stack Stek na koji se gura operator
 * @param {char} value Oznaka operatora koji se gura
 * @returns {Result} Uspešnost operacije
 */
Result operatorStackPush(NodeOperator **stack, char value) {
    if (stack == NULL) {
        return OOPS;
    }
    NodeOperator *newNode = malloc(sizeof(NodeOperator));
    if (newNode == NULL) {
        return OOM;
    }
    newNode->value = value;
    if ((*stack) == NULL) {
        *stack = newNode;
        (*stack)->next = NULL;
    } else {
        newNode->next = *stack;
        *stack = newNode;
    }
    return OK;
}

/**
 * Izbacivanje poslednjeg operatora sa steka.
 * @param {NodeOperator**} stack Stek sa kojeg se izbacuje operator
 * @returns {char} Poslednji operator sa steka, ili \0 ako se desila greška
 */
char operatorStackPop(NodeOperator **stack) {
    if (stack == NULL || *stack == NULL) {
        return '\0';
    }
    NodeOperator *stackTop = *stack;
    char returnValue = stackTop->value;
    *stack = (*stack)->next;
    free(stackTop);
    return returnValue;
}

/**
 * Guranje operanda na stek.
 * @param {NodeOperand**} stack Stek na koji se gura operand
 * @param {double} value Vrednost operanda koja se gura
 * @returns {Result} Uspešnost operacije
 */
Result operandStackPush(NodeOperand **stack, double value) {
    if (stack == NULL) {
        return OOPS;
    }
    NodeOperand *newNode = malloc(sizeof(NodeOperand));
    if (newNode == NULL) {
        return OOM;
    }
    newNode->value = value;
    if ((*stack) == NULL) {
        *stack = newNode;
        (*stack)->next = NULL;
    } else {
        newNode->next = *stack;
        *stack = newNode;
    }
    return OK;
}

/**
 * Izbacivanje poslednjeg operanda sa steka.
 * @param {NodeOperand**} stack Stek sa kojeg se izbacuje operand
 * @returns {double} Poslednji operand sa steka, ili -1 ako se desila greška
 */
double operandStackPop(NodeOperand **stack) {
    if (stack == NULL || *stack == NULL) {
        return -1;
    }
    NodeOperand *stackTop = *stack;
    double returnValue = stackTop->value;
    *stack = (*stack)->next;
    free(stackTop);
    return returnValue;
}

/**
 * Ubacuje čvor i njegov indeks u punom stablu u red.
 * @param {IndexNode**} head Strana reda na koju se ubacuju čvorovi
 * @param {IndexNode**} tail Strana reda sa koje se izbacuju čvorovi
 * @param {Tree*} value Čvor koji se ubacuje u red
 * @param {int} index Indeks čvora u punom stablu
 * @returns {Result} Uspešnost operacije
 */
Result indexQueuePush(IndexNode **head, IndexNode **tail, Tree *value, int index) {
    if (
        head == NULL ||
        tail == NULL ||
        ((*head) == NULL && (*tail) != NULL) ||
        ((*tail) == NULL && (*head) != NULL)
    ) {
        return OOPS;
    }
    IndexNode *newNode = malloc(sizeof(IndexNode));
    if (newNode == NULL) {
        return OOM;
    }
    newNode->value = value;
    newNode->index = index;
    newNode->next = NULL;
    if ((*head) == NULL) {
        *head = newNode;
        *tail = newNode;
    } else {
        (*head)->next = newNode;
        *head = (*head)->next;
    }
    return OK;
}

/**
 * Izbacuje čvor i njegov indeks u punom stablu iz reda.
 * NAPOMENA: Dealokacija ovog čvora se ostavlja korisniku!
 * @param {IndexNode**} head Strana reda na koju se ubacuju čvorovi
 * @param {IndexNode**} tail Strana reda sa koje se izbacuju čvorovi
 * @returns {IndexNode*} Struktura sa čvorom i njegovim indeksom
 */
IndexNode *indexQueuePop(IndexNode **head, IndexNode **tail) {
    if (head == NULL || tail == NULL || (*head) == NULL || (*tail) == NULL) {
        return NULL;
    }
    IndexNode *returnValue = (*tail);
    *tail = (*tail)->next;
    if ((*tail) == NULL) {
        *head = NULL;
    }
    // Oslobađanje se ostavlja korisniku!
    return returnValue;
}

/**
 * Vraća tip sintakse nekog karaktera.
 * @param {char} input Karakter čiji se tip sintakse proverava
 * @returns {Token} Tip sintakse karaktera
 */
Token getToken(char input) {
    switch (input) {
        case ' ': return SPACE;
        case '(': return LEFT_BRACE;
        case ')': return RIGHT_BRACE;
        case ',': return ARGUMENT_SEPARATOR;
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
        // Specijalni karakter za unarni minus.
        case '_':
            return OPERATOR;
        // Podržane su samo konstante 0 i 1 i to isključivo prilikom
        // pojednostabljenja.
        case '0':
        case '1':
            return CONSTANT;
        default:
            if (input >= 'A' && input <= 'Z') {
                return OPERAND;
            }
            if (input >= '0' && input <= '9') {
                return CONSTANT;
            }
            if (input >= 'a' && input <= 'z') {
                return FUNCTION;
            }
            return UNKNOWN;
    }
}

/**
 * Dobavljanje ulaznog prioriteta operatora.
 * @param {char} operator Operator za koji se proverava ulazni prioritet
 * @returns {int} Ulazni prioritet operatora
 */
int inputPriority(char operator) {
    switch (operator) {
        case ')':
            return 1;
        case '+':
        case '-':
            return 2;
        case '*':
        case '/':
            return 3;
        case '^':
            return 5;
        case 'l':
        case 't':
        case 'm':
        case 's':
        case 'c':
        case '_':
        case ',':
        case '(':
            return 6;
        default:
            return -1;
    }
}

/**
 * Dobavljanje stek prioriteta operatora.
 * @param {char} operator Operator za koji se proverava stek prioritet
 * @returns {int} Stek prioritet operatora
 */
int stackPriority(char operator) {
    switch (operator) {
        case '(':
        case 'l':
        case 't':
        case 'm':
        case 's':
        case 'c':
        case '_':
            return 0;
        case '^':
            return 4;
        default:
            return inputPriority(operator);
    }
}

/**
 * Prebacivanje operatora sa steka operatora u stablo.
 * @param {NodeTree**} treeStack Pokazivač na stek iz kojeg se formira stablo
 * @param {NodeOperator**} operatorStack Pokazivač na stek operatora
 * @returns {Result} Uspešnost operacije
 */
Result moveLastOperator(NodeTree **treeStack, NodeOperator **operatorStack) {
    char operator = operatorStackPop(operatorStack);
    Tree *newNode = getNode(operator);
    switch (operator) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
        case 'm':
            newNode->right = treeStackPop(treeStack);
            newNode->left = treeStackPop(treeStack);
            break;
        case '_':
        case 'l':
        case 't':
        case 's':
        case 'c':
            newNode->left = treeStackPop(treeStack);
            break;
        default:
            // Uhh nešto smo zeznuli.
            return OOPS;
    }
    treeStackPush(treeStack, newNode);
    return OK;
}

/**
 * Unos izraza i pretvaranje u stablo.
 * Po propozicijama zadatka, smatra se da je uneti izraz validan.
 * Podržane funkcije su prirodni logaritam (ln), tangens (tg/tan), minimum sa
 * dva parametra (min), sinus (sin) i kosinus (cos).
 * @param {InputVariable[]} variables Podaci o svim mogućim promenljivama
 * @returns {Tree*} Napravljeno stablo, ili NULL ako se desila greška.
 */
Tree *inputExpression(InputVariable variables[26]) {
    char c, prev = '\0';
    Token token, prevToken = UNKNOWN, tempToken;
    NodeTree *treeStack = NULL;
    NodeOperator *operatorStack = NULL;
    Tree *returnValue;
    printf("Unesite izraz: ");
    while ((c = getchar()) != '\n') {
        token = getToken(c);
        switch (token) {
            case OPERAND:
                treeStackPush(&treeStack, getNode(c));
                variables[c - 'A'].present = true;
                break;
            case OPERATOR:
                if (prev == '(' && c == '-') {
                    // Unarno minus.
                    c = '_';
                }
                while (
                    operatorStack != NULL &&
                    inputPriority(c) <= stackPriority(operatorStack->value)
                ) {
                    moveLastOperator(&treeStack, &operatorStack);
                }
                operatorStackPush(&operatorStack, c);
                break;
            case FUNCTION:
                // Funkcije identifikujemo po njihovom prvom karakteru
                // ln -> l, tg -> t, min -> m, s -> sin, c -> cos
                // i stoga preskačemo sve dalje karaktere u imenu funkcije
                if (prevToken == FUNCTION) {
                    continue;
                }
                break;
            case LEFT_BRACE:
                if (prevToken == FUNCTION) {
                    operatorStackPush(&operatorStack, prev);
                } else {
                    operatorStackPush(&operatorStack, '(');
                }
                break;
            case RIGHT_BRACE:
                while (operatorStack != NULL) {
                    tempToken = getToken(operatorStack->value);
                    if (tempToken == FUNCTION || tempToken == LEFT_BRACE) {
                        break;
                    }
                    moveLastOperator(&treeStack, &operatorStack);
                }
                if (tempToken == FUNCTION) {
                    moveLastOperator(&treeStack, &operatorStack);
                } else {
                    operatorStackPop(&operatorStack);
                }
                break;
            case ARGUMENT_SEPARATOR:
                while (
                    operatorStack != NULL &&
                    getToken(operatorStack->value) != FUNCTION
                ) {
                    moveLastOperator(&treeStack, &operatorStack);
                }
                break;
            case SPACE:
                // Namerno ne postavljamo prethodni karakter.
                continue;
            case CONSTANT:
            case UNKNOWN:
            default:
                printf("%c nije validan karakter.\n", c);
                while (treeStack != NULL) {
                    treeStackPop(&treeStack);
                }
                while (operatorStack != NULL) {
                    operatorStackPop(&operatorStack);
                }
                return NULL;
        }
        prev = c;
        prevToken = token;
    }
    while (operatorStack != NULL) {
        moveLastOperator(&treeStack, &operatorStack);
    }
    returnValue = treeStackPop(&treeStack);
    if (treeStack != NULL) {
        printf(
            "Desila se nepoznata greška prilikom parsiranja izraza. Proverite "
            "da li je uneseni izraz ispravan po propozicijama zadatka.\n"
        );
        while (treeStack != NULL) {
            treeStackPop(&treeStack);
        }
        return NULL;
    }
    return returnValue;
}

/**
 * Manipuliše prostorno-vremenskim kontinuumom tako da se u određenom
 * vremenskom periodu određen prostor kontinualno pojavi na ekranu korisnika
 * u vidu karaktera.
 * @param {FILE*} file Datoteka nad kojom se vrši gorepomenuta magija.
 * @param {char*} space Prostor koji se pojavljuje na ekranu
 * @param {int} time Dužina vremenskom intervala tokom kojeg se prostor
 *                   pojavljuje na ekranu u femtogodinama.
 */
void spacetime(FILE *file, char *space, int time) {
    for (int i = 0; i < time; ++i) {
        fprintf(file, space);
    }
}

/**
 * Ispisuje matematički smislen naziv za vrednost čvora.
 * @param {char} internal Interni naziv za operator/funkciju
 */
void printExternal(char internal) {
    switch (internal) {
        case 'l':
            printf("ln");
            break;
        case 'm':
            printf("min");
            break;
        case 't':
            printf("tg");
            break;
        case 's':
            printf("sin");
            break;
        case 'c':
            printf("cos");
            break;
        case '_':
            printf("-");
            break;
        default:
            printf("%c", internal);
            break;
    }
}

/**
 * Dozvoljava korisniku biranje stabla nad kojim će se izvršavati sledeća
 * operacija. Ako u kolekciji stabala postoji samo jedno stablo, meni za
 * biranje stable se ne prikazuje.
 * @param {TreeList**} trees Naša kolekcija stabala
 * @param {const char*} reason Razlog za biranje stabla
 * @returns {Tree*} Izabrano stablo, ili NULL ako pokazivači nisu validni
 */
Tree *chooseTree(TreeList **trees, const char *reason) {
    if (trees == NULL || (*trees) == NULL || (*trees)->next == NULL) {
        return NULL;
    }
    if ((*trees) == (*trees)->next) {
        return (*trees)->tree;
    }
    printf("Izaberite stablo %s:\n", reason);
    int option, length = 0;
    TreeList *currentNode = (*trees)->next,
             *returnTree = *trees;
    do {
        ++length;
        printf("[%d] %s\n", length, currentNode->label);
        currentNode = currentNode->next;
    } while (currentNode != (*trees)->next);
    currentNode = *trees;
    while (true) {
        scanf("%d", &option);
        if (option < 1 || option > length) {
            printf("Nije izabrano validno stablo.");
        } else {
            break;
        }
    }
    clear();
    while (option--) {
        returnTree = returnTree->next;
    }
    return returnTree->tree;
}

/**
 * Ubacuje sve čvorove prosleđenog stabla u stek tako da se čvorovi iz tog
 * steka izbacuju u postorder poretku.
 * @param {Tree*} tree Stablo koje bi trebalo da se čita u postorder poretku
 * @returns {NodeTree*} Stek koji se može iščitati u postorder poretku
 */
NodeTree *getPostorderStack(Tree *tree) {
    NodeTree *returnValue = NULL,
             *treeStack = NULL;
    Tree *next;
    treeStackPush(&treeStack, tree);
    while (treeStack != NULL) {
        next = treeStackPop(&treeStack);
        treeStackPush(&returnValue, next);
        if (next->left != NULL) {
            treeStackPush(&treeStack, next->left);
        }
        if (next->right != NULL) {
            treeStackPush(&treeStack, next->right);
        }
    }
    return returnValue;
}

/**
 * Dinamička alokacija unesenog teksta.
 * @param {char**} str Pokazivač na tekst koji se unosi
 * @returns {int} Dužina teksta, ili -1 ukoliko se desila greška
 */
int getString(char **str) {
    *str = malloc(sizeof(char));
    if (*str == NULL) {
        return -1;
    }
    **str = '\0';
    char input;
    int strSize = 0;
    while ((input = getchar()) == '\n');
    do {
        *((*str) + strSize) = input;
        ++strSize;
        *str = realloc(*str, (strSize + 1) * sizeof(char));
        if (*str == NULL) {
            return -1;
        }
        *((*str) + strSize) = '\0';
    } while ((input = getchar()) != '\n');
    return strSize;
}

/**
 * Ispisuje izgled formiranog stabla.
 * @param {TreeList**} trees Sva trenutno sačuvana stabla
 * @param {InputVariable[]} variables Podaci o svim promenljivama (nekorišćeno)
 * @returns {Result} Rezultat operacije
 */
Result printTree(TreeList **trees, InputVariable variables[26]) {
    // Nekorišćene promenljive.
    (void) variables;
    Tree *tree = chooseTree(trees, "za ispisivanje");
    IndexNode *levelOrderQueueTail = NULL,
              *levelOrderQueueHead = NULL;
    // Level-order obilazak radi utvrđivanja dubine stabla.
    int maxLevel = 0;
    indexQueuePush(&levelOrderQueueHead, &levelOrderQueueTail, tree, 1);
    while (levelOrderQueueHead != NULL) {
        IndexNode *currentNode = indexQueuePop(
            &levelOrderQueueHead,
            &levelOrderQueueTail
        );
        if (currentNode->index > maxLevel) {
            maxLevel = currentNode->index;
        }
        if (currentNode->value->left != NULL) {
            indexQueuePush(
                &levelOrderQueueHead,
                &levelOrderQueueTail,
                currentNode->value->left,
                currentNode->index + 1
            );
        }
        if (currentNode->value->right != NULL) {
            indexQueuePush(
                &levelOrderQueueHead,
                &levelOrderQueueTail,
                currentNode->value->right,
                currentNode->index + 1
            );
        }
        free(currentNode);
    }
    // Potencijalno ispisivanje u datoteku.
    long long width = (1 << maxLevel) + 1;
    char isFileInput, *fileName;
    FILE *file = stdout;
    if (maxLevel > 6) {
        printf(
            "Ispis stabla zauzima širinu od %lld karaktera. Da li želite da "
            "ga ispišete u datoteku umesto na standardni izlaz? [d/n]: ",
            width
        );
        scanf(" %c", &isFileInput);
        if (isFileInput == 'd') {
            printf("Unesite naziv datoteke: ");
            if (getString(&fileName) == -1) {
                return OOM;
            }
            file = fopen(fileName, "w");
            free(fileName);
            if (file == NULL) {
                printf("Desila se greška prilikom otvaranja datoteke.\n");
                return RTFM;
            }
        }
    }
    // Formiranje punog stabla od trenutnog stabla.
    long long fullTreeNodeNumber = width - 2;
    Tree **fullTree = malloc(fullTreeNodeNumber * sizeof(Tree*));
    if (fullTree == NULL) {
        return OOM;
    }
    for (long long i = 0; i < fullTreeNodeNumber; ++i) {
        *(fullTree + i) = NULL;
    }
    // Populacija punog stabla pokazivačima na čvorove level-order obilaskom.
    indexQueuePush(&levelOrderQueueHead, &levelOrderQueueTail, tree, 1);
    while (levelOrderQueueHead != NULL) {
        IndexNode *currentNode = indexQueuePop(
            &levelOrderQueueHead,
            &levelOrderQueueTail
        );
        *(fullTree + currentNode->index - 1) = currentNode->value;
        if (currentNode->value->left != NULL) {
            indexQueuePush(
                &levelOrderQueueHead,
                &levelOrderQueueTail,
                currentNode->value->left,
                currentNode->index * 2
            );
        }
        if (currentNode->value->right != NULL) {
            indexQueuePush(
                &levelOrderQueueHead,
                &levelOrderQueueTail,
                currentNode->value->right,
                currentNode->index * 2 + 1
            );
        }
        free(currentNode);
    }
    // Ispisivanje punog stabla.
    int currentLevelNodes = 1,
        index1 = 0,
        index2 = 0,
        baseSpace = pow(2, maxLevel) - 1;
    char currValue;
    printf(
        "Napomena: Zbog preglednosti stabla, funkcije se ispisuju sa "
        "svojim prvim slovom umesto celim imenom.\n"
    );
    for (int i = 0; i < maxLevel; ++i) {
        // Ispisivanje čvorova.
        for (int j = 0; j < currentLevelNodes; ++j) {
            if (j == 0) {
                spacetime(file, " ", baseSpace / 2);
            } else {
                spacetime(file, " ", baseSpace);
            }
            if (*(fullTree + index1) == NULL) {
                fprintf(file, " ");
            } else {
                currValue = (*(fullTree + index1))->value;
                fprintf(file, "%c", currValue == '_' ? '-' : currValue);
            }
            ++index1;
        }
        baseSpace /= 2;
        fprintf(file, "\n");
        // Ispisivanje strelica.
        if (i != maxLevel - 1) {
            for (int j = 0; j < currentLevelNodes; ++j) {
                bool exists = *(fullTree + index2) != NULL,
                     leftChildExists = false,
                     rightChildExists = false;
                if (exists) {
                    if ((*(fullTree + index2))->left != NULL) {
                        leftChildExists = true;
                    }
                    if ((*(fullTree + index2))->right != NULL) {
                        rightChildExists = true;
                    }
                }
                if (leftChildExists) {
                    spacetime(file, " ", baseSpace / 2);
                    fprintf(file, "┌");
                    spacetime(file, "─", baseSpace / 2);
                } else {
                    spacetime(file, " ", baseSpace);
                }
                if (leftChildExists && rightChildExists) {
                    fprintf(file, "┴");
                } else if (leftChildExists) {
                    fprintf(file, "┘");
                } else if (rightChildExists) {
                    fprintf(file, "└");
                } else {
                    fprintf(file, " ");
                }
                if (rightChildExists) {
                    spacetime(file, "─", baseSpace / 2);
                    fprintf(file, "┐");
                    spacetime(file, " ", baseSpace / 2);
                } else {
                    spacetime(file, " ", baseSpace);
                }
                fprintf(file, " ");
                ++index2;
            }
            fprintf(file, "\n");
        }
        currentLevelNodes *= 2;
    }
    free(fullTree);
    return OK;
}

/**
 * Ispisuje uneti izraz u postfiksnoj notaciji.
 * @param {TreeList**} trees Sva trenutno sačuvana stabla
 * @param {InputVariable[]} variables Podaci o svim promenljivama (nekorišćeno)
 * @returns {Result} Rezultat operacije
 */
Result printPostfix(TreeList **trees, InputVariable variables[26]) {
    // Nekorišćene promenljive.
    (void) variables;
    NodeTree *postorderStack = getPostorderStack(
        chooseTree(trees, "koje predstavlja izraz za ispisivanje")
    );
    while (postorderStack != NULL) {
        printExternal(treeStackPop(&postorderStack)->value);
        printf(" ");
    }
    printf("\n");
    return OK;
}

/**
 * Radi računanje za calculateExpression.
 * @param {Tree*} tree Stablo koje se računa
 * @param {InputVariable[]} variables Promenljive u izrazu
 * @param {double*} output Rezultat računanja
 * @param {bool} original Da li se računa originalno stablo ili izvedeno
 * @returns {Result} Uspešnost operacije
 */
Result calculateExpressionInner(Tree *tree, InputVariable variables[26], double *output, bool original) {
    NodeOperand *operandStack = NULL;
    NodeTree *postorderStack = getPostorderStack(tree);
    double firstOperand, secondOperand, thirdOperand, fourthOperand, result;
    char value;
    while (postorderStack != NULL) {
        value = treeStackPop(&postorderStack)->value;
        switch (value) {
            case '+':
                operandStackPush(
                    &operandStack,
                    operandStackPop(&operandStack) +
                    operandStackPop(&operandStack)
                );
                break;
            case '-':
                secondOperand = operandStackPop(&operandStack);
                firstOperand = operandStackPop(&operandStack);
                operandStackPush(
                    &operandStack,
                    firstOperand - secondOperand
                );
                break;
            case '*':
                operandStackPush(
                    &operandStack,
                    operandStackPop(&operandStack) *
                    operandStackPop(&operandStack)
                );
                break;
            case '/':
                secondOperand = operandStackPop(&operandStack);
                firstOperand = operandStackPop(&operandStack);
                if (secondOperand == 0) {
                    while (postorderStack != NULL) {
                        treeStackPop(&postorderStack);
                    }
                    while (operandStack != NULL) {
                        operandStackPop(&operandStack);
                    }
                    printf("Drugi operand deljenja ne sme biti nula.\n");
                    return RTFM;
                }
                operandStackPush(
                    &operandStack,
                    firstOperand / secondOperand
                );
                break;
            case '^':
                // TODO: Možda ne koristiti pow?
                secondOperand = operandStackPop(&operandStack);
                firstOperand = operandStackPop(&operandStack);
                operandStackPush(
                    &operandStack,
                    pow(firstOperand, secondOperand)
                );
                break;
            case '_':
                operandStackPush(
                    &operandStack,
                    -operandStackPop(&operandStack)
                );
                break;
            case 'l':
                firstOperand = operandStackPop(&operandStack);
                if (firstOperand <= 0) {
                    while (postorderStack != NULL) {
                        treeStackPop(&postorderStack);
                    }
                    while (operandStack != NULL) {
                        operandStackPop(&operandStack);
                    }
                    printf(
                        "Prvi operand logaritma ne sme biti manji ili jednak "
                        "nuli.\n"
                    );
                    return RTFM;
                }
                operandStackPush(&operandStack, log(firstOperand));
                break;
            case 't':
                // TODO: Provera domena.
                operandStackPush(
                    &operandStack,
                    tan(operandStackPop(&operandStack))
                );
                break;
            case 'm':
                // U originalnom stablu ovde ima dva operanda, u prvom izvodu
                // četiri a u ostalima ne postoji.
                if (original) {
                    secondOperand = operandStackPop(&operandStack);
                    firstOperand = operandStackPop(&operandStack);
                    operandStackPush(
                        &operandStack,
                        firstOperand <= secondOperand ?
                            firstOperand :
                            secondOperand
                    );
                } else {
                    fourthOperand = operandStackPop(&operandStack);
                    thirdOperand = operandStackPop(&operandStack);
                    secondOperand = operandStackPop(&operandStack);
                    firstOperand = operandStackPop(&operandStack);
                    operandStackPush(
                        &operandStack,
                        firstOperand <= secondOperand ?
                            thirdOperand :
                            fourthOperand
                    );
                }
                break;
            case 's':
                // TODO: Provera domena.
                operandStackPush(
                    &operandStack,
                    sin(operandStackPop(&operandStack))
                );
                break;
            case 'c':
                // TODO: Provera domena.
                operandStackPush(
                    &operandStack,
                    cos(operandStackPop(&operandStack))
                );
                break;
            case '?':
                // Nije pravi operator.
                break;
            default:
                if (value >= 'A' && value <= 'Z') {
                    operandStackPush(
                        &operandStack,
                        variables[value - 'A'].value
                    );
                } else if (value == '0' || value == '1') {
                    operandStackPush(&operandStack, value - '0');
                } else {
                    // ???
                    while (postorderStack != NULL) {
                        treeStackPop(&postorderStack);
                    }
                    while (operandStack != NULL) {
                        operandStackPop(&operandStack);
                    }
                    return OOPS;
                }
        }
    }
    result = operandStackPop(&operandStack);
    if (operandStack != NULL) {
        while (operandStack != NULL) {
            operandStackPop(&operandStack);
        }
        return OOPS;
    }
    *output = result;
    return OK;
}

/**
 * Računa vrednost izraza.
 * @param {TreeList**} trees Sva trenutno sačuvana stabla
 * @param {InputVariable[]} variables Podaci o svim promenljivama
 * @returns {Result} Rezultat operacije
 */
Result calculateExpression(TreeList **trees, InputVariable variables[26]) {
    for (int i = 0; i < 26; ++i) {
        if (variables[i].present) {
            printf("Unesite vrednost promenljive %c: ", 'A' + i);
            scanf("%lf", &variables[i].value);
        }
    }
    TreeList *originalTree = *trees;
    do {
        originalTree = originalTree->next;
    } while (originalTree->next != (*trees));
    Tree *tree = chooseTree(trees, "koje predstavlja izraz za izračunavanje");
    double output;
    Result result = calculateExpressionInner(
        tree,
        variables,
        &output,
        originalTree->tree == tree
    );
    if (result != OK) {
        return result;
    }
    printf("Rezultat: %lf\n", output);
    return OK;
}

#ifdef POJEDNOSTABLJENJE
/**
 * Pojednostavljuje stablo (pojednostabljuje) dobijeno diferenciranjem.
 * Uglavnom vodi računa samo o izbacivanju konstanti 1 i 0 gde je to moguće.
 * Izvršava se samo ako je makro POJEDNOSTABLJENJE definisan.
 * @param {Tree*} tree Stablo za pojednostavljivanje
 */
void pojednostabljenje(Tree *tree) {
    NodeTree *postorderStack = getPostorderStack(tree);
    Tree *next, *tmp;
    while (postorderStack != NULL) {
        next = treeStackPop(&postorderStack);
        switch (next->value) {
            case '+':
                if (next->left->value == '0') {
                    // 0+X = X
                    freeTree(next->left);
                    tmp = next->right;
                    next->left = tmp->left;
                    next->right = tmp->right;
                    next->value = tmp->value;
                    free(tmp);
                } else if (next->right->value == '0') {
                    // X+0 = X
                    freeTree(next->right);
                    tmp = next->left;
                    next->left = tmp->left;
                    next->right = tmp->right;
                    next->value = tmp->value;
                    free(tmp);
                }
                break;
            case '-':
                if (next->left->value == '0' && next->right->value == '0') {
                    // 0-0 = 0
                    freeTree(next->left);
                    freeTree(next->right);
                    next->left = NULL;
                    next->right = NULL;
                    next->value = '0';
                } else if (next->left->value == '0') {
                    // 0-X = -X
                    freeTree(next->left);
                    next->left = next->right;
                    next->value = '_';
                    next->right = NULL;
                } else if (next->right->value == '0') {
                    // X-0 = X
                    freeTree(next->right);
                    tmp = next->left;
                    next->left = tmp->left;
                    next->right = tmp->right;
                    next->value = tmp->value;
                    free(tmp);
                }
                break;
            case '*':
                if (next->left->value == '0' || next->right->value == '0') {
                    // X*0 ili 0*X = 0
                    freeTree(next->left);
                    freeTree(next->right);
                    next->left = NULL;
                    next->right = NULL;
                    next->value = '0';
                } else if (next->left->value == '1') {
                    // 1*X = X
                    freeTree(next->left);
                    tmp = next->right;
                    next->left = tmp->left;
                    next->right = tmp->right;
                    next->value = tmp->value;
                    free(tmp);
                } else if (next->right->value == '1') {
                    // X*1 = X
                    freeTree(next->right);
                    tmp = next->left;
                    next->left = tmp->left;
                    next->right = tmp->right;
                    next->value = tmp->value;
                    free(tmp);
                }
                break;
            case '/':
                if (next->left->value == '0') {
                    // 0/X = 0
                    freeTree(next->left);
                    freeTree(next->right);
                    next->left = NULL;
                    next->right = NULL;
                    next->value = '0';
                } else if (next->right->value == '1') {
                    // X/1 = X
                    freeTree(next->right);
                    tmp = next->left;
                    next->left = tmp->left;
                    next->right = tmp->right;
                    next->value = tmp->value;
                    free(tmp);
                }
                break;
            case '^':
                if (next->left->value == '0') {
                    // 0^X = 0
                    freeTree(next->left);
                    freeTree(next->right);
                    next->left = NULL;
                    next->right = NULL;
                    next->value = '0';
                } else if (next->left->value == '1') {
                    // 1^X = 1
                    freeTree(next->left);
                    freeTree(next->right);
                    next->left = NULL;
                    next->right = NULL;
                    next->value = '1';
                } else if (next->right->value == '0') {
                    // X^0 = 1
                    freeTree(next->left);
                    freeTree(next->right);
                    next->left = NULL;
                    next->right = NULL;
                    next->value = '1';
                } else if (next->right->value == '1') {
                    // X^1 = X
                    freeTree(next->right);
                    tmp = next->left;
                    next->left = tmp->left;
                    next->right = tmp->right;
                    next->value = tmp->value;
                    free(tmp);
                }
                break;
            case '_':
                if (next->left->value == '0') {
                    // -0 = 0
                    freeTree(next->left);
                    next->left = NULL;
                    next->value = '0';
                }
                break;
            case 'l':
                if (next->left->value == '1') {
                    // ln(1) = 0
                    freeTree(next->left);
                    next->left = NULL;
                    next->value = '0';
                }
                break;
            case 's':
            case 't':
                if (next->left->value == '0') {
                    // sin(0) = 0, tg(0) = 0
                    freeTree(next->left);
                    next->left = NULL;
                    next->value = '0';
                }
                break;
            case 'c':
                if (next->left->value == '0') {
                    // cos(0) = 1
                    freeTree(next->left);
                    next->left = NULL;
                    next->value = '1';
                }
                break;
            case 'm':
            case '?':
            default:
                // Nemamo šta da pojednostablimo.
                break;
        }
    }
}
#endif

/**
 * Diferencira izraz po zadatoj promenljivoj.
 * @param {TreeList**} trees Sva trenutno sačuvana stabla
 * @param {InputVariable[]} variables Podaci o svim promenljivama (nekorišćeno)
 * @returns {Result} Rezultat operacije
 */
Result differentiate(TreeList **trees, InputVariable variables[26]) {
    Tree *tree = chooseTree(trees, "koje predstavlja izraz za diferenciranje"),
         *differentialTree = copyTree(tree);
    TreeList *originalTree = *trees;
    do {
        originalTree = originalTree->next;
    } while (originalTree->next != (*trees));
    printf(
        "Unesite oznaku diferenciranog stabla kako biste mogli da izaberete "
        "ovo stablo u ostalim opcijama u meniju kasnije: "
    );
    char *label, input;
    if (getString(&label) == -1) {
        freeTree(differentialTree);
        return OOM;
    }
    while (true) {
        printf("Unesite promenljivu po kojoj se diferencira: ");
        scanf(" %c", &input);
        if (input < 'A' || input > 'Z') {
            printf("Nije unet validan naziv promenljive.\n");
        } else if (!variables[input - 'A'].present) {
            printf("Uneta promenljiva se ne nalazi u izrazu.\n");
        } else {
            break;
        }
    }
    // Postorder obilazak stabla prilikom diferenciranja.
    NodeTree *postorderStack = getPostorderStack(differentialTree);
    Tree *next, *tmpLeft, *tmpRight;
    bool alreadyRead = false;
    while (postorderStack != NULL) {
        next = treeStackPop(&postorderStack);
        switch (next->value) {
            case '+':
            case '-':
                // Leva i desna strana su već diferencirani.
            case '_':
                // Levi operand je već diferenciran.
            case '?':
                // Ovo nije operator.
                break;
            case '*':
                // (A*B)' = A'B + AB'
                next->value = '+';
                tmpLeft = next->left;
                tmpRight = next->right;
                next->left = getNode('*');
                next->right = getNode('*');
                next->left->left = tmpLeft;
                next->left->right = copyTree(tmpRight->original);
                next->right->left = copyTree(tmpLeft->original);
                next->right->right = tmpRight;
                break;
            case '/':
                // (A/B)' = (A'B - AB')/(B*B)
                tmpLeft = next->left;
                tmpRight = next->right;
                next->left = getNode('-');
                next->right = getNode('*');
                next->left->left = getNode('*');
                next->left->right = getNode('*');
                next->left->left->left = tmpLeft;
                next->left->left->right = copyTree(tmpRight->original);
                next->left->right->left = copyTree(tmpLeft->original);
                next->left->right->right = tmpRight;
                next->right->left = copyTree(tmpRight->original);
                next->right->right = copyTree(tmpRight->original);
                break;
            case '^':
                // Po propozicijama zadatka, mogući slučajevi su X^a, a^X i a^a
                if (containsNode(next->left->original, input)) {
                    // (X^a)' = a * X^(a-1) * X'
                    tmpRight = next->right->original;
                    freeTree(next->right);
                    next->right = next->left;
                    next->value = '*';
                    next->left = getNode('*');
                    next->left->left = copyTree(tmpRight);
                    next->left->right = getNode('^');
                    next->left->right->left = copyTree(next->right->original);
                    next->left->right->right = getNode('-');
                    next->left->right->right->left = copyTree(tmpRight);
                    next->left->right->right->right = getNode('1');
                } else if (containsNode(next->right->original, input)) {
                    // (a^X)' = a^X * ln(a) * X'
                    tmpLeft = next->left->original;
                    tmpRight = next->right;
                    freeTree(next->left);
                    next->value = '*';
                    next->left = getNode('^');
                    next->right = getNode('*');
                    next->left->left = copyTree(tmpLeft);
                    next->left->right = copyTree(tmpRight->original);
                    next->right->left = getNode('l');
                    next->right->left->left = copyTree(tmpLeft);
                    next->right->right = tmpRight;
                } else {
                    // (a^a)' = 0
                    freeTree(next->left);
                    freeTree(next->right);
                    next->value = '0';
                    next->left = NULL;
                    next->right = NULL;
                }
                break;
            case 'l':
                // (ln(X))' = 1/X * X'
                tmpLeft = next->left;
                next->value = '*';
                next->left = getNode('/');
                next->right = tmpLeft;
                next->left->left = getNode('1');
                next->left->right = copyTree(tmpLeft->original);
                break;
            case 's':
                // (sin(X))' = cos(X) * X'
                next->value = '*';
                next->right = next->left;
                next->left = getNode('c');
                next->left->left = copyTree(next->right->original);
                break;
            case 'c':
                // (cos(X))' = -sin(X) * X'
                next->value = '*';
                next->right = next->left;
                next->left = getNode('_');
                next->left->left = getNode('s');
                next->left->left->left = copyTree(next->right->original);
                break;
            case 't':
                // (tg(X))' = 1/(cos(X) * cos(X)) * X'
                tmpLeft = next->left;
                next->value = '*';
                next->left = getNode('/');
                next->right = tmpLeft;
                next->left->left = getNode('1');
                next->left->right = getNode('*');
                next->left->right->left = getNode('c');
                next->left->right->left->left = copyTree(tmpLeft->original);
                next->left->right->right = getNode('c');
                next->left->right->right->left = copyTree(tmpLeft->original);
                break;
            case 'm':
                // Ako nije jasno kako diferenciranje minimuma funkcioniše,
                // pogledati zaglavlje datoteke i mejl profesoru Mišiću.
                if (originalTree->tree == tree) {
                    // Diferenciramo originalno stablo.
                    tmpLeft = next->left;
                    tmpRight = next->right;
                    next->left = getNode('?');
                    next->right = getNode('?');
                    next->left->left = copyTree(tmpLeft->original);
                    next->left->right = copyTree(tmpRight->original);
                    next->right->left = tmpLeft;
                    next->right->right = tmpRight;
                } else {
                    // Prvo evaluiramo izraz pa biramo diferencijal koji treba.
                    double resultLeft, resultRight;
                    if (!alreadyRead) {
                        printf(
                            "U skladu sa pretpostavkama zadatka, minimum se "
                            "ne diferencira dalje od prvog izvoda. Unesite "
                            "promenljive izraza kako biste nastavili sa "
                            "diferenciranjem.\n"
                        );
                        for (int i = 0; i < 26; ++i) {
                            if (variables[i].present) {
                                printf(
                                    "Unesite vrednost promenljive %c: ",
                                    'A' + i
                                );
                                scanf("%lf", &variables[i].value);
                            }
                        }
                        alreadyRead = true;
                    }
                    calculateExpressionInner(
                        next->left->left->original,
                        variables,
                        &resultLeft,
                        true
                    );
                    calculateExpressionInner(
                        next->left->right->original,
                        variables,
                        &resultRight,
                        true
                    );
                    freeTree(next->left);
                    if (resultLeft <= resultRight) {
                        next->value = next->right->left->value;
                        next->left = next->right->left->left;
                        tmpRight = next->right->left->right;
                        freeTree(next->right->right);
                        free(next->right->left);
                        free(next->right);
                        next->right = tmpRight;
                    } else {
                        next->value = next->right->right->value;
                        next->left = next->right->right->left;
                        tmpRight = next->right->right->right;
                        freeTree(next->right->left);
                        free(next->right->right);
                        free(next->right);
                        next->right = tmpRight;
                    }
                }
                break;
            default:
                if (next->value >= 'A' && next->value <= 'Z') {
                    if (next->value == input) {
                        next->value = '1';
                    } else {
                        next->value = '0';
                    }
                } else if (next->value == '0' || next->value == '1') {
                    next->value = '0';
                } else {
                    // Ne znamo šta diferenciramo.
                    freeTree(differentialTree);
                    while (postorderStack != NULL) {
                        treeStackPop(&postorderStack);
                    }
                    return OOPS;
                }
        }
    }
    #ifdef POJEDNOSTABLJENJE
    pojednostabljenje(differentialTree);
    #endif
    addTree(trees, differentialTree, label);
    return OK;
}

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
