#include <stdio.h>
#include <stdlib.h>

#include "../../include/dataStructures/ast.h"

TAst* newAst(NodeInfo *root, TAst* ls, TAst* rs) {
    TAst* ast = (TAst*) malloc(sizeof(TAst));

    ast->data = root;
    ast->ls = ls;
    ast->rs = rs;
    return ast;
}

TAst* newEmptyAst() {
    TAst *ast = (TAst*) malloc(sizeof(TAst));
    ast->data = newEmptyNodeInfo();
    ast->ls = NULL;
    ast->rs = NULL;
    return ast;
}

int isEmptyAst(TAst ast) {
    return isEmptyNode(*ast.data) && ast.ls == NULL && ast.rs == NULL;
}

TAst* newLeaf(NodeInfo **root) {
    TAst *ast = (TAst*) malloc(sizeof(TAst));
    ast->data = *root;
    ast->ls = NULL;
    ast->rs = NULL;
    return ast;
}


void printAst(TAst* ast) {

    if (ast == NULL || isEmptyAst(*ast)) {
        return ;
    }

    printf("ROOT: ");
    printf("%s", nodeInfoToString(*ast->data));
    (ast->data->id == NULL) ? : printf("    (ID %s)", ast->data->id);
    (ast->data->value == NULL) ? printf("\n") : printf("    (VALUE %d)\n", *(int*)ast->data->value);
    printf("        LS: %s", (ast->ls == NULL) ? "NULL" : nodeInfoToString(*ast->ls->data));
    printf("        RS: %s\n\n", (ast->rs == NULL) ? "NULL" : nodeInfoToString(*ast->rs->data));
    printAst(ast->ls);
    printAst(ast->rs);

    return ;

}

int isLeaf(TAst *ast){
    return (ast->ls == NULL && ast->rs == NULL);   
}