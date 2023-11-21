#include "../../include/dataStructures/nodeInfoStack.h"

void pushTACNode(NodeInfoStack** stack, NodeInfo *node){
    node->nextParams = malloc(sizeof(NodeInfo));
    node->nextParams = (*stack)->head;
    (*stack)->head = node;
}

NodeInfo* popTACNode(NodeInfoStack** stack){
    NodeInfo* node = malloc(sizeof(NodeInfo));
    node = (*stack)->head;
    (*stack)->head = (*stack)->head->nextParams;
    return node;
}

NodeInfoStack *createEmptyNodeInfoStack(){
    NodeInfoStack *stack = malloc(sizeof(NodeInfoStack));
    stack->head = newEmptyNodeInfo();
    return stack;
}

NodeInfo* popIfEquals(NodeInfoStack** stack, NodeInfo* param){
    NodeInfo* t =  top(stack);
    if(t == NULL) return NULL; 
    if(nodeInfoIDEquals(t, param)) return popTACNode(stack);
    else return NULL;
}

NodeInfo* top(NodeInfoStack** stack){
    return (*stack)->head;
}