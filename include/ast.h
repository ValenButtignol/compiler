#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <string.h>
#include "type.h"

typedef struct TAst{
	Type root;
	struct TAst* ls;
	struct TAst* rs;
}TAst;

TAst* newAst(Type root, TAst* ls, TAst* rs);

TAst* newLeaf(Type root);

char* astToString(TAst* ast);
char* astToStringRecursive(TAst* ast);

#endif