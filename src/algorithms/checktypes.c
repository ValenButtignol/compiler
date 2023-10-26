#include "../../include/algorithms/checktypes.h"

int checkTypes(TAst* ast, ErrorNode** errors) {
    setTypesInAst(ast, errors);

    if (*errors != NULL) {
        return 0;
    }

    return 1;
}   

void setTypesInAst(TAst* ast, ErrorNode** errors) {
    printf("Tag = %s\n", ast==NULL?"NULL":"NO NULL");
    if (ast == NULL || isEmptyAst(*ast) || (ast->data)->type != NONETYPE) {
        return;
    }

    if (isTypeableTag(ast->data->tag) && (ast->data)->type == NONETYPE) {
        if ((ast->data)->tag == RETURN || (ast->data)->tag == NOT || (ast->data)->tag == NEGATIVE){
            (ast->data)->type = getAstType(ast->rs);
            return;
        }
        //LOS SIGUIENTES TAG SE TRATATN DE ESTA MANERA :: 
        //VAR_DECL
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
        //TAGS QUE VIENEN CON EL TIPO DESDE EL AST
        //VAR
        setTypesInAst(ast->ls, errors);
        setTypesInAst(ast->rs, errors);
    }
}

enum TType getAstType(TAst* ast) {
    if ((ast->data)->type != NONETYPE) {
        return (ast->data)->type;
    }
    enum TType lsType = getAstType(ast->ls);
    enum TType rsType = getAstType(ast->rs);
    if (lsType != rsType) {
        return ERROR;
    }
    (ast->data)->type = lsType;
    return lsType;

}