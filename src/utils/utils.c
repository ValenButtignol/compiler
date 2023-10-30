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