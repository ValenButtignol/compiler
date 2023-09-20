#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <string.h>
#include "nodeInfo.h"
#include "enums.h"

typedef struct TAst{
	NodeInfo data;
	struct TAst* ls;
	struct TAst* rs;
}TAst;

TAst* newAst(NodeInfo *root, TAst* ls, TAst* rs);

TAst* newEmptyAst();

TAst* newLeaf(NodeInfo *root);

char* astToString(TAst* ast);

char* astToStringRecursive(TAst* ast);

int isEmptyAst(TAst ast);

int checkType(TAst* ast);

enum TType getAstType(TAst* ast);

void evaluateAst(TAst* ast);

void evaluateExpression(TAst* ast);

int evaluateInteger(TAst* ast);

int evaluateBoolean(TAst* ast);

int isTypeTag(TAst ast);

#endif