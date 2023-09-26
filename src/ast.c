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

int isTypeableTag(TAst ast){
    return  ast.data.tag == EXPR_OP || ast.data.tag == VAR_DECL || ast.data.tag == DECL 
              || ast.data.tag == CONST_DECL || ast.data.tag == ASSIGNMENT_OP || ast.data.tag == RETURN;
}

void setTypesInAst(TAst* ast) {
    if (ast == NULL || isEmptyAst(*ast) || ast->data.type != NONETYPE) {
        return;
    }

    if (isTypeableTag(*ast) && ast->data.type == NONETYPE) {
        if (ast->data.tag == RETURN) {
            ast->data.type = getAstType(ast->rs);
            return;
        }

        enum TType lsType = getAstType(ast->ls);
        enum TType rsType = getAstType(ast->rs);
        
        if (lsType != rsType || lsType == ERROR || rsType == ERROR) {
            printf("\033[1;31mLine: %d Error:\033[0m Type mismatch\n", ast->data.lineNumber);
            return;
        }
        ast->data.type = rsType;
        return;
    }

    setTypesInAst(ast->ls);
    setTypesInAst(ast->rs); 
}

enum TType getAstType(TAst* ast) {
    if (ast->data.type != NONETYPE) {
        return ast->data.type;
    }
    switch (ast->data.tag) {
        case EXPR_OP:
            enum TType lsType = getAstType(ast->ls);
            enum TType rsType = getAstType(ast->rs);
            if (lsType != rsType) {
                return ERROR;       // Maybe is good to return the line number, or show the error here.
            }
            return lsType;

        default:
            return ast->data.type;
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
                printf("\033[1;31mLine: %d Error:\033[0m Can't Divide for 0\n", ast->data.lineNumber);
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

int isLeaf(TAst *ast){
    return (ast->ls == NULL && ast->rs == NULL);   
}