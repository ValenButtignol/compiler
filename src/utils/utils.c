#include "../../include/utils/utils.h"

void setParamsToNodeInfo(NodeInfo** node, TAst* ast){
    if (ast == NULL || isEmptyAst(*ast)) return;
    TAst* parameterTreeNode = ast;
    
    NodeInfo* currentNode = *node; 
    
    while (parameterTreeNode != NULL) {
        currentNode->nextParams = parameterTreeNode->data;
        
        currentNode = currentNode->nextParams;
        parameterTreeNode = parameterTreeNode->ls;
    }
        
    return ;
}

void addOperationError(ErrorNode** errors, int lineNumber, enum TTag tag){
    int errorStrLength = snprintf(NULL, 0, "\033[1;36mLine: %d \033[1;31mError:\033[0m Type mismatch in \'%s\'\n", lineNumber, operatorToString(tag));
    char* errorStr = malloc(errorStrLength + 1);
    sprintf(errorStr, "\033[1;36mLine: %d \033[1;31mError:\033[0m Type mismatch in \'%s\'\n", lineNumber, operatorToString(tag));
    insertErrorNode(errors, errorStr);
}

int checkReturnTypes(TAst *ast){
    enum TType lsType = getAstType(ast->ls);
    return !((lsType==ast->data->type) && (VOID==ast->data->type && ast->ls==NULL && lsType==NONETYPE));
}

int checkSonsTypes(TAst *ast){
    return !(getAstType(ast->ls) == getAstType(ast->rs));
}

int checkSonsFatherTypes(TAst *ast){
    return !(!checkSonsTypes(ast) && getAstType(ast->ls) == ast->data->type);
}