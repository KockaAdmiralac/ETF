/**
 * Usvojene pretpostavke:
 * - Promenljiva se ne može deklarisati nakon korišćenja.
 * - Identifikacioni brojevi instrukcija su uvek u redosledu 1, 2, 3...
 * - Postoji tačno jedan operator po redu, kao i najmanje jedna a najviše
 *   dve promenljive.
 *
 * Domaći je, barem delimično, proveren Valgrind-om protiv curenja memorije.
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define VT100_ESCAPE 27
#define MAX_GRAPH_NODES 26
// Isključuje funkcionalnost čišćenja ekrana.
// #define DEBUG

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
 * Čišćenje ekrana realizovano korišćenjem VT100 komandi.
 * @see https://www.csie.ntu.edu.tw/~r92094/c++/VT100.html
 */
void clear() {
    #ifndef DEBUG
    printf("%c[2J%c[f", VT100_ESCAPE, VT100_ESCAPE);
    #endif
}

/**
 * Read a dynamically allocated string from standard input, terminated by a
 * newline.
 * @returns {char*} Dynamically allocated string, or NULL if allocation failed
 */
char *readString() {
    int length = 0;
    int capacity = 1;
    char c;
    char *str = NULL, *tmp;
    while ((c = getchar()) != '\n') {
        ++length;
        if (length == capacity) {
            capacity *= 2;
            tmp = realloc(str, capacity * sizeof(char));
            if (tmp == NULL) {
                free(str);
                return NULL;
            }
            str = tmp;
        }
        *(str + length - 1) = c;
    }
    tmp = realloc(str, (length + 1) * sizeof(char));
    if (tmp == NULL) {
        free(str);
        return NULL;
    }
    str = tmp;
    *(str + length) = '\0';
    return str;
}

/**
 * Representation of a node's operand type.
 */
typedef enum {
    CONSTANT,
    NODE,
    UNUSED_NODE
} OperandType;

/**
 * Representation of a graph node.
 */
typedef struct {
    // Graph node's label - variable name.
    char label;
    // The operator between left hand and right hand side.
    // Possible values: +, -, *, /, &, |, ^, ~
    char operator;
    // Whether the left hand/right hand side is actually referencing another
    // graph node.
    OperandType leftHandType, rightHandType;
    // Left hand/right hand of the assignment.
    int leftHand, rightHand;
} GraphNode;

/**
 * Representation of a graph.
 */
typedef struct {
    // Graph node count.
    int nodeCount;
    // Graph nodes.
    GraphNode nodes[MAX_GRAPH_NODES];
    // Label-to-identificator mapping.
    int labelToId[MAX_GRAPH_NODES];
    // Connections between graph nodes.
    bool connections[MAX_GRAPH_NODES][MAX_GRAPH_NODES];
} Graph;

/**
 * Connects two nodes of the graph.
 * @param {Graph*} graph Graph whose two nodes should be connected
 * @param {int} startNode Identifier of the path's starting node
 * @param {int} endNode Identifier of the path's ending node
 * @returns {Result} Whether the action succeeded
 */
Result connectNodes(Graph *graph, int startNode, int endNode) {
    if (
        graph == NULL ||
        startNode < 1 ||
        startNode > graph->nodeCount ||
        endNode < 1 ||
        endNode > graph->nodeCount
    ) {
        return OOPS;
    }
    graph->connections[startNode-1][endNode-1] = true;
    return OK;
}

/**
 * Adds a node to the graph.
 * @param {Graph*} graph Graph to which the node should be added
 * @param {GraphNode} node Graph node data to be added
 * @returns {Result} Whether the action succeeded
 */
Result addGraphNode(Graph *graph, GraphNode node) {
    if (graph->nodeCount == MAX_GRAPH_NODES) {
        return OOM;
    }
    if (graph == NULL) {
        return OOPS;
    }
    graph->nodes[graph->nodeCount++] = node;
    graph->labelToId[node.label - 'a'] = graph->nodeCount;
    Result nodeConnectionResult;
    if (node.leftHandType == NODE) {
        nodeConnectionResult = connectNodes(
            graph,
            node.leftHand,
            graph->nodeCount
        );
        if (nodeConnectionResult != OK) {
            return nodeConnectionResult;
        }
    }
    if (node.rightHandType == NODE) {
        nodeConnectionResult = connectNodes(
            graph,
            node.rightHand,
            graph->nodeCount
        );
        if (nodeConnectionResult != OK) {
            return nodeConnectionResult;
        }
    }
    return OK;
}

/**
 * Disconnects two nodes of the graph.
 * @param {Graph*} graph Graph whose two nodes should be disconnected
 * @param {int} startNode Identifier of the path's starting node
 * @param {int} endNode Identifier of the path's ending node
 * @returns {Result} Whether the action succeeded
 */
Result disconnectNodes(Graph *graph, int startNode, int endNode) {
    if (
        graph == NULL ||
        startNode < 1 ||
        startNode > graph->nodeCount ||
        endNode < 1 ||
        endNode > graph->nodeCount
    ) {
        return OOPS;
    }
    graph->connections[startNode-1][endNode-1] = false;
    return OK;
}

/**
 * Resets a graph to its initial state.
 * @param {Graph*} graph Graph that should be reset
 * @returns {Result} Whether the action succeeded
 */
Result resetGraph(Graph *graph) {
    if (graph == NULL) {
        return OOPS;
    }
    for (int i = 0; i < graph->nodeCount; ++i) {
        for (int j = 0; j < graph->nodeCount; ++j) {
            graph->connections[i][j] = false;
        }
    }
    for (int i = 0; i < graph->nodeCount; ++i) {
        graph->labelToId[i] = 0;
    }
    graph->nodeCount = 0;
    return OK;
}

/**
 * Initializes a new graph structure.
 * @param {Graph*} graph Graph that should be initialized
 * @returns {Result} Whether the action succeeded
 */
Result createGraph(Graph *graph) {
    if (graph == NULL) {
        return OOPS;
    }
    graph->nodeCount = MAX_GRAPH_NODES;
    resetGraph(graph);
    return OK;
}

/**
 * Maps an operator to branch weight.
 * @param {char} operator Operator in the starting node of the branch
 * @returns {int} Weight of the branch starting with specified operator
 */
int weightFromOperator(char operator) {
    switch (operator) {
        case '+':
        case '-':
            return 3;
        case '*':
            return 10;
        case '/':
            return 23;
        case '&':
        case '|':
        case '^':
        case '~':
            return 1;
        default:
            return -1;
    }
}

/**
 * Gets a branch's weight.
 * @param {Graph*} graph Graph where branch weight should be found
 * @param {int} startNode Branch's starting node
 * @returns {int} Weight of the branch or -1 on failure
 */
int getWeight(Graph *graph, int startNode) {
    if (
        graph == NULL ||
        startNode < 1 ||
        startNode > graph->nodeCount
    ) {
        return -1;
    }
    return weightFromOperator(graph->nodes[startNode-1].operator);
}

/**
 * Converts a textual operator's first character to a sign operator.
 * Possible cases: and (&), or (|), not (~), xor (^).
 * @param {char} operator First character of textual operator
 * @returns {char} The corresponding sign operator
 */
char operatorFromText(char operator) {
    switch (operator) {
        case 'a': return '&';
        case 'o': return '|';
        case 'n': return '~';
        case 'x': return '^';
        default: return '\0';
    }
}

/**
 * Reads the input file until the next newline or closes it immediately if
 * it's not standard input. Not to be used when the currently read
 * character is a newline.
 * @param {FILE*} input File used to read the graph from
 */
void cleanInput(FILE *input) {
    if (input == stdin) {
        char c;
        while ((c = fgetc(input)) != '\n' && c != EOF);
    } else {
        fclose(input);
    }
}

/**
 * Parses the code from a specified input source into graph nodes.
 * @param {Graph*} graph Graph to insert the nodes to.
 * @returns {Result} Whether the action succeeded
 */
Result inputCode(Graph *graph) {
    printf(
        "Unesite naziv datoteke iz koje će programski kod biti učitan "
        "(ostavite prazno za unos sa standardnog ulaza): "
    );
    // Remove leading \n.
    getchar();
    char *filename = readString(), c;
    FILE *input = stdin;
    if (filename == NULL) {
        return OOM;
    }
    if (*filename != '\0') {
        input = fopen(filename, "r");
        if (input == NULL) {
            free(filename);
            printf(
                "Desila se greška prilikom otvaranja datoteke. Proverite da "
                "li datoteka sa zadatim imenom postoji i trenutnom korisniku "
                "je dozvoljeno njeno čitanje.\n"
            );
            return RTFM;
        }
    }
    free(filename);
    resetGraph(graph);
    int state = 0, charCounter = 0, constant = 0;
    char prev = '\0';
    bool running = true;
    GraphNode currentNode;
    Result tempResult;
    if (input == stdin) {
        printf("1: ");
    }
    /**
     * State meaning:
     * 0: We are parsing a variable name and spaces before it
     * 1: We are parsing the equals sign and spaces before it
     * 2: We are parsing the left hand side and spaces before it
     * 3: We are parsing the operator and spaces before it
     * 4: We are parsing a constant or an operator and spaces before it
     * 5: We are parsing the operator and spaces AFTER it or a constant
     * 6: We are parsing the right hand side and spaces before it
     * 7: We are parsing a constant or the end of line
     * 8: We are parsing the end of line
     */
    while (running && (c = fgetc(input)) != EOF) {
        ++charCounter;
        switch (c) {
            case '+':
            case '-':
            case '*':
            case '/':
            case '&':
            case '|':
            case '^':
                if (state == 3 || state == 4) {
                    // We entered a single-character operator.
                    if (state == 4) {
                        currentNode.leftHand = constant;
                        currentNode.leftHandType = CONSTANT;
                        constant = 0;
                    }
                    currentNode.operator = c;
                    state = 6;
                } else {
                    printf(
                        "Neočekivan operator '%c' na poziciji %d.\n",
                        c,
                        charCounter
                    );
                    resetGraph(graph);
                    cleanInput(input);
                    return RTFM;
                }
                break;
            case '=':
                if (state == 1) {
                    state = 2;
                } else {
                    printf(
                        "Neočekivana dodela na poziciji %d.\n",
                        charCounter
                    );
                    resetGraph(graph);
                    cleanInput(input);
                    return RTFM;
                }
                break;
            case '\n':
                if (state == 7 || state == 8) {
                    // We finished entering a node.
                    if (state == 7) {
                        currentNode.rightHand = constant;
                        currentNode.rightHandType = CONSTANT;
                        constant = 0;
                    }
                    tempResult = addGraphNode(graph, currentNode);
                    if (tempResult != OK) {
                        resetGraph(graph);
                        return tempResult;
                    }
                    state = 0;
                    if (graph->nodeCount == MAX_GRAPH_NODES) {
                        running = false;
                        break;
                    }
                    charCounter = 0;
                    prev = '\0';
                    if (input == stdin) {
                        printf("%d: ", graph->nodeCount + 1);
                    }
                } else if (state == 0) {
                    // We finished our input.
                    running = false;
                } else {
                    printf(
                        "Neočekivan kraj linije na poziciji %d.\n",
                        charCounter
                    );
                    resetGraph(graph);
                    if (input != stdin) {
                        fclose(input);
                    }
                    return RTFM;
                }
                break;
            case ' ':
                switch (state) {
                    case 4:
                        // Parsing the left-hand constant ended.
                        currentNode.leftHand = constant;
                        currentNode.leftHandType = CONSTANT;
                        constant = 0;
                        state = 3;
                        break;
                    case 5:
                        // Parsing the operator ended.
                        state = 6;
                        break;
                    case 7:
                        // Parsing the right-hand constant ended.
                        currentNode.rightHand = constant;
                        currentNode.rightHandType = CONSTANT;
                        constant = 0;
                        state = 8;
                        break;
                }
                break;
            default:
                if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                    if (c >= 'A' && c <= 'Z') {
                        // We technically accept uppercase letters.
                        c = c - 'A' + 'a';
                    }
                    switch (state) {
                        case 0:
                            // We are parsing the first variable.
                            currentNode.label = c;
                            state = 1;
                            break;
                        case 2:
                            // We are parsing the left-hand side variable.
                            currentNode.leftHand = graph->labelToId[c - 'a'];
                            if (currentNode.leftHand == 0) {
                                currentNode.leftHand = c;
                                currentNode.leftHandType = UNUSED_NODE;
                            } else {
                                currentNode.leftHandType = NODE;
                            }
                            state = 3;
                            break;
                        case 3:
                        case 4:
                            // We are parsing an operator.
                            if (prev >= 'a' && prev <= 'z') {
                                // We are parsing a unary operator.
                                if (prev == 'n') {
                                    // The unary operator is a NOT.
                                    currentNode.operator = '~';
                                } else {
                                    printf(
                                        "Operator na poziciji %d nije validan "
                                        "unarni operator.\n",
                                        charCounter
                                    );
                                    resetGraph(graph);
                                    cleanInput(input);
                                    return RTFM;
                                }
                            } else {
                                currentNode.operator = operatorFromText(c);
                                if (currentNode.operator == '\0') {
                                    printf(
                                        "Operator na poziciji %d nije validan "
                                        "binarni operator.\n",
                                        charCounter
                                    );
                                    resetGraph(graph);
                                    cleanInput(input);
                                    return RTFM;
                                }
                            }
                            state = 5;
                            break;
                        case 5:
                            // We are still parsing an operator, but the
                            // useless parts of it.
                            break;
                        case 6:
                            // We are parsing the right-hand side variable.
                            currentNode.rightHand = graph->labelToId[c - 'a'];
                            if (currentNode.rightHand == 0) {
                                currentNode.rightHand = c;
                                currentNode.rightHandType = UNUSED_NODE;
                            } else {
                                currentNode.rightHandType = NODE;
                            }
                            state = 8;
                            break;
                        default:
                            printf(
                                "Neočekivani karakter '%c' na poziciji %d.\n",
                                c,
                                charCounter
                            );
                            resetGraph(graph);
                            cleanInput(input);
                            return RTFM;
                    }
                } else if (c >= '0' || c <= '9') {
                    // We are parsing a constant.
                    constant = constant * 10 + c - '0';
                    switch (state) {
                        case 2:
                        case 4:
                            state = 4;
                            break;
                        case 5:
                        case 6:
                        case 7:
                            state = 7;
                            break;
                        default:
                            printf(
                                "Neočekivana konstanta '%c' na poziciji %d.\n",
                                c,
                                charCounter
                            );
                            cleanInput(input);
                            resetGraph(graph);
                            return RTFM;
                    }
                } else {
                    printf(
                        "Karakter '%c' na poziciji %d nije validan unos.\n",
                        c,
                        charCounter
                    );
                    cleanInput(input);
                    resetGraph(graph);
                    return RTFM;
                }
                break;
        }
        prev = c;
    }
    if (input != stdin) {
        fclose(input);
    }
    return OK;
}

/**
 * Outputs the graph to standard output or a specified file.
 * @param {Graph*} graph Graph to output
 * @returns {Result} Whether the action succeeded
 */
Result outputGraph(Graph *graph) {
    if (graph->nodeCount == 0) {
        printf("Graf je prazan.\n");
        return RTFM;
    }
    printf(
        "Unesite naziv datoteke u koju će graf biti upisan (ostavite prazno "
        "za ispis na standardni izlaz): "
    );
    // Remove leading \n.
    getchar();
    char *filename = readString();
    FILE *output = stdout;
    if (*filename != '\0') {
        output = fopen(filename, "w");
        if (output == NULL) {
            free(filename);
            printf(
                "Desila se greška prilikom otvaranja datoteke. Proverite da "
                "li datoteka sa zadatim imenom postoji i trenutnom korisniku "
                "je dozvoljeno njeno pisanje.\n"
            );
            return RTFM;
        }
    }
    free(filename);
    for (int i = 0; i < graph->nodeCount; ++i) {
        fprintf(output, "%c (", graph->nodes[i].label);
        if (graph->nodes[i].operator == '~') {
            fprintf(output, "~");
        } else {
            if (graph->nodes[i].leftHandType == NODE) {
                fprintf(output, "%c", graph->nodes[graph->nodes[i].leftHand-1].label);
            } else if (graph->nodes[i].leftHandType == CONSTANT) {
                fprintf(output, "%d", graph->nodes[i].leftHand);
            } else {
                fprintf(output, "%c", graph->nodes[i].leftHand);
            }
            fprintf(output, " %c ", graph->nodes[i].operator);
        }
        if (graph->nodes[i].rightHandType == NODE) {
            fprintf(output, "%c", graph->nodes[graph->nodes[i].rightHand-1].label);
        } else if (graph->nodes[i].rightHandType == CONSTANT) {
            fprintf(output, "%d", graph->nodes[i].rightHand);
        } else {
            fprintf(output, "%c", graph->nodes[i].rightHand);
        }
        fprintf(output, "): ");
        bool anyConnections = false;
        for (int j = 0; j < graph->nodeCount; ++j) {
            if (graph->connections[i][j]) {
                anyConnections = true;
                fprintf(output, "%c ", graph->nodes[j].label);
            }
        }
        if (!anyConnections) {
            fprintf(output, "✗");
        }
        fprintf(output, "\n");
    }
    if (output != stdout) {
        fclose(output);
    }
    return OK;
}

/**
 * Calculates the critical path and possible placement of operations.
 * @param {Graph*} graph Graph for which the critical path should be calculated
 * @returns {Result} Whether the operation was successful
 */
Result optimalPath(Graph *graph) {
    if (graph->nodeCount == 0) {
        printf("Graf je prazan.\n");
        return RTFM;
    }
    int EST[MAX_GRAPH_NODES],
        LST[MAX_GRAPH_NODES],
        criticalPathLength = 0;
    for (int i = 0; i < graph->nodeCount; ++i) {
        EST[i] = 0;
        for (int j = 0; j < graph->nodeCount; ++j) {
            if (graph->connections[j][i]) {
                int weight = getWeight(graph, j + 1);
                if (EST[j] + weight > EST[i]) {
                    EST[i] = EST[j] + weight;
                }
            }
        }
        int outWeight = getWeight(graph, i + 1);
        if (EST[i] + outWeight > criticalPathLength) {
            criticalPathLength = EST[i] + outWeight;
        }
    }
    for (int i = graph->nodeCount - 1; i >= 0; --i) {
        int weight = getWeight(graph, i + 1);
        LST[i] = criticalPathLength - weight;
        for (int j = 0; j < graph->nodeCount; ++j) {
            if (graph->connections[i][j]) {
                if (LST[j] - weight < LST[i]) {
                    LST[i] = LST[j] - weight;
                }
            }
        }
    }
    printf(
        "Dužina kritičnog puta: %d\n"
        "Vremena počinjanja operacija:\n"
        "┌──────┬──────┬──────┐\n"
        "│ Čvor │  EST │ LST  │\n"
        "├──────┼──────┼──────┤\n",
        criticalPathLength
    );
    for (int i = 0; i < graph->nodeCount; ++i) {
        printf(
            "│  %c   │ % 4d │ % 4d │\n",
            graph->nodes[i].label,
            EST[i],
            LST[i]
        );
    }
    printf(
        "└──────┴──────┴──────┘\n"
        "Raspored po taktovima:\n"
    );
    bool anyPrinted;
    for (int i = 0; i <= criticalPathLength; ++i) {
        anyPrinted = false;
        for (int j = 0; j < graph->nodeCount; ++j) {
            if (EST[j] != LST[j] && EST[j] <= i && LST[j] >= i) {
                if (!anyPrinted) {
                    printf("% 4d: ", i);
                }
                anyPrinted = true;
                printf("%c ", graph->nodes[j].label);
            }
        }
        if (anyPrinted) {
            printf("\n");
        }
    }
    printf("Kritični putevi:\n");
    char currentCriticalPath[27] = "";
    int currentNodeIdentifier, currentIndex, currentCriticalPathLength;
    bool hasChild;
    for (int i = 0; i < 26; ++i) {
        if (EST[i] != 0 || EST[i] != LST[i]) {
            continue;
        }
        currentCriticalPathLength = 1;
        currentNodeIdentifier = i;
        currentIndex = 0;
        currentCriticalPath[0] = graph->nodes[i].label;
        while (true) {
            hasChild = false;
            for (int j = currentIndex; j < graph->nodeCount; ++j) {
                if (
                    graph->connections[currentNodeIdentifier][j] &&
                    EST[j] == LST[j] &&
                    getWeight(graph, currentNodeIdentifier + 1) ==
                    EST[j] - EST[currentNodeIdentifier]
                ) {
                    currentCriticalPath[currentCriticalPathLength++] =
                        graph->nodes[j].label;
                    currentNodeIdentifier = j;
                    currentIndex = 0;
                    hasChild = true;
                    break;
                }
            }
            if (hasChild) {
                continue;
            }
            if (
                LST[currentNodeIdentifier] +
                getWeight(graph, currentNodeIdentifier + 1) ==
                criticalPathLength
            ) {
                currentCriticalPath[currentCriticalPathLength] = '\0';
                printf("- %s\n", currentCriticalPath);
            }
            currentIndex = currentNodeIdentifier + 1;
            if (currentCriticalPathLength == 1) {
                break;
            }
            --currentCriticalPathLength;
            currentNodeIdentifier =
                graph->labelToId[
                    currentCriticalPath[currentCriticalPathLength - 1] - 'a'
                ] - 1;
        }
    }
    return OK;
}

/**
 * Calculates transitive dependencies of a specified node.
 * @param {Graph*} graph Graph in which the specified node should be located
 * @returns {Result} Whether the operation was successful
 */
Result transitiveDependencies(Graph *graph) {
    if (graph->nodeCount == 0) {
        printf("Graf je prazan.\n");
        return RTFM;
    }
    printf(
        "Unesite oznaku čvora za koji želite da pronađete tranzitivne grane.\n"
    );
    char nodeLabel;
    scanf(" %c", &nodeLabel);
    int nodeId = graph->labelToId[nodeLabel - 'a'];
    if (nodeId == 0) {
        printf("Dati čvor se ne nalazi u grafu.\n");
        return RTFM;
    }
    bool isTransitive[MAX_GRAPH_NODES] = {false},
         connectionsWarshall[MAX_GRAPH_NODES][MAX_GRAPH_NODES];
    for (int i = 0; i < graph->nodeCount; ++i) {
        for (int j = 0; j < graph->nodeCount; ++j) {
            connectionsWarshall[i][j] = graph->connections[i][j];
        }
    }
    bool hasTransitive = false;
    for (int k = 0; k < graph->nodeCount; ++k) {
        if (connectionsWarshall[nodeId-1][k]) {
            for (int j = 0; j < graph->nodeCount; ++j) {
                if (connectionsWarshall[k][j]) {
                    if (graph->connections[nodeId-1][j]) {
                        isTransitive[j] = true;
                        hasTransitive = true;
                    }
                    connectionsWarshall[nodeId-1][j] = true;
                }
            }
        }
    }
    if (hasTransitive) {
        printf("Krajnji čvorovi tranzitivnih grana iz datog čvora: ");
        for (int i = 0; i < graph->nodeCount; ++i) {
            if (isTransitive[i]) {
                printf("%c ", graph->nodes[i].label);
            }
        }
        printf("\n");
    } else {
        printf("Iz datog čvora ne polaze tranzitivne grane.\n");
    }
    return OK;
}

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
