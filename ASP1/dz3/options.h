#ifndef _OPTIONS_H
#define _OPTIONS_H
#include "graph.h"
#include "util.h"

Result outputGraph(Graph *graph);
Result optimalPath(Graph *graph);
Result transitiveDependencies(Graph *graph);

#endif
