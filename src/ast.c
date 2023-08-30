#include <stdio.h>
#include <stdlib.h>

#include "../include/ast.h"

TAst* newAst(Type root, TAst* ls, TAst* rs) {
    TAst* ast = (TAst*) malloc(sizeof(TAst));

    ast->root = root;
    ast->ls = ls;
    ast->rs = rs;
    return ast;
}

TAst* newLeaf(Type root) {
    TAst *ast = (TAst*) malloc(sizeof(TAst));
    ast->root = root;
    ast->ls = NULL;
    ast->rs = NULL;
    return ast;
}

char* astToString(TAst* ast) {
        printf("\n2wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww\n\n");

    return astToStringRecursive(ast);
}

char* astToStringRecursive(TAst* ast) {
    if (ast == NULL) {
        return strdup(""); // Return an empty string for NULL ast
    }

    char* rootStr = nodeInfoToString(ast->root);
    printf("\n%s\n\n", rootStr);
    char* lsStr = astToStringRecursive(ast->ls);
    char* rsStr = astToStringRecursive(ast->rs);

    // Calculate the length of the final string
    size_t totalLength = strlen(rootStr) + strlen(lsStr) + strlen(rsStr) + 5; // +5 for formatting characters

    char* result = (char*)malloc(totalLength * sizeof(char));
    if (result == NULL) {
        // Handle memory allocation failure
        return NULL;
    }

    // Format the result string
    snprintf(result, totalLength, "[%s %s %s]", rootStr, lsStr, rsStr);

    free(rootStr);
    free(lsStr);
    free(rsStr);

    return result;
}