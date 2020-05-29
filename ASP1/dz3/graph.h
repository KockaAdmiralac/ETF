#ifndef _GRAPH_H
#define _GRAPH_H
#include "util.h"
#define MAX_GRAPH_NODES 26

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

Result addGraphNode(Graph *graph, GraphNode node);
Result connectNodes(Graph *graph, int firstNode, int secondNode);
Result disconnectNodes(Graph *graph, int firstNode, int secondNode);
Result resetGraph(Graph *graph);
Result createGraph(Graph *graph);
int getWeight(Graph *graph, int startNode);

#endif
