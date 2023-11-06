#ifndef	UTILS_H
#define UTILS_H
#include <stdio.h>
#include "../dataStructures/ast.h"
#include "../dataStructures/nodeInfo.h"

void setParamsToNodeInfo(NodeInfo** node, TAst* ast);
void addOperationError(ErrorNode** errors, int lineNumber, enum TTag tag);
int checkReturnTypes(TAst *ast);
int checkSonsTypes(TAst *ast);
int checkSonsFatherTypes(TAst *ast);
#endif