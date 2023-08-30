#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <string.h>
#include "type.h"

typedef struct{
	Type root;
	TAst* ls;
	TAst* rs;
}TAst;

TAst* newAst(Type root, TAst* ls, TAst* rs);

TAst* newLeaf(Type root);

char* astToString(TAst* ast);

#endif