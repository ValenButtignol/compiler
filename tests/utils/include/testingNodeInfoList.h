#ifndef UTILS_NODEINFO_LIST_H
#define UTILS_NODEINFO_LIST_H

#include "../../../include/dataStructures/ast.h"
#include "../../../include/dataStructures/nodeInfo.h"

typedef struct TestingNode {
    NodeInfo* data;
    struct TestingNode* next;
} TestingNode;

typedef struct {
    TestingNode* head;
} TestingNodeInfoList;

TestingNodeInfoList* newTestingNodeInfoList();

void addNodeToTestingList(TestingNodeInfoList** list, NodeInfo* data);

void freeTestingNodeInfoList(TestingNodeInfoList* list);

#endif