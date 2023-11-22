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

int checkReturnTypes(TAst *ast){
    enum TType lsType = getAstType(ast->ls);
    return (!(lsType==ast->data->type) && !(VOID==ast->data->type && ast->ls==NULL && lsType==NONETYPE));
}

int checkFatherLeftSonTypes(TAst *ast){
    enum TType lsType = getAstType(ast->ls);
    return !(lsType==ast->data->type);
}

int checkSonsTypes(TAst *ast){
    return !(getAstType(ast->ls) == getAstType(ast->rs));
}

int checkSonsFatherTypes(TAst *ast){
    return !(!checkSonsTypes(ast) && (getAstType(ast->ls) == ast->data->type));
}

void checkDivByZero(TAst *ast, ErrorNode** errors){
    if(ast->data->tag == DIV || ast->data->tag == MOD){
        if(ast->rs->data->tag == CONST_VALUE && *((int*)ast->rs->data->value) == 0){
            addDivByZeroError(errors, ast->data->lineNumber, ast->data->tag);
        }
    }
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

char* getParamRegister(char* paramRegister) {
    char* result = malloc(5);
    strcpy(result, "");
    if (strcmp(paramRegister, "1") == 0) {
        strcpy(result, "%rdi");
    } else if (strcmp(paramRegister, "2") == 0) {
        strcpy(result, "%rsi");
    } else if (strcmp(paramRegister, "3") == 0) {
        strcpy(result, "%rdx");
    } else if (strcmp(paramRegister, "4") == 0) {
        strcpy(result, "%rcx");
    } else if (strcmp(paramRegister, "5") == 0) {
        strcpy(result, "%r8");
    } else if (strcmp(paramRegister, "6") == 0) {
        strcpy(result, "%r9");
    }
    return result;
}

int hasBokExtension(const char* fileName) {
    // Find the last occurrence of '.' in the file name
    const char* dotPosition = strrchr(fileName, '.');

    // Check if there is a dot and if the extension is ".bok"
    if (dotPosition != NULL && strcmp(dotPosition, ".bok") == 0) {
        return 1;
    } else {
        return 0;
    }
}