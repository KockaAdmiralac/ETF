/**
 * Usvojene pretpostavke:
 * - Matrica je sortirana, ne moramo da validiramo to.
 * - Radi se sa celim brojevima manjim od 1000 i većim od -100.
 *   (Program radi i za brojeve veće od tih, ali izgleda ružnije.)
 * - Korisnik će generisati stablo iz matrice pre poređenja performansi.
 *   (Ne moramo mi da ga generišemo za njega.)
 */
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <iomanip>
#include <new>
#include <queue>
#include <random>
#include <stack>
#include <string>
#include <utility>
#include <vector>
// Iskomentarisati kako se ekran ne bi čistio.
// #define DEBUG
// Iskomentarisati kako se stablo ne bi bojilo.
#define COLORFUL

// Generator nasumičnih brojeva.
std::default_random_engine randomEngine;

/**
 * Struktura čvora AVL stabla.
 */
struct AVL {
    AVL *left, *right;
    int key, balance;
};

/**
 * Čišćenje ekrana realizovano korišćenjem VT100 komandi.
 * @see https://www.csie.ntu.edu.tw/~r92094/c++/VT100.html
 */
void clear() {
    #ifndef DEBUG
    std::cout << "\033[2J\033[f";
    #endif
}

/**
 * Ispis menija za izbor opcija.
 * @param {int&} option Promenljiva za čuvanje izabrane opcije
 */
void menu(int &option) {
    std::cout
    // Ovaj enkodovani meni služi za to da ako na odbrani GCC verzija ne
    // bude lepo rukovodila Unicode karakterima.
    // << "\u2554\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2557\n"
    // <<  "\u2551 Prvi domaći iz Algoritama i struktura podataka 2         \u2551\n"
    // <<  "\u2551 Student Luka Simić, broj indeksa 368, godina upisa 2019. \u2551\n"
    // <<  "\u255f\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2562\n"
    // <<  "\u2551 Izaberite opciju za svoju narednu operaciju.             \u2551\n"
    // <<  "\u255f\u2500 Matrica \u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2562\n"
    // <<  "\u2551 1.  Unos matrice.                                        \u2551\n"
    // <<  "\u2551 2.  Generisanje matrice.                                 \u2551\n"
    // <<  "\u2551 3.  Pretraživanje matrice.                               \u2551\n"
    // <<  "\u2551 4.  Ispis matrice.                                       \u2551\n"
    // <<  "\u255f\u2500 AVL \u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2562\n"
    // <<  "\u2551 5.  Formiranje AVL stabla od matrice.                    \u2551\n"
    // <<  "\u2551 6.  Umetanje u AVL stablo.                               \u2551\n"
    // <<  "\u2551 7.  Pretraga AVL stabla.                                 \u2551\n"
    // <<  "\u2551 8.  Ispis AVL stabla.                                    \u2551\n"
    // <<  "\u2551 9.  Brisanje AVL stabla.                                 \u2551\n"
    // <<  "\u255f\u2500 Ostalo \u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2562\n"
    // <<  "\u2551 10. Evaluacija performansi pretrage.                     \u2551\n"
    // <<  "\u2551 0.  Izlaz iz programa.                                   \u2551\n"
    // <<  "\u255a\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u255d"
    <<  "╔══════════════════════════════════════════════════════════╗\n"
    <<  "║ Prvi domaći iz Algoritama i struktura podataka 2         ║\n"
    <<  "║ Student Luka Simić, broj indeksa 368, godina upisa 2019. ║\n"
    <<  "╟──────────────────────────────────────────────────────────╢\n"
    <<  "║ Izaberite opciju za svoju narednu operaciju.             ║\n"
    <<  "╟─ Matrica ────────────────────────────────────────────────╢\n"
    <<  "║ 1.  Unos matrice.                                        ║\n"
    <<  "║ 2.  Generisanje matrice.                                 ║\n"
    <<  "║ 3.  Pretraživanje matrice.                               ║\n"
    <<  "║ 4.  Ispis matrice.                                       ║\n"
    <<  "╟─ AVL ────────────────────────────────────────────────────╢\n"
    <<  "║ 5.  Formiranje AVL stabla od matrice.                    ║\n"
    <<  "║ 6.  Umetanje u AVL stablo.                               ║\n"
    <<  "║ 7.  Pretraga AVL stabla.                                 ║\n"
    <<  "║ 8.  Ispis AVL stabla.                                    ║\n"
    <<  "║ 9.  Brisanje AVL stabla.                                 ║\n"
    <<  "╟─ Ostalo ─────────────────────────────────────────────────╢\n"
    <<  "║ 10. Evaluacija performansi pretrage.                     ║\n"
    <<  "║ 0.  Izlaz iz programa.                                   ║\n"
    <<  "╚══════════════════════════════════════════════════════════╝"
    << std::endl;
    std::cin >> option;
}

/**
 * Dealocira celu matricu.
 * @param {int**&} Matrica za dealociranje
 * @param {int} height Visina matrice za dealociranje
 */
void deleteMatrix(int **&matrix, int &height) {
    for (int i = 0; i < height; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    matrix = nullptr;
}

/**
 * Čita podatke o matrici iz prosleđenog izvora (standardni ulaz ili datoteka).
 * @param {int**&} matrix Matrica u koju se učitavaju podaci
 * @param {int&} width Širina matrice u koju se učitavaju podaci
 * @param {int&} height Visina matrice u koju se učitavaju podaci
 * @param {std::istream&} file Izvor iz kojeg se čitaju podaci
 */
void readMatrixFromFile(int **&matrix, int &width, int &height, std::istream &file) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            file >> matrix[i][j];
        }
    }
}

/**
 * Iznova inicijalizuje matricu sa visinom i širinom zadatim preko
 * standardnog ulaza.
 * @param {int**&} matrix Matrica koja se inicijalizuje.
 * @param {int&} width Širina matrice za inicijalizaciju
 * @param {int&} height Visina matrica za inicijalizaciju
 * @throw {const char*} Pri pogrešno unetim dimenzijama matrice
 */
void initializeMatrix(int **&matrix, int &width, int &height) {
    if (matrix != nullptr) {
        deleteMatrix(matrix, height);
    }
    std::cout << "Unesite širinu matrice: ";
    std::cin >> width;
    std::cout << "Unesite visinu matrice: ";
    std::cin >> height;
    if (width <= 0 || height <= 0) {
        throw "Nisu unete validne dimenzije matrice.";
    }
    matrix = new int*[height];
    for (int i = 0; i < height; ++i) {
        matrix[i] = new int[width];
    }
}

/**
 * Vrši unos podataka matrice sa standardnog ulaza ili datoteke.
 * @param {int**&} matrix Matrica čiji se podaci unose.
 * @param {int&} width Širina matrica čiji se podaci unose
 * @param {int&} height Visina matrica čiji se podaci unose
 * @throw {const char*} Pri grešci u radu sa datotekom ili pogrešno unetim
 *                      dimenzijama matrice
 */
void inputMatrix(int **&matrix, int &width, int &height, AVL*&) {
    initializeMatrix(matrix, width, height);
    std::cout << "Unesite naziv datoteke iz koje se čita matrica "
              <<  "(ostavite prazno za unos sa standardnog ulaza): ";
    std::string filename;
    std::cin.ignore();
    std::getline(std::cin, filename);
    if (filename.length() == 0) {
        readMatrixFromFile(matrix, width, height, std::cin);
    } else {
        std::ifstream matrixFile(filename.c_str(), std::ios::in);
        if (!matrixFile.is_open()) {
            throw "Desila se greška prilikom otvaranja zadate datoteke.";
        }
        readMatrixFromFile(matrix, width, height, matrixFile);
        matrixFile.close();
    }
}

/**
 * Nasumično generiše podatke u matrici. Distribucija nasumičnih brojeva koja
 * se koristi je gama distribucija i parametri su uzeti sa:
 * https://upload.wikimedia.org/wikipedia/commons/e/e6/Gamma_distribution_pdf.svg
 * @param {int**&} matrix Matrica čiji se podaci nasumično generišu
 * @param {int&} width Širina matrice čiji se podaci nasumično generišu
 * @param {int&} height Visina matrice čiji se podaci nasumično generišu
 * @throw {const char*} Pri pogrešno unetim dimenzijama matrice
 */
void generateMatrix(int **&matrix, int &width, int &height, AVL*&) {
    initializeMatrix(matrix, width, height);
    for (int x = 0; x < height; ++x) {
        for (int y = 0; y < width; ++y) {
            int high = 100;
            if (x > 0 && matrix[y][x-1] < high) {
                high = matrix[y][x-1];
            }
            if (y > 0 && matrix[y-1][x] < high) {
                high = matrix[y-1][x];
            }
            std::gamma_distribution<double> distribution(5.0, 1.0);
            matrix[y][x] = high - (int)distribution(randomEngine) % (high + 1);
        }
    }
}

/**
 * Pretražuje matricu nerastuće sortiranu po vrstama i kolonama za određeni
 * element i broji broj iteracija potrebnih za to.
 * @param {int**&} matrix Matrica koja se pretražuje
 * @param {int&} width Širina matrice koja se pretražuje
 * @param {int&} height Visina matrice koja se pretražuje
 * @param {int} value Vrednost koja se traži u matrici
 * @returns {std::tuple<int, int, int>} Torka koja označava koordinate
 *                                      pronađenog elementa i broj iteracija
 *                                      potrebnih za pronalaženje
 */
std::tuple<int, int, int> searchMatrix(int **&matrix, int &width, int &height, int value) {
    int x = width - 1, y = 0, steps = 0;
    while (x >= 0 && y < height) {
        ++steps;
        if (matrix[y][x] == value) {
            return std::make_tuple(x, y, steps);
        } else if (matrix[y][x] < value) {
            --x;
        } else {
            ++y;
        }
    }
    return std::make_tuple(-1, -1, steps);
}

/**
 * Pretražuje matricu nerastuće sortiranu po vrstama i kolonama za određeni
 * element unet preko standardnog ulaza.
 * @param {int**&} matrix Matrica koja se pretražuje
 * @param {int&} width Širina matrice koja se pretražuje
 * @param {int&} height Visina matrice koja se pretražuje
 * @throw {const char*} Ukoliko matrica nije inicijalizovana
 */
void searchMatrixForValue(int **&matrix, int &width, int &height, AVL*&) {
    if (matrix == nullptr) {
        throw "Matrica nije uneta.";
    }
    int value;
    std::cout << "Unesite broj koji se traži: ";
    std::cin >> value;
    auto found = searchMatrix(matrix, width, height, value);
    if (std::get<0>(found) == -1) {
        std::cout << "Uneti broj nije pronađen u matrici." << std::endl;
    } else {
        std::cout << "Uneti broj je pronađen na (" << std::get<0>(found) << ", "
                  << std::get<1>(found) << ")." << std::endl;
    }
}

/**
 * Ispisuje sadržaj matrice na standardni izlaz.
 * @param {int**&} matrix Matrica koja se ispisuje
 * @param {int&} width Širina matrice koja se ispisuje
 * @param {int&} height Visina matrice koja se ispisuje
 * @throw {const char*} Ukoliko matrica nije inicijalizovana
 */
void outputMatrix(int **&matrix, int &width, int &height, AVL*&) {
    if (matrix == nullptr) {
        throw "Matrica nije uneta.";
    }
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::cout << std::setw(4) << matrix[y][x];
        }
        std::cout << std::endl;
    }
}

/**
 * Formira novi čvor AVL stabla sa zadatim ključem.
 * @param {int} key Ključ u čvoru stabla
 * @returns {AVL*} Novoformirani čvor stabla
 */
AVL *getNode(int key) {
    AVL *node = new AVL;
    node->left = nullptr;
    node->right = nullptr;
    node->balance = 0;
    node->key = key;
    return node;
}

/**
 * Radi desnu rotaciju oko čvora u AVL stablu.
 * @param {AVL*&} node Čvor oko kojeg se vrši rotacija
 */
void rightRotation(AVL *&node) {
    AVL *temp = node->left->right;
    node->left->right = node;
    node->left = temp;
}

/**
 * Radi levu rotaciju oko čvora u AVL stablu.
 * @param {AVL*&} node Čvor oko kojeg se vrši rotacija
 */
void leftRotation(AVL *&node) {
    AVL *temp = node->right->left;
    node->right->left = node;
    node->right = temp;
}

/**
 * Ubacuje ključ u AVL stablo. Ukoliko čvor sa datim ključem već postoji,
 * čvor se unosi na mesto njegovog sledbenika.
 * 
 * Ova funkcija je zasnovana na pseudokodu profesora Mila V. Tomaševića sa
 * strana 241-243 knjige "Algoritmi i strukture podataka", funkcija AVL-INSERT.
 * @param {AVL*&} tree Stablo u koje se unosi ključ
 * @param {int} key Ključ koji se unosi
 */
void avlInsert(AVL *&tree, int key) {
    AVL *newNode = getNode(key),
        *curr = tree,
        *prev = nullptr,
        *critical = tree,
        *criticalParent = nullptr,
        *criticalImbalancedChild = nullptr;
    int imbalance;
    if (tree == nullptr) {
        tree = newNode;
        return;
    }
    while (curr != nullptr) {
        AVL *next;
        if (curr->key <= key) {
            next = curr->right;
        } else {
            next = curr->left;
        }
        if (next != nullptr && next->balance != 0) {
            criticalParent = curr;
            critical = next;
        }
        prev = curr;
        curr = next;
    }
    if (prev->key <= key) {
        prev->right = newNode;
    } else {
        prev->left = newNode;
    }
    if (critical->key <= key) {
        criticalImbalancedChild = critical->right;
    } else {
        criticalImbalancedChild = critical->left;
    }
    curr = criticalImbalancedChild;
    imbalance = (critical->key <= key) ? -1 : 1;
    while (curr != newNode) {
        if (curr->key <= key) {
            curr->balance = -1;
            curr = curr->right;
        } else {
            curr->balance = 1;
            curr = curr->left;
        }
    }
    if (critical->balance == 0) {
        critical->balance = imbalance;
        return;
    } else if (critical->balance != imbalance) {
        critical->balance = 0;
        return;
    }
    if (criticalImbalancedChild->balance == imbalance) {
        curr = criticalImbalancedChild;
        if (imbalance == 1) {
            rightRotation(critical);
        } else {
            leftRotation(critical);
        }
        critical->balance = 0;
        criticalImbalancedChild->balance = 0;
    } else {
        if (imbalance == 1) {
            curr = criticalImbalancedChild->right;
            leftRotation(criticalImbalancedChild);
            critical->left = curr;
            rightRotation(critical);
        } else {
            curr = criticalImbalancedChild->left;
            critical->right = curr;
            rightRotation(criticalImbalancedChild);
            leftRotation(critical);
        }
        if (curr->balance == 0) {
            critical->balance = 0;
            criticalImbalancedChild->balance = 0;
        } else {
            if (curr->balance == imbalance) {
                critical->balance = -imbalance;
                criticalImbalancedChild->balance = 0;
            } else {
                critical->balance = 0;
                criticalImbalancedChild->balance = imbalance;
            }
            curr->balance = 0;
        }
    }
    if (criticalParent == nullptr) {
        tree = curr;
    } else {
        if (critical == criticalParent->right) {
            criticalParent->right = curr;
        } else {
            criticalParent->left = curr;
        }
    }
}

/**
 * Pretražuje AVL stablo za zadati ključ i broji iteracije potrebne da se taj
 * ključ pretraži.
 * @param {AVL*&} tree Stablo za pretraživanje
 * @param {int} key Ključ za traženje
 * @returns {std::tuple<bool, int>} Torku koja predstavlja da li je ključ nađen
 *                                  i u koliko iteracija.
 */
std::tuple<bool, int> searchTree(AVL*& tree, int key) {
    AVL *curr = tree;
    int steps = 0;
    while (curr != nullptr) {
        ++steps;
        if (curr->key == key) {
            return std::make_tuple(true, steps);
        } else if (curr->key < key) {
            curr = curr->right;
        } else {
            curr = curr->left;
        }
    }
    return std::make_tuple(false, steps);
}

/**
 * Pretražuje AVL stablo za ključ zadat preko standardnog ulaza.
 * @param {AVL*&} tree Stablo koje se pretražuje
 */
void searchTreeForValue(int **&, int &, int &, AVL *&tree) {
    int value;
    std::cout << "Uneti vrednost ključa: ";
    std::cin >> value;
    auto found = searchTree(tree, value);
    if (std::get<0>(found)) {
        std::cout << "Zadati ključ se nalazi u stablu." << std::endl;
    } else {
        std::cout << "Zadati ključ se ne nalazi u stablu." << std::endl;
    }
}

/**
 * Ubacuje ključ zadat preko standardnog ulaza u AVL stablo.
 * @param {AVL*&} tree Stablo za pretraživanje
 */
void insertNode(int **&, int &, int &, AVL *&tree) {
    int key;
    std::cout << "Uneti vrednost novog ključa: ";
    std::cin >> key;
    avlInsert(tree, key);
}

/**
 * Manipuliše prostorno-vremenskim kontinuumom tako da se u određenom
 * vremenskom periodu određen prostor kontinualno pojavi na ekranu korisnika
 * u vidu karaktera.
 *
 * Verzija 2: Sada se gorepomenute manipulacije vrše nad upućivačem na
 * std::ostream umesto pokazivačem na FILE.
 * @param {std::ostream&} file Datoteka nad kojom se vrši gorepomenuta magija.
 * @param {char*} space Prostor koji se pojavljuje na ekranu
 * @param {int} time Dužina vremenskom intervala tokom kojeg se prostor
 *                   pojavljuje na ekranu u femtogodinama.
 */
void spacetime(std::ostream &file, const char *space, int time) {
    for (int i = 0; i < time; ++i) {
        file << space;
    }
}

/**
 * Ispisuje formatirano AVL stablo na standardni izlaz ili u datoteku.
 *
 * Ova funkcija je preuzeta sa autorovog drugog domaćeg iz Algoritama i
 * struktura podataka 1 i modifikovana da bude više po C++ standardima,
 * kao i da dozvoljava ispis čvorova do tri karaktera širokih.
 * @param {AVL*&} tree Stablo koje se ispisuje
 * @param {std::ostream&} file Mesto na koje se ispisuje AVL stablo
 */
void printTree(AVL*& tree, std::ostream &file) {
    // Level-order obilazak radi utvrđivanja dubine stabla.
    std::queue<std::pair<int, AVL*>> levelOrderQueue;
    int maxLevel = 0;
    levelOrderQueue.push(std::make_pair(1, tree));
    while (!levelOrderQueue.empty()) {
        auto indexNodePair = levelOrderQueue.front();
        int index = indexNodePair.first;
        AVL *node = indexNodePair.second;
        levelOrderQueue.pop();
        if (index > maxLevel) {
            maxLevel = index;
        }
        if (node->left != nullptr) {
            levelOrderQueue.push(std::make_pair(index + 1, node->left));
        }
        if (node->right != nullptr) {
            levelOrderQueue.push(std::make_pair(index + 1, node->right));
        }
    }
    long long width = (1 << maxLevel) + 1;
    // Formiranje punog stabla od trenutnog stabla.
    long long fullTreeNodeNumber = width - 2;
    AVL **fullTree = new AVL*[fullTreeNodeNumber];
    for (long long i = 0; i < fullTreeNodeNumber; ++i) {
        fullTree[i] = nullptr;
    }
    // Populacija punog stabla pokazivačima na čvorove level-order obilaskom.
    levelOrderQueue.push(std::make_pair(1, tree));
    while (!levelOrderQueue.empty()) {
        auto indexNodePair = levelOrderQueue.front();
        int index = indexNodePair.first;
        AVL *node = indexNodePair.second;
        levelOrderQueue.pop();
        fullTree[index - 1] = node;
        if (node->left != nullptr) {
            levelOrderQueue.push(std::make_pair(index * 2, node->left));
        }
        if (node->right != nullptr) {
            levelOrderQueue.push(std::make_pair(index * 2 + 1, node->right));
        }
    }
    // Ispisivanje punog stabla.
    int currentLevelNodes = 1,
        index1 = 0,
        index2 = 0,
        baseSpace = std::pow(2, maxLevel) - 2,
        currValue;
    for (int i = 0; i < maxLevel; ++i) {
        // Ispisivanje čvorova.
        for (int j = 0; j < currentLevelNodes; ++j) {
            if (j == 0) {
                spacetime(file, " ", baseSpace);
            } else {
                spacetime(file, " ", baseSpace * 2 + 1);
            }
            if (fullTree[index1] == nullptr) {
                file << "   ";
            } else {
                currValue = fullTree[index1]->key;
                #ifdef COLORFUL
                if (file.rdbuf() == std::cout.rdbuf()) {
                    file << "\x1B[3" << (i % 7) + 1 << "m";
                }
                #endif
                if (currValue >= 0 && currValue < 10) {
                    file << ' ' << currValue << ' ';
                } else {
                    file << std::setw(3) << fullTree[index1]->key;
                }
                #ifdef COLORFUL
                if (file.rdbuf() == std::cout.rdbuf()) {
                    file << "\x1B[0m";
                }
                #endif
            }
            ++index1;
        }
        file << std::endl;
        // Ispisivanje strelica.
        if (i != maxLevel - 1) {
            for (int j = 0; j < currentLevelNodes; ++j) {
                bool exists = fullTree[index2] != nullptr,
                     leftChildExists = false,
                     rightChildExists = false;
                if (exists) {
                    if (fullTree[index2]->left != nullptr) {
                        leftChildExists = true;
                    }
                    if (fullTree[index2]->right != nullptr) {
                        rightChildExists = true;
                    }
                }
                if (leftChildExists) {
                    spacetime(file, " ", baseSpace / 2);
                    file << "\u250C";
                    spacetime(file, "\u2500", baseSpace / 2);
                } else {
                    spacetime(file, " ", baseSpace + 1);
                }
                if (leftChildExists && rightChildExists) {
                    file << "\u2534";
                } else if (leftChildExists) {
                    file << "\u2518";
                } else if (rightChildExists) {
                    file << "\u2514";
                } else {
                    file << " ";
                }
                if (rightChildExists) {
                    spacetime(file, "\u2500", baseSpace / 2);
                    file << "\u2510";
                    spacetime(file, " ", baseSpace / 2);
                } else {
                    spacetime(file, " ", baseSpace + 1);
                }
                file << " ";
                ++index2;
            }
            file << std::endl;
        }
        baseSpace = (baseSpace - 2) / 2;
        currentLevelNodes *= 2;
    }
    delete[] fullTree;
}

/**
 * Ispisuje formatirano AVL stablo na standardni izlaz ili u datoteku, koje god
 * se zada na standardnom ulazu.
 * @param {AVL*&} AVL stablo koje se ispisuje
 * @throw {const char*} Ukoliko stablo nije inicijalizovano
 */
void outputTree(int **&, int &, int &, AVL *&tree) {
    if (tree == nullptr) {
        throw "Stablo nije uneto.";
    }
    // Potencijalno ispisivanje u datoteku.
    std::cout << "Ukoliko želite da se stablo ispiše u datoteku, "
              << "unesite njen naziv: ";
    std::string filename;
    std::cin.ignore();
    std::getline(std::cin, filename);
    if (filename.length() == 0) {
        printTree(tree, std::cout);
    } else {
        std::ofstream treeFile(filename.c_str(), std::ios::out);
        if (!treeFile.is_open()) {
            throw "Desila se greška prilikom otvaranja zadate datoteke.";
        }
        printTree(tree, treeFile);
        treeFile.close();
    }
}

/**
 * Dealocira celo AVL stablo.
 * @param {AVL*&} tree AVL stablo za dealociranje
 * @throw {const char*} Ukoliko stablo nije alocirano
 */
void deleteTree(int **&, int &, int &, AVL *&tree) {
    if (tree == nullptr) {
        throw "Stablo nije uneto.";
    }
    std::stack<AVL*> deleteStack;
    deleteStack.push(tree);
    while (!deleteStack.empty()) {
        AVL *node = deleteStack.top();
        deleteStack.pop();
        if (node->left) {
            deleteStack.push(node->left);
        }
        if (node->right) {
            deleteStack.push(node->right);
        }
        delete node;
    }
    tree = nullptr;
}

/**
 * Inicijalizuje AVL stablo ubacujući sve vrednosti iz matrice u njega.
 * @param {int**&} matrix Matrica iz koje se čitaju vrednosti
 * @param {int&} width Širina matrice iz koje se čitaju vrednosti
 * @param {int&} height Visina matrice iz koje se čitaju vrednosti
 * @param {AVL*&} tree Stablo u koje se ubacuju vrednosti
 * @throw {const char*} Ukoliko matrica nije inicijalizovana
 */
void initializeTreeFromMatrix(int **&matrix, int &width, int &height, AVL*& tree) {
    if (matrix == nullptr) {
        throw "Matrica nije uneta.";
    }
    if (tree != nullptr) {
        deleteTree(matrix, width, height, tree);
    }
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            avlInsert(tree, matrix[y][x]);
        }
    }
}

/**
 * Čita unesene ključeve za pretragu sa standardnog ulaza ili iz datoteke.
 * @param {int} keyCount Broj ključeva za unos
 * @param {std::vector<int>&} keys Za čuvanje unesenih ključeva
 * @param {std::istream&} file Ulaz kroz koji se unose ključevi
 */
void inputKeys(int keyCount, std::vector<int> &keys, std::istream &file) {
    int key;
    for (int i = 0; i < keyCount; ++i) {
        file >> key;
        keys.push_back(key);
    }
}

/**
 * Pronalazi koliko je prosečno iteracija potrebno za pronalaženje ključeva u
 * matrici i AVL stablu za sve vrednosti iz zadatog opsega, radi poređenja
 * performansi. Ključevi se unose sa standardnog ulaza, ili kao raspon brojeva
 * ili kao sekvenca ključeva, sa standardnog ulaza ili iz datoteke.
 * @param {int**&} matrix Matrica čije se performanse porede
 * @param {int&} width Širina matrice čije se performanse porede
 * @param {int&} height Visina matrice čije se performanse porede
 * @param {AVL*&} tree Stablo čije se performanse porede
 */
void evaluateSearch(int **&matrix, int &width, int &height, AVL *&tree) {
    if (matrix == nullptr) {
        throw "Matrica nije uneta.";
    }
    if (tree == nullptr) {
        throw "Stablo nije uneto.";
    }
    int stepsMatrix = 0, stepsAVL = 0, separateKeys;
    std::cout << "Da li želite da unosite ključeve odvojeno? [0/1] ";
    std::cin >> separateKeys;
    std::vector<int> keys;
    if (separateKeys) {
        int keyCount;
        std::string filename;
        std::cout << "Unesite broj ključeva za unos: ";
        std::cin >> keyCount;
        std::cout << "Unesite naziv datoteke za unos ključeva "
                  << "(prazno za unos sa standardnog ulaza): ";
        std::cin.ignore();
        std::getline(std::cin, filename);
        if (filename.length() == 0) {
            inputKeys(keyCount, keys, std::cin);
        } else {
            std::ifstream keysFile(filename.c_str(), std::ios::in);
            if (!keysFile.is_open()) {
                throw "Desila se greška prilikom otvaranja zadate datoteke.";
            }
            inputKeys(keyCount, keys, keysFile);
            keysFile.close();
        }
    } else {
        int low, high;
        std::cout << "Unesite donju granicu intervala za pretragu: ";
        std::cin >> low;
        std::cout << "Unesite gornju granicu intervala za pretragu: ";
        std::cin >> high;
        for (int i = low; i <= high; ++i) {
            keys.push_back(i);
        }
    }
    for (size_t i = 0; i < keys.size(); ++i) {
        auto foundMatrix = searchMatrix(matrix, width, height, keys[i]);
        auto foundAVL = searchTree(tree, keys[i]);
        stepsMatrix += std::get<2>(foundMatrix);
        stepsAVL += std::get<1>(foundAVL);
    }
    double averageMatrix = ((double)stepsMatrix) / keys.size(),
           averageAVL = ((double)stepsAVL) / keys.size();
    std::cout << "Prosečan broj koraka po pretrazi u intervalu:" << std::endl
              << "  Matrica: " << averageMatrix << std::endl
              << "  AVL:     " << averageAVL << std::endl;
}

/**
 * Glavna funkcija programa.
 */
int main(void) {
    int option = 1, width, height;
    int **matrix = nullptr;
    AVL *tree = nullptr;
    void (*options[])(int**&, int&, int&, AVL*&) = {
        inputMatrix,
        generateMatrix,
        searchMatrixForValue,
        outputMatrix,
        initializeTreeFromMatrix,
        insertNode,
        searchTreeForValue,
        outputTree,
        deleteTree,
        evaluateSearch
    };
    clear();
    while (option) {
        menu(option);
        clear();
        if (option > 0 && option < 11) {
            try {
                options[option-1](matrix, width, height, tree);
            } catch (const char *message) {
                std::cout << message << std::endl;
            } catch (std::bad_alloc &exc) {
                std::cout << "Desila se greška prilikom alokacije memorije: "
                          << exc.what() << "." << std::endl;
            }
        } else if (option != 0) {
            std::cout << "Nije izabrana validna opcija." << std::endl;
        }
    }
    if (matrix != nullptr) {
        deleteMatrix(matrix, height);
    }
    if (tree != nullptr) {
        deleteTree(matrix, width, height, tree);
    }
    return EXIT_SUCCESS;
}
