#include "../include/checkTypesInputs.h"

void checkTypesExpectedNodesFactory(char* inputTestFileName, TestingNodeInfoList* expectedNodes) {
    
    if (strcmp(inputTestFileName, "validInput1.txt") == 0) {
        checkTypesExpectedNodesCreator1(expectedNodes);
    }

}

void checkTypesExpectedNodesCreator1(TestingNodeInfoList* expectedNodes) {

    NodeInfo node;

    node = *newNodeInfoWithoutValue(INTEGER, "a", VAR_DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newEmptyNodeInfo();// Empty
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(INTEGER, "", RETURN,0);// Return
    addNodeToTestingList(expectedNodes, node);
    node = *newEmptyNodeInfo();// LAMBDA
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)3, INTEGER, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)2, INTEGER, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(INTEGER, "+", EXPR_OP,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(INTEGER, "a", VAR_DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(INTEGER, "=", DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", DECL_BLOCK,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", PROGRAM,0);
    addNodeToTestingList(expectedNodes, node);

}