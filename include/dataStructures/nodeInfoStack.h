#ifndef	NODE_INFO_STACK_H
#define NODE_INFO_STACK_H

#include <stdio.h>
#include <stdlib.h>
#include "nodeInfo.h"

typedef struct NodeInfoStack{
	struct NodeInfo* head;
}NodeInfoStack;

void pushTACNode(NodeInfoStack** stack, NodeInfo *node);
NodeInfo* popTACNode(NodeInfoStack** stack);
NodeInfoStack *createEmptyNodeInfoStack();
NodeInfo* popIfEquals(NodeInfoStack** stack, NodeInfo* param);
NodeInfo* top(NodeInfoStack** stack);
#endif
