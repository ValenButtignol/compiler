#include <stdio.h>
#include <stdlib.h>

#include "../include/ast.h"

TAst* newAst(NodeInfo *root, TAst* ls, TAst* rs){
    TAst* ast = (TAst*) malloc(sizeof(TAst));

    ast->data = *root;
    ast->ls = ls;
    ast->rs = rs;
    return ast;
}

TAst* newEmptyAst(){
    TAst *ast = (TAst*) malloc(sizeof(TAst));
    ast->data = *newEmptyNodeInfo();
    ast->ls = NULL;
    ast->rs = NULL;
    return ast;
}

int isEmptyAst(TAst ast){
    return isEmptyNode(ast.data) && ast.ls == NULL && ast.rs == NULL;
}

TAst* newLeaf(NodeInfo *root) {
    TAst *ast = (TAst*) malloc(sizeof(TAst));
    ast->data = *root;
    ast->ls = NULL;
    ast->rs = NULL;
    return ast;
}

char* astToString(TAst* ast) {
    return astToStringRecursive(ast);
}

char* astToStringRecursive(TAst* ast) {
    if (ast == NULL || isEmptyAst(*ast)) {
        return strdup(""); // Return an empty string for NULL ast
    }

    char* lsStr = astToStringRecursive(ast->ls);
    char* rootStr;
    if(!isEmptyNode(ast->data)) rootStr = nodeInfoToString(ast->data);
    else{
        rootStr = malloc(sizeof(""));
        *rootStr = ""; 
    }
    char* rsStr = astToStringRecursive(ast->rs);

    // Calculate the length of the final string
    size_t totalLength = strlen(rootStr) + strlen(lsStr) + strlen(rsStr) + 5; // +5 for formatting characters

    char* result = (char*)malloc(totalLength * sizeof(char));
    if (result == NULL) {
        // Handle memory allocation failure
        return NULL;
    }
    printf("    root: %s\nls: %s        lr: %s\n", rootStr, lsStr, rsStr);
    // Format the result string
    snprintf(result, totalLength, "%s %s %s", lsStr, rootStr, rsStr);
    free(rootStr);
    free(lsStr);
    free(rsStr);

    return result;
}