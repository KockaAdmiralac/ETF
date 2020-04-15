#ifndef _OPTIONS_H
#define _OPTIONS_H
#include "tree.h"
#include "util.h"

Result printTree(Tree *tree);
Result printPostfix(Tree *tree);
Result calculateExpression(Tree *tree);
Result differentiate(Tree *tree);

#endif
