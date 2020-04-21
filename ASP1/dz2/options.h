#ifndef _OPTIONS_H
#define _OPTIONS_H
#include "math.h"
#include "stack.h"
#include "tree.h"
#include "util.h"
#include "queue.h"

Result printTree(TreeList **trees, InputVariable variables[26]);
Result printPostfix(TreeList **trees, InputVariable variables[26]);
Result calculateExpression(TreeList **trees, InputVariable variables[26]);
Result differentiate(TreeList **trees, InputVariable variables[26]);

#endif
