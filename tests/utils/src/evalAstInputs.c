#include "../include/evalAstInputs.h"

void evalAstExpectedNodesFactory(char* inputTestFileName, TestingNodeInfoList* expectedNodes) {
    
    if(strstr(inputTestFileName, "invalid")!=NULL){
        return;
    }
    if (strcmp(inputTestFileName, "validInput1.txt") == 0) {
        evalAstExpectedNodesCreator1(expectedNodes);
    }else if (strcmp(inputTestFileName, "validInput2.txt") == 0) {
        evalAstExpectedNodesCreator2(expectedNodes);
    }else if (strcmp(inputTestFileName, "validInput3.txt") == 0) {
        evalAstExpectedNodesCreator3(expectedNodes);
    }else if (strcmp(inputTestFileName, "validInput4.txt") == 0) {
        evalAstExpectedNodesCreator4(expectedNodes);
    }else if (strcmp(inputTestFileName, "validInput5.txt") == 0) {
        evalAstExpectedNodesCreator5(expectedNodes);
    }else if (strcmp(inputTestFileName, "validInput6.txt") == 0) {
        evalAstExpectedNodesCreator6(expectedNodes);
    }else if (strcmp(inputTestFileName, "validInput7.txt") == 0) {
        evalAstExpectedNodesCreator7(expectedNodes);
    }else if (strcmp(inputTestFileName, "validInput8.txt") == 0) {
        evalAstExpectedNodesCreator8(expectedNodes);
    }else if (strcmp(inputTestFileName, "validInput9.txt") == 0) {
        evalAstExpectedNodesCreator9(expectedNodes);
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

void evalAstExpectedNodesCreator2(TestingNodeInfoList* expectedNodes) {
    NodeInfo node;
    printf("FILE 2\n\n");

    node = *newNodeInfo(6, INTEGER, "a", VAR_DECL, 0);
    addNodeToTestingList(expectedNodes, node);
    node = *newEmptyNodeInfo();// Empty
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo(6, INTEGER, "", RETURN, 0);// Return
    addNodeToTestingList(expectedNodes, node);
    node = *newEmptyNodeInfo();// LAMBDA
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)3, INTEGER, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)2, INTEGER, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)6, INTEGER, "*", EXPR_OP,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo(6, INTEGER, "a", VAR_DECL, 0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(INTEGER, "=", DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", DECL_BLOCK,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", PROGRAM,0);
    addNodeToTestingList(expectedNodes, node);

}

void evalAstExpectedNodesCreator3(TestingNodeInfoList* expectedNodes) {

    NodeInfo node;
    node = *newNodeInfo(-1, INTEGER, "a", VAR_DECL, 0);
    addNodeToTestingList(expectedNodes, node);
    node = *newEmptyNodeInfo();// Empty
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo(-1, INTEGER, "", RETURN, 0);// Return
    addNodeToTestingList(expectedNodes, node);
    node = *newEmptyNodeInfo();// LAMBDA
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)3, INTEGER, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)2, INTEGER, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)-1, INTEGER, "-", EXPR_OP,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo(-1, INTEGER, "a", VAR_DECL, 0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(INTEGER, "=", DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", DECL_BLOCK,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", PROGRAM,0);
    addNodeToTestingList(expectedNodes, node);

}

void evalAstExpectedNodesCreator4(TestingNodeInfoList* expectedNodes) {

    NodeInfo node;

    node = *newNodeInfo(2, INTEGER, "a", VAR_DECL, 0);
    addNodeToTestingList(expectedNodes, node);
    node = *newEmptyNodeInfo();// Empty
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo(2, INTEGER, "", RETURN, 0);// Return
    addNodeToTestingList(expectedNodes, node);
    node = *newEmptyNodeInfo();// LAMBDA
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)2, INTEGER, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)4, INTEGER, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)2, INTEGER, "/", EXPR_OP,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo(2, INTEGER, "a", VAR_DECL, 0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(INTEGER, "=", DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", DECL_BLOCK,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", PROGRAM,0);
    addNodeToTestingList(expectedNodes, node);

}

void evalAstExpectedNodesCreator5(TestingNodeInfoList* expectedNodes) {

    NodeInfo node;
    node = *newNodeInfo(1, BOOLEAN, "a", VAR_DECL, 0);
    addNodeToTestingList(expectedNodes, node);
    node = *newEmptyNodeInfo();// Empty
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo(1, BOOLEAN, "", RETURN, 0);// Return
    addNodeToTestingList(expectedNodes, node);
    node = *newEmptyNodeInfo();// LAMBDA
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)1, BOOLEAN, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo(1, BOOLEAN, "a", VAR_DECL, 0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(BOOLEAN, "=", DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", DECL_BLOCK,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", PROGRAM,0);
    addNodeToTestingList(expectedNodes, node);

}

void evalAstExpectedNodesCreator6(TestingNodeInfoList* expectedNodes) {

    NodeInfo node;
    node = *newNodeInfo(0, BOOLEAN, "a", VAR_DECL, 0);
    addNodeToTestingList(expectedNodes, node);
    node = *newEmptyNodeInfo();// Empty
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo(0, BOOLEAN, "", RETURN, 0);// Return
    addNodeToTestingList(expectedNodes, node);
    node = *newEmptyNodeInfo();// LAMBDA
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)0, BOOLEAN, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo(0, BOOLEAN, "a", VAR_DECL, 0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(BOOLEAN, "=", DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", DECL_BLOCK,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", PROGRAM,0);
    addNodeToTestingList(expectedNodes, node);

}

void evalAstExpectedNodesCreator7(TestingNodeInfoList* expectedNodes) {

    NodeInfo node;

    node = *newNodeInfo(1, BOOLEAN, "a", VAR_DECL, 0);
    addNodeToTestingList(expectedNodes, node);
    node = *newEmptyNodeInfo();// Empty
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo(1, BOOLEAN, "", RETURN, 0);// Return
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)1, BOOLEAN, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo(1, BOOLEAN, "a", VAR_DECL, 0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo(1, BOOLEAN, "+", EXPR_OP,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo(1, BOOLEAN, "a", VAR_DECL, 0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(BOOLEAN, "=", ASSIGNMENT_OP, 0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", STMT_BLOCK,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newEmptyNodeInfo();// LAMBDA
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)0, BOOLEAN, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)0, BOOLEAN, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)0, BOOLEAN, "+", EXPR_OP,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo(1, BOOLEAN, "a", VAR_DECL, 0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)0, BOOLEAN, "=", DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", DECL_BLOCK,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", PROGRAM,0);
    addNodeToTestingList(expectedNodes, node);

}

void evalAstExpectedNodesCreator8(TestingNodeInfoList* expectedNodes) {

    NodeInfo node;

    node = *newNodeInfo((int *)1, BOOLEAN, "a", VAR_DECL,0);// TID EXPR
    addNodeToTestingList(expectedNodes, node);
    node = *newEmptyNodeInfo();// Empty
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)1, BOOLEAN, "", RETURN,0);// Return
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)0, BOOLEAN, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)0, BOOLEAN, "b", VAR_DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)0, BOOLEAN, "*", EXPR_OP,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)0, BOOLEAN, "b", VAR_DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)0, BOOLEAN, "=", ASSIGNMENT_OP,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", STMT_BLOCK,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)1, BOOLEAN, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)0, BOOLEAN, "b", VAR_DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)1, BOOLEAN, "*", EXPR_OP,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)1, BOOLEAN, "a", VAR_DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)0, BOOLEAN, "=", ASSIGNMENT_OP,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", STMT_BLOCK,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newEmptyNodeInfo();// LAMBDA
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)1, BOOLEAN, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)1, BOOLEAN, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)1, BOOLEAN, "*", EXPR_OP,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)0, BOOLEAN, "b", VAR_DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)0, BOOLEAN, "=", DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", DECL_BLOCK,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)0, BOOLEAN, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)1, BOOLEAN, "a", VAR_DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)0, BOOLEAN, "=", DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", DECL_BLOCK,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", PROGRAM,0);
    addNodeToTestingList(expectedNodes, node);

}

void evalAstExpectedNodesCreator9(TestingNodeInfoList* expectedNodes) {

    NodeInfo node;

    node = *newNodeInfo((int *)40, INTEGER, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)2, INTEGER, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)2, INTEGER, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(INTEGER, "-", EXPR_OP,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)40, INTEGER, "+", EXPR_OP,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)40, INTEGER, "b", VAR_DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(INTEGER, "=", ASSIGNMENT_OP, 0);
    addNodeToTestingList(expectedNodes, node);
    node = *newEmptyNodeInfo();// LAMBDA
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)0, INTEGER, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)40, INTEGER, "b", VAR_DECL, 0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(INTEGER, "=", DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", DECL_BLOCK,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)1, BOOLEAN, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)0, BOOLEAN, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(BOOLEAN, "*", EXPR_OP,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)1, BOOLEAN, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)1, BOOLEAN, "+", EXPR_OP,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)1, BOOLEAN, "a", VAR_DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(BOOLEAN, "=", DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", DECL_BLOCK,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", PROGRAM,0);
    addNodeToTestingList(expectedNodes, node);

}