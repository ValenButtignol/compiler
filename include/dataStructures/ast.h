#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <string.h>
#include "nodeInfo.h"
#include "../utils/enums.h"
#include "errorNode.h"

typedef struct TAst{
	NodeInfo *data;
	struct TAst* ls;
	struct TAst* rs;
}TAst;

TAst* newAst(NodeInfo *root, TAst* ls, TAst* rs);

TAst* newEmptyAst();

TAst* newLeaf(NodeInfo **root);

char* astToString(TAst* ast);

char* astToStringRecursive(TAst* ast);

int isEmptyAst(TAst ast);

int isLeaf(TAst *ast);

#endif