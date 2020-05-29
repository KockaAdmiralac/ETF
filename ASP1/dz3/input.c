#include "input.h"

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
