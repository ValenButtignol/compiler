#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <string.h>
#include "nodeInfo.h"

typedef struct TAst{
	NodeInfo data; //sentencia, definicion
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
#endif
//arbol *info *ast *ast
//info = tag nombre tipo value
//ts = *info *ts -> ACA VAN SOLO VARIABLES.