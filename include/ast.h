#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <string.h>
#include "type.h"

typedef struct TAst{
	Type tipoDeNodo;//sentencia, definicion
	Type informacion;// + - int const true false variable NULL
	struct TAst* ls;
	struct TAst* rs;
}TAst;

TAst* newAst(Type root, TAst* ls, TAst* rs);

TAst* newLeaf(Type root);

char* astToString(TAst* ast);
char* astToStringRecursive(TAst* ast);

#endif
//arbol *info *ast *ast
//info = tag nombre tipo value
//ts = *info *ts