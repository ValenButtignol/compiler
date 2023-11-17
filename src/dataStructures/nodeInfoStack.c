#include "../../include/dataStructures/nodeInfoStack.h"

void pushTACNode(NodeInfoStack** stack, NodeInfo *node){
    printf("push %s\n");
    node->nextParams = malloc(sizeof(NodeInfo));
    node->nextParams = (*stack)->head;
    (*stack)->head = node;
}

NodeInfo* popTACNode(NodeInfoStack** stack){
    NodeInfo* node = malloc(sizeof(NodeInfo));
    node = (*stack)->head;
    (*stack)->head = (*stack)->head->nextParams;
    printf("pop\n");
    return node;
}

NodeInfoStack *createEmptyNodeInfoStack(){
    printf("create\n");
    NodeInfoStack *stack = malloc(sizeof(NodeInfoStack));
    stack->head = newEmptyNodeInfo();
    return stack;
}

NodeInfo* popIfEquals(NodeInfoStack** stack, NodeInfo* param){
    printf("popIFEQ\n");
    NodeInfo* t =  top(&stack);
    printf("t == %s\n", t->id);
    if(t == NULL) return NULL; 
    if(nodeInfoIDEquals(t, param)) return popTACNode(&stack);
    else return NULL;
}

NodeInfo* top(NodeInfoStack** stack){
    printf("top\n");
    return (*stack)->head;
}