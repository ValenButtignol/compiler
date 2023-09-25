#include "../include/checkTypesInputs.h"

void checkTypesExpectedNodesFactory(char* inputTestFileName, TestingNodeInfoList* expectedNodes) {
    
    if (strcmp(inputTestFileName, "validInput1.txt") == 0) {
        checkTypesExpectedNodesCreator1(expectedNodes);
    }

}

void checkTypesExpectedNodesCreator1(TestingNodeInfoList* expectedNodes) {

    NodeInfo node;

    node = *newNodeInfoWithoutValue(INTEGER, "a", VAR_DECL);
    addNodeToTestingList(expectedNodes, node);
    node = *newEmptyNodeInfo();// Empty
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(INTEGER, "", RETURN);// Return
    addNodeToTestingList(expectedNodes, node);
    node = *newEmptyNodeInfo();// LAMBDA
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)3, INTEGER, "", CONST_VALUE);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)2, INTEGER, "", CONST_VALUE);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(INTEGER, "+", EXPR_OP);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(INTEGER, "a", VAR_DECL);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(INTEGER, "=", DECL);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", DECL_BLOCK);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", PROGRAM);
    addNodeToTestingList(expectedNodes, node);

}