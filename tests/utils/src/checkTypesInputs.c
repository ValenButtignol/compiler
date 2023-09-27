#include "../include/checkTypesInputs.h"

void checkTypesFactory(char* inputTestFileName, TestingNodeInfoList* expectedNodes, ErrorNode** expectedErrors) {
    
    if (strcmp(inputTestFileName, "validInput1.txt") == 0) {
        checkTypesExpectedNodesCreator1(expectedNodes);
    } else if (strcmp(inputTestFileName, "validInput2.txt") == 0) {
        checkTypesExpectedNodesCreator2(expectedNodes);
    } else if (strcmp(inputTestFileName, "validInput3.txt") == 0) {
        checkTypesExpectedNodesCreator3(expectedNodes);
    } else if (strcmp(inputTestFileName, "validInput4.txt") == 0) {
        checkTypesExpectedNodesCreator4(expectedNodes);
    } else if (strcmp(inputTestFileName, "validInput5.txt") == 0) {
        checkTypesExpectedNodesCreator5(expectedNodes);
    } else if (strcmp(inputTestFileName, "validInput6.txt") == 0) {
        checkTypesExpectedNodesCreator6(expectedNodes);
    } else if (strcmp(inputTestFileName, "validInput7.txt") == 0) {
        checkTypesExpectedNodesCreator7(expectedNodes);
    } else if (strcmp(inputTestFileName, "validInput8.txt") == 0) {
        checkTypesExpectedNodesCreator8(expectedNodes);
    } else if (strcmp(inputTestFileName, "validInput9.txt") == 0) {
        checkTypesExpectedNodesCreator9(expectedNodes);
    } else if (strcmp(inputTestFileName, "invalidInput1.txt") == 0) {
        checkTypesErrorListCreator1(expectedErrors);
    } else if (strcmp(inputTestFileName, "invalidInput2.txt") == 0) {
        checkTypesErrorListCreator2(expectedErrors);
    } else if (strcmp(inputTestFileName, "invalidInput3.txt") == 0) {
        checkTypesErrorListCreator3(expectedErrors);
    } else if (strcmp(inputTestFileName, "invalidInput4.txt") == 0) {
        checkTypesErrorListCreator4(expectedErrors);
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


void checkTypesExpectedNodesCreator2(TestingNodeInfoList* expectedNodes) {

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
    node = *newNodeInfoWithoutValue(INTEGER, "*", EXPR_OP,0);
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


void checkTypesExpectedNodesCreator3(TestingNodeInfoList* expectedNodes) {

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
    node = *newNodeInfoWithoutValue(INTEGER, "-", EXPR_OP,0);
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

void checkTypesExpectedNodesCreator4(TestingNodeInfoList* expectedNodes) {

    NodeInfo node;

    node = *newNodeInfoWithoutValue(INTEGER, "a", VAR_DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newEmptyNodeInfo();// Empty
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(INTEGER, "", RETURN,0);// Return
    addNodeToTestingList(expectedNodes, node);
    node = *newEmptyNodeInfo();// LAMBDA
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)2, INTEGER, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)4, INTEGER, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(INTEGER, "/", EXPR_OP,0);
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

void checkTypesExpectedNodesCreator5(TestingNodeInfoList* expectedNodes) {

    NodeInfo node;
    node = *newNodeInfoWithoutValue(BOOLEAN, "a", VAR_DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newEmptyNodeInfo();// Empty
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(BOOLEAN, "", RETURN,0);// Return
    addNodeToTestingList(expectedNodes, node);
    node = *newEmptyNodeInfo();// LAMBDA
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)1, BOOLEAN, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(BOOLEAN, "a", VAR_DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(BOOLEAN, "=", DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", DECL_BLOCK,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", PROGRAM,0);
    addNodeToTestingList(expectedNodes, node);

}

void checkTypesExpectedNodesCreator6(TestingNodeInfoList* expectedNodes) {

    NodeInfo node;
    node = *newNodeInfoWithoutValue(BOOLEAN, "a", VAR_DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newEmptyNodeInfo();// Empty
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(BOOLEAN, "", RETURN,0);// Return
    addNodeToTestingList(expectedNodes, node);
    node = *newEmptyNodeInfo();// LAMBDA
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)0, BOOLEAN, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(BOOLEAN, "a", VAR_DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(BOOLEAN, "=", DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", DECL_BLOCK,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", PROGRAM,0);
    addNodeToTestingList(expectedNodes, node);

}

void checkTypesExpectedNodesCreator7(TestingNodeInfoList* expectedNodes) {

    NodeInfo node;

    node = *newNodeInfoWithoutValue(BOOLEAN, "a", VAR_DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newEmptyNodeInfo();// Empty
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(BOOLEAN, "", RETURN,0);// Return
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)1, BOOLEAN, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(BOOLEAN, "a", VAR_DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(BOOLEAN, "+", EXPR_OP,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(BOOLEAN, "a", VAR_DECL,0);
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
    node = *newNodeInfoWithoutValue(BOOLEAN, "+", EXPR_OP,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(BOOLEAN, "a", VAR_DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(BOOLEAN, "=", DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", DECL_BLOCK,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", PROGRAM,0);
    addNodeToTestingList(expectedNodes, node);

}

void checkTypesExpectedNodesCreator8(TestingNodeInfoList* expectedNodes) {

    NodeInfo node;

    node = *newNodeInfo((int *)0, BOOLEAN, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(BOOLEAN, "b", VAR_DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(BOOLEAN, "*", EXPR_OP,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(BOOLEAN, "b", VAR_DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(BOOLEAN, "=", ASSIGNMENT_OP, 0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)1, BOOLEAN, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(BOOLEAN, "b", VAR_DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(BOOLEAN, "*", EXPR_OP,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(BOOLEAN, "a", VAR_DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(BOOLEAN, "=", ASSIGNMENT_OP, 0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", STMT_BLOCK,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newEmptyNodeInfo();// LAMBDA
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)1, BOOLEAN, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)1, BOOLEAN, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(BOOLEAN, "*", EXPR_OP,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(BOOLEAN, "b", VAR_DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(BOOLEAN, "=", DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", DECL_BLOCK,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)0, BOOLEAN, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(BOOLEAN, "a", VAR_DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(BOOLEAN, "=", DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", DECL_BLOCK,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", PROGRAM,0);
    addNodeToTestingList(expectedNodes, node);

}

void checkTypesExpectedNodesCreator9(TestingNodeInfoList* expectedNodes) {

    NodeInfo node;

    node = *newNodeInfo((int *)40, INTEGER, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)2, INTEGER, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)2, INTEGER, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(INTEGER, "-", EXPR_OP,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(INTEGER, "+", EXPR_OP,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(INTEGER, "b", VAR_DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(INTEGER, "=", ASSIGNMENT_OP, 0);
    addNodeToTestingList(expectedNodes, node);
    node = *newEmptyNodeInfo();// LAMBDA
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfo((int *)0, INTEGER, "", CONST_VALUE,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(INTEGER, "b", VAR_DECL,0);
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
    node = *newNodeInfoWithoutValue(BOOLEAN, "+", EXPR_OP,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(BOOLEAN, "a", VAR_DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(BOOLEAN, "=", DECL,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", DECL_BLOCK,0);
    addNodeToTestingList(expectedNodes, node);
    node = *newNodeInfoWithoutValue(NONETYPE, "", PROGRAM,0);
    addNodeToTestingList(expectedNodes, node);

}

void checkTypesErrorListCreator1(ErrorNode** expectedErrors) {
    char* errorStr = "\033[1;31mLine: 1 Error:\033[0m Type mismatch\n";
    insertErrorNode(expectedErrors, errorStr);   
}
 
void checkTypesErrorListCreator2(ErrorNode** expectedErrors) {
    char* errorStr = "\033[1;31mLine: 1 Error:\033[0m Type mismatch\n";
    insertErrorNode(expectedErrors, errorStr);   
}

void checkTypesErrorListCreator3(ErrorNode** expectedErrors) {
    char* errorStr = "\033[1;31mLine: 2 Error:\033[0m Type mismatch\n";
    insertErrorNode(expectedErrors, errorStr);   
}

void checkTypesErrorListCreator4(ErrorNode** expectedErrors) {
    char* errorStr = "\033[1;31mLine: 1 Error:\033[0m Type mismatch\n";
    insertErrorNode(expectedErrors, errorStr);   
    errorStr = "\033[1;31mLine: 2 Error:\033[0m Type mismatch\n";
    insertErrorNode(expectedErrors, errorStr);   
}