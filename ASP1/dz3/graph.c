#include "graph.h"

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
