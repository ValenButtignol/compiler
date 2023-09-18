#include <stdio.h>
#include <stdlib.h>

#include "../include/ast.h"

TAst* newAst(NodeInfo *root, TAst* ls, TAst* rs) {
    TAst* ast = (TAst*) malloc(sizeof(TAst));

    ast->data = *root;
    ast->ls = ls;
    ast->rs = rs;
    return ast;
}

TAst* newEmptyAst() {
    TAst *ast = (TAst*) malloc(sizeof(TAst));
    ast->data = *newEmptyNodeInfo();
    ast->ls = NULL;
    ast->rs = NULL;
    return ast;
}

int isEmptyAst(TAst ast) {
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
    if (!isEmptyNode(ast->data)) rootStr = nodeInfoToString(ast->data);
    else {
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
int isTypeTag(TAst ast){
    return  ast.data.tag == EXPR_OP || ast.data.tag == VAR_DECL || ast.data.tag == DECL 
              || ast.data.tag == CONST_DECL || ast.data.tag == ASSIGNMENT_OP;
}

int checkType(TAst* ast)  {
    
    if (ast == NULL || isEmptyAst(*ast)) return 1;
    if(ast->data.type == ERROR) return 0;

    if (ast->data.type == NONETYPE && isTypeTag(*ast)) {
        ast->data.type = getAstType(ast);
        if (getAstType(ast->ls) != getAstType(ast->rs)) {
            return 0;
        }
    }
    return checkType(ast->ls) && checkType(ast->rs);
}

enum TType getAstType(TAst* ast) {
    if (ast == NULL || isEmptyAst(*ast)) {
        printf("\033[1;31m");
        printf("Missing operating\n");
        printf("\033[0m"); // Reset text color to default
        exit(1);
    } else if (ast->data.type != NONETYPE) {
        return ast->data.type;
    } else if (ast->data.type == NONETYPE) {
        enum TType lsType = getAstType(ast->ls);
        enum TType rsType = getAstType(ast->ls);
        if (lsType != rsType) {
            return ERROR;
        }
        return lsType;
    }
}

void evaluateAst(TAst* ast) {
    enum TTag treeTag = ast->data.tag;
    if (treeTag == DECL) {
        evaluateExpression(ast->rs);
        setValue(&ast->ls->data, ast->rs->data.value, ast->rs->data.type);
    
    } else if (treeTag == EXPR_OP) {
        evaluateExpression(ast);
        
    } else if (treeTag == ASSIGNMENT_OP) {
        evaluateExpression(ast->rs);
        setValue(&ast->ls->data, ast->rs->data.value, ast->rs->data.type);
    
    } else if (treeTag == RETURN) {
        evaluateExpression(ast->rs);
        setValue(&ast->data, ast->rs->data.value, ast->rs->data.type);
    
    } else if (treeTag == NONETAG) {
        return;
    
    } else {
        evaluateAst(ast->ls);
        evaluateAst(ast->rs);
    }
}

void evaluateExpression(TAst* ast) {
    char* treeOperator = ast->data.id;

    if (ast->data.type == INTEGER) {
        int result;
        if (treeOperator == "+") {
            result = evaluateInteger(ast->ls) + evaluateInteger(ast->rs);

        } else if (treeOperator == "-") {
            result = evaluateInteger(ast->ls) - evaluateInteger(ast->rs);

        } else if (treeOperator == "*") {
            result = evaluateInteger(ast->ls) * evaluateInteger(ast->rs);

        } else if (treeOperator == "/") {
            int divider = evaluateInteger(ast->rs);
            if (divider == 0) {
                printf("Can't Divide for 0\n");
                exit(1);
            }
            result = evaluateInteger(ast->ls) / divider;
            
        }
        setValue(&ast->data, (void*)&result, INTEGER);
    }

    if (ast->data.type == BOOLEAN) {
        int result;
        if (treeOperator == "+") {
            result = evaluateBoolean(ast->ls) || evaluateBoolean(ast->rs);
        } else if (treeOperator == "*") {
            result = evaluateBoolean(ast->ls) && evaluateBoolean(ast->rs);
        }
        setValue(&ast->data, (void*)&result, BOOLEAN);
    }
}

int evaluateInteger(TAst* ast) {
    if (ast->data.value != NULL) {
        return *((int*)ast->data.value); 
    } else {
        evaluateExpression(ast->ls);
        evaluateExpression(ast->rs);
    }
}

int evaluateBoolean(TAst* ast) {
    if (ast->data.value != NULL) {
        return *((int*)ast->data.value); 
    } else {
        evaluateExpression(ast->ls);
        evaluateExpression(ast->rs);
    }
}