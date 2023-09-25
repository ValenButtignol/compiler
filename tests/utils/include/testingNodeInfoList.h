#ifndef UTILS_NODEINFO_LIST_H
#define UTILS_NODEINFO_LIST_H

#include "../../../include/ast.h"
#include "../../../include/nodeInfo.h"

// Define the Node structure for the linked list
typedef struct TestingNode {
    NodeInfo data;
    struct TestingNode* next;
} TestingNode;

// Define the LinkedList structure
typedef struct {
    TestingNode* head;
} TestingNodeInfoList;

TestingNodeInfoList* newTestingNodeInfoList();

void addNodeToTestingList(TestingNodeInfoList* list, NodeInfo data);

void freeTestingNodeInfoList(TestingNodeInfoList* list);

#endif