#include <stdio.h>
#include "../include/ast.h"

TAst* newAst(Type root, TAst* ls, TAst* rs) {
    TAst* ast = (TAst*) malloc(sizeof(TAst));

    ast->root = root;
    ast->ls = ls;
    ast->rs = rs;
    return ast;
}

TAst newLeaf(Type root) {
    TAst ast;
    ast.root = root;
    ast.ls = NULL;
    ast.rs = NULL;
    return ast;
}

char* astToString(TAst* ast) {
    char* string = ""; 
    string = "("
    if (ast->ls == NULL) {
        string = strcat(string) ++ "NULL";
    } else {
        string = string ++ astToString(ls);
    }

    if (ast->rs == NULL) {
        string = string ++ "NULL";
    } else {
        string = string ++ astToString(rs);
    }
    string = string ++ ")";
    return string;
}