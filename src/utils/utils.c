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
    int errorStrLength = snprintf(NULL, 0, "\033[1;36mLine: %d \033[1;31mError:\033[0m Type mismatch in \'\033[1;36m %s \033[0m \' \n", lineNumber, operatorToString(tag));
    char* errorStr = malloc(errorStrLength + 1);
    sprintf(errorStr, "\033[1;36mLine: %d \033[1;31mError:\033[0m Type mismatch in \'\033[1;36m %s \033[0m\' \n", lineNumber, operatorToString(tag));
    insertErrorNode(errors, errorStr);
}

void addMethodCallError(ErrorNode** errors, int lineNumber, char* message, char* methodName){
    int errorStrLength = snprintf(NULL, 0, "\033[1;36mLine: %d \033[1;31mError:\033[0m %s in function \'\033[1;36m %s \033[0m\' \n", lineNumber, message, methodName);
    char* errorStr = malloc(errorStrLength + 1);
    sprintf(errorStr, "\033[1;36mLine: %d \033[1;31mError:\033[0m %s in function \'\033[1;36m %s \033[0m\' \n", lineNumber, message, methodName);
    insertErrorNode(errors, errorStr);
}

int checkReturnTypes(TAst *ast){
    enum TType lsType = getAstType(ast->ls);
    return (!(lsType==ast->data->type) && !(VOID==ast->data->type && ast->ls==NULL && lsType==NONETYPE));
}

int checkSonsTypes(TAst *ast){
    return !(getAstType(ast->ls) == getAstType(ast->rs));
}

int checkSonsFatherTypes(TAst *ast){
    return !(!checkSonsTypes(ast) && (getAstType(ast->ls) == ast->data->type));
}
void copyMethodName(char **methodName,TAst *ast){
    int methodNameSize = snprintf(NULL, 0, "%s", ast->data->id);
    *methodName = malloc(methodNameSize + 1);
    sprintf(*methodName, "%s", ast->rs->data->id);
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