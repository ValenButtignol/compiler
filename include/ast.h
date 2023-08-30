#include <stdio.h>

typedef struct{
	Type root;
	TAst* ls;
	TAst* rs;
}TAst;

TAst newAst(Type root, TAst* ls, TAst rs);
TAst newLeaf(Type root);
