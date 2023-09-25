#include "../include/evalAstInputs.h"

void evalAstExpectedNodesFactory(char* inputTestFileName, TestingNodeInfoList* expectedNodes) {
    
    if (strcmp(inputTestFileName, "validInput1.txt") == 0) {
        evalAstExpectedNodesCreator1(expectedNodes);
    }

}

void evalAstExpectedNodesCreator1(TestingNodeInfoList* expectedNodes) {

    NodeInfo node;

    node = *newNodeInfo((int *)5, INTEGER, "a", VAR_DECL);// TID EXPR
    addNodeToTestingList(expectedNodes, node);
    node = *newEmptyNodeInfo();// Empty
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)5, INTEGER, "", RETURN);// Return
    addNodeToTestingList(expectedNodes, node);
    node = *newEmptyNodeInfo();// LAMBDA
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)3, INTEGER, "", CONST_VALUE);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)2, INTEGER, "", CONST_VALUE);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)5, INTEGER, "+", EXPR_OP);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)5, INTEGER, "a", VAR_DECL);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(INTEGER, "=", DECL);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", DECL_BLOCK);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", PROGRAM);
    addNodeToTestingList(expectedNodes, node);

}