#include "options.h"

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
        criticalPathLength = 0,
        criticalPathNode = -1;
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
            criticalPathNode = i;
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
        printf("% 4d: ", i);
        anyPrinted = false;
        for (int j = 0; j < graph->nodeCount; ++j) {
            if (EST[j] != LST[j] && EST[j] <= i && LST[j] >= i) {
                anyPrinted = true;
                printf("%c ", graph->nodes[j].label);
            }
        }
        if (!anyPrinted) {
            printf("✗");
        }
        printf("\n");
    }
    printf("Kritični put: ");
    bool anyParent;
    do {
        anyParent = false;
        printf("%c ", graph->nodes[criticalPathNode].label);
        for (int i = 0; i < graph->nodeCount; ++i) {
            if (graph->connections[i][criticalPathNode] && EST[i] == LST[i]) {
                criticalPathNode = i;
                anyParent = true;
                break;
            }
        }
    } while (anyParent);
    printf("\n");
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
