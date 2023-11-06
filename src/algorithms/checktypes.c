#include "../../include/algorithms/checktypes.h"

int checkTypes(TAst* ast, ErrorNode** errors) {
    checkForTypeErrors(ast, errors);

    if (*errors != NULL) {
        return 0;
    }

    return 1;
}

void checkForTypeErrors(TAst* ast, ErrorNode** errors) {

    if (ast == NULL || isEmptyAst(*ast))
        return;

    if(ast->data->type != NONETYPE){
        enum TType lsType = getAstType(ast->ls);
        enum TType rsType = getAstType(ast->rs);
        if(isAssignTag(ast->data->tag) || isArithmeticOrBooleanTag(ast->data->tag)){
            if(checkSonsFatherTypes(ast))
                addOperationError(errors, ast->data->lineNumber, ast->data->tag);
        }else if(isRelationalOperatorTag(ast->data->tag)){
            if(checkSonsTypes(ast))
                addOperationError(errors, ast->data->lineNumber, ast->data->tag);
        }else if(isReturnTag(ast->data->tag)){
            if(checkReturnTypes(ast)) 
                addOperationError(errors, ast->data->lineNumber, ast->data->tag);
        }else if(isMethodCallTag(ast->data->tag)){
            char* methodName;
            copyMethodName(&methodName ,ast);
            NodeInfo* currentParameters = ast->data->nextParams;
            NodeInfo* formalParameters = ast->rs->data->nextParams;
            
            while(currentParameters != NULL && formalParameters != NULL ){
                if(!(currentParameters->type == formalParameters->type))
                    addMethodCallError(errors, (ast->data)->lineNumber, "Type mismatch", methodName);
                currentParameters = currentParameters->nextParams;
                formalParameters = formalParameters->nextParams;
            }

            if(currentParameters != NULL)
                addMethodCallError(errors, (ast->data)->lineNumber, "To many parameters", methodName);

            if(formalParameters != NULL)
                addMethodCallError(errors, (ast->data)->lineNumber, "Miss parameters", methodName);
        }
    }
    checkForTypeErrors(ast->ls, errors);
    checkForTypeErrors(ast->rs, errors);
}