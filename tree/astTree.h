#include <stdio.h>

typedef struct{
	Type root;
	TAstTree* ls;
	TAstTree* rs;
}TAstTree;

TAstTree newAstTree(Type root, TAstTree* ls, TAstTree rs);
TAstTree newLeaf(Type root);
