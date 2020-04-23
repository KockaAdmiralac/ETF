#include "options.h"
// Uklonite ovu definiciju ako želite da vidite kako izgleda stablo izraza
// pre pojednostavljivanja.
#define POJEDNOSTABLJENJE

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

Result calculateExpressionInner(Tree *tree, InputVariable variables[26], double *output) {
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
    Tree *tree = chooseTree(trees, "koje predstavlja izraz za izračunavanje");
    double output;
    Result result = calculateExpressionInner(tree, variables, &output);
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
                if (
                    (
                        next->left->value == '0' && (
                            next->right->value == '0' ||
                            next->right->value == '1'
                        )
                    ) ||
                    (next->right->value == '0' && next->left->value == '1')
                ) {
                    // min(0, 1) = 0, min(0, 0) = 0
                    freeTree(next->left);
                    freeTree(next->right);
                    next->left = NULL;
                    next->right = NULL;
                    next->value = '0';
                } else if (
                    next->left->value == '0' &&
                    next->right->value == '1'
                ) {
                    freeTree(next->left);
                    freeTree(next->right);
                    next->left = NULL;
                    next->right = NULL;
                    next->value = '1';
                }
                break;
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
                if ((*trees)->tree == (*trees)->next->tree) {
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
                        &resultLeft
                    );
                    calculateExpressionInner(
                        next->left->right->original,
                        variables,
                        &resultRight
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
