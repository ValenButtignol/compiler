#include "../include/evalAstInputs.h"

void evalAstExpectedNodesFactory(char* inputTestFileName, TestingNodeInfoList* expectedNodes) {
    
    if (strcmp(inputTestFileName, "validInput1.txt") == 0) {
        evalAstExpectedNodesCreator1(expectedNodes);
    }

}

void evalAstExpectedNodesCreator1(TestingNodeInfoList* expectedNodes) {

    NodeInfo node;

    node = *newNodeInfo((int *)5, INTEGER, "a", VAR_DECL,0);// TID EXPR
    addNodeToTestingList(expectedNodes, node);
    node = *newEmptyNodeInfo();// Empty
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)5, INTEGER, "", RETURN,0);// Return
    addNodeToTestingList(expectedNodes, node);
    node = *newEmptyNodeInfo();// LAMBDA
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)3, INTEGER, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)2, INTEGER, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)5, INTEGER, "+", EXPR_OP,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)5, INTEGER, "a", VAR_DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(INTEGER, "=", DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", DECL_BLOCK,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", PROGRAM,0);
    addNodeToTestingList(expectedNodes, node);

}