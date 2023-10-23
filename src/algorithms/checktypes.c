#include "../../include/algorithms/checktypes.h"

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

    if (isTypeableTag(ast->data->tag) && (ast->data)->type == NONETYPE) {
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