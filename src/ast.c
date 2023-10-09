#include <stdio.h>
#include <stdlib.h>

#include "../include/ast.h"

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

char* astToString(TAst* ast) {
    return astToStringRecursive(ast);
}

char* astToStringRecursive(TAst* ast) {
    if (ast == NULL || isEmptyAst(*ast)) {
        return strdup(""); // Return an empty string for NULL ast
    }

    char* lsStr = astToStringRecursive(ast->ls);
    char* rootStr;
    if (!isEmptyNode(*ast->data)) rootStr = nodeInfoToString(*ast->data);
    else {
        rootStr = malloc(sizeof(""));
        strcpy(rootStr, ""); 
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
    enum TTag tag = (ast.data)->tag;
    return tag == EXPR_OP || tag == VAR_DECL || tag == DECL 
              || tag == CONST_DECL || tag == ASSIGNMENT_OP || tag == RETURN;
}


int checkTypes(TAst* ast, ErrorNode** errors) {
    setTypesInAst(ast, errors);

    if (*errors != NULL) {
        return 0;
    }

    return 1;
}

void setTypesInAst(TAst* ast, ErrorNode** errors) {
    if (ast == NULL || isEmptyAst(*ast) || (ast->data)->type != NONETYPE) {
        return;
    }

    if (isTypeableTag(*ast) && (ast->data)->type == NONETYPE) {
        if ((ast->data)->tag == RETURN) {
            (ast->data)->type = getAstType(ast->rs);
            return;
        }

        enum TType lsType = getAstType(ast->ls);
        enum TType rsType = getAstType(ast->rs);

        
        if (lsType != rsType || lsType == ERROR || rsType == ERROR) {
            char* errorStr = malloc(50);
            sprintf(errorStr, "\033[1;31mLine: %d Error:\033[0m Type mismatch\n", (ast->data)->lineNumber);
            insertErrorNode(errors, errorStr);    // Add line number in &(ast->data)->lineNumber
            (ast->data)->type = ERROR;
        } else {
            (ast->data)->type = lsType;
            return;
        }
    } else {
        setTypesInAst(ast->ls, errors);
        setTypesInAst(ast->rs, errors);
    }
}

enum TType getAstType(TAst* ast) {
    if ((ast->data)->type != NONETYPE) {
        return (ast->data)->type;
    }
    switch ((ast->data)->tag) {
        case EXPR_OP:
            enum TType lsType = getAstType(ast->ls);
            enum TType rsType = getAstType(ast->rs);
            if (lsType != rsType) {
                return ERROR;
            }
            (ast->data)->type = lsType;
            return lsType;

        default:
            return (ast->data)->type;
    }
}

void evaluateAst(TAst* ast) {
    enum TTag treeTag = (ast->data)->tag;
    if (treeTag == DECL) {
        evaluateExpression(ast->rs);   
        setValue(&(ast->ls->data), (ast->rs->data)->value, (ast->rs->data)->type);
    } else if (treeTag == EXPR_OP) {
        evaluateExpression(ast);
        
    } else if (treeTag == ASSIGNMENT_OP) {
        evaluateExpression(ast->rs);
        setValue(&(ast->ls->data), (ast->rs->data)->value, (ast->rs->data)->type);
    
    } else if (treeTag == RETURN) {
        evaluateExpression(ast->rs);
        setValue(&(ast->data), (ast->rs->data)->value, (ast->rs->data)->type);
    
    } else if (treeTag == NONETAG) {
        return;
    } else {
        evaluateAst(ast->ls);
        evaluateAst(ast->rs);
    }
}

void evaluateExpression(TAst* ast) {
    enum TOperator treeOperator = (ast->data)->operator;
    if ((ast->data)->type == INTEGER) {
        int *result = malloc(sizeof(int*));
        if (treeOperator == PLUS) {
            int a = evaluateInteger(ast->ls);
            int b = evaluateInteger(ast->rs);
            *result =  a + b;
        } else if (treeOperator == MINUS) {
            int a = evaluateInteger(ast->ls);
            int b = evaluateInteger(ast->rs);
            *result =  a - b;
        } else if (treeOperator == MULTIPLY) {
            *result = evaluateInteger(ast->ls) * evaluateInteger(ast->rs);

        } else if (treeOperator == DIVIDE) {
            int divider = evaluateInteger(ast->rs);
            if (divider == 0) {
                printf("\033[1;31mLine: %d Error:\033[0m Can't Divide for 0\n", (ast->data)->lineNumber);
                exit(1);
            }
            *result = evaluateInteger(ast->ls) / divider;
            
        }else if(treeOperator == NONOPERATOR){
            return;
        }
        setValue(&(ast->data), (void*)result, INTEGER);
    }

    if ((ast->data)->type == BOOLEAN) {
        int *result = malloc(sizeof(int*));
        if (treeOperator == PLUS) {//TODO: PODRIAMOS ACTUALIZAR EL PLUS POR OR
            *result = evaluateBoolean(ast->ls) || evaluateBoolean(ast->rs);
        } else if (treeOperator == MULTIPLY) {
            *result = evaluateBoolean(ast->ls) && evaluateBoolean(ast->rs);
        }else if (treeOperator == MINUS || treeOperator == DIVIDE) {
            printf("\033[1;31mLine: %d Error:\033[0m Can't do %s in booleans\n", 
                    (ast->data)->lineNumber, operatorToString(treeOperator)
            );
            exit(1);
        }else if(treeOperator == NONOPERATOR){
            int* a = ast->data->value;
            return;
        }           // TODO: ADD INVALID OPERATORS AS ERRORS. 
        setValue(&(ast->data), (void*)result, BOOLEAN);
    }
}

int evaluateInteger(TAst* ast) {
    if ((ast->data)->value != NULL) {
        return *((int*)(ast->data)->value); 
    } else {
        evaluateExpression(ast);
    }
}

int evaluateBoolean(TAst* ast) {
    if (&(ast->data)->value != NULL) {
        return *((int *)(ast->data)->value); 
    } else {
        evaluateExpression(ast);
    }
}

int isLeaf(TAst *ast){
    return (ast->ls == NULL && ast->rs == NULL);   
}