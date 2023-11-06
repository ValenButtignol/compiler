#include "../../include/algorithms/checktypes.h"

int checkTypes(TAst* ast, ErrorNode** errors) {
    checkForTypeErrors(ast, errors);

    if (*errors != NULL) {
        return 0;
    }

    return 1;
}   

void checkForTypeErrors(TAst* ast, ErrorNode** errors) {

    if (ast == NULL || isEmptyAst(*ast)) {
        return;
    }

    if(ast->data->type != NONETYPE){
        enum TType lsType = getAstType(ast->ls);
        enum TType rsType = getAstType(ast->rs);
        if(isAssignTag(ast->data->tag) || isArithmeticOrBooleanTag(ast->data->tag)){
            if(checkSonsFatherTypes(ast))
                addOperationError(errors, ast->data->lineNumber, ast->data->tag);
        }
        if(isRelationalOperatorTag(ast->data->tag)){
            if(checkSonsTypes(ast))
                addOperationError(errors, ast->data->lineNumber, ast->data->tag);
        }if(isReturnTag(ast->data->tag)){
            if(checkReturnTypes(ast)) 
                addOperationError(errors, ast->data->lineNumber, ast->data->tag);
        }
        // printf("TYPE = %s\n", typeToString(ast->data->type));
        if(ast->data->tag==METHOD_CALL){
            int methodNameSize = snprintf(NULL, 0, "%s", ast->data->id);
            char* methodName = malloc(methodNameSize + 1);
            sprintf(methodName, "%s", ast->rs->data->id);
            NodeInfo* currentParameters = ast->data->nextParams;
            NodeInfo* formalParameters = ast->rs->data->nextParams;
            while(currentParameters != NULL && formalParameters != NULL ){
                if(!(currentParameters->type == formalParameters->type)){
                    int errorStrLength = snprintf(NULL, 0, "\033[1;36mLine: %d \033[1;31mError:\033[0m Type mismatch in function %s call\n", (ast->data)->lineNumber, methodName);
                    char* errorStr = malloc(errorStrLength + 1);
                    sprintf(errorStr, "\033[1;36mLine: %d \033[1;31mError:\033[0m Type mismatch in function %s call\n", (ast->data)->lineNumber, methodName);
                    insertErrorNode(errors, errorStr);
                }
                currentParameters = currentParameters->nextParams;
                formalParameters = formalParameters->nextParams;
            }
            if(currentParameters != NULL){//dividir el if para diferenciar el error
                int errorStrLength = snprintf(NULL, 0, "\033[1;36mLine: %d \033[1;31mError:\033[0m To many parameters in function %s call\n", (ast->data)->lineNumber, methodName);
                char* errorStr = malloc(errorStrLength + 1);
                sprintf(errorStr, "\033[1;36mLine: %d \033[1;31mError:\033[0m To many parameters in function %s call\n", (ast->data)->lineNumber, methodName);
                insertErrorNode(errors, errorStr);
            }
            if(formalParameters != NULL){//dividir el if para diferenciar el error
                int errorStrLength = snprintf(NULL, 0, "\033[1;36mLine: %d \033[1;31m Error:\033[0m Miss parameters in function %s call\n", (ast->data)->lineNumber, methodName);
                char* errorStr = malloc(errorStrLength + 1);
                sprintf(errorStr, "\033[1;36mLine: %d \033[1;31m Error:\033[0m Miss parameters in function %s call\n", (ast->data)->lineNumber, methodName);
                insertErrorNode(errors, errorStr);
            }
        }
    }
    checkForTypeErrors(ast->ls, errors);
    checkForTypeErrors(ast->rs, errors);
}

enum TType getAstType(TAst* ast) { 
    if(ast==NULL) return NONETYPE;
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