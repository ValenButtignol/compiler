#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <string.h>
#include "nodeInfo.h"
#include "enums.h"
#include "errorNode.h"

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

int checkTypes(TAst* ast, ErrorNode** errors);

void setTypesInAst(TAst* ast, ErrorNode** errors);

enum TType getAstType(TAst* ast);

void evaluateAst(TAst* ast);

void evaluateExpression(TAst* ast);

int evaluateInteger(TAst* ast);

int evaluateBoolean(TAst* ast);

int isTypeableTag(TAst ast);

int isLeaf(TAst *ast);//tener en cuenta que si los dos hijos son arboles vacios o null entonces es una hoja
#endif