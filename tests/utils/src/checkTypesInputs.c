#include "../include/checkTypesInputs.h"

void checkTypesFactory(char* inputTestFileName, TestingNodeInfoList** expectedNodes, ErrorNode** expectedErrors) {
    
    if (strcmp(inputTestFileName, "invalidInput1.bok") == 0) {
        checkTypesListErrors1(expectedErrors);
    } else if (strcmp(inputTestFileName, "invalidInput2.bok") == 0) {
        checkTypesListErrors2(expectedErrors);
    } else if (strcmp(inputTestFileName, "invalidInput3.bok") == 0) {
        checkTypesListErrors3(expectedErrors);
    } else if (strcmp(inputTestFileName, "invalidInput4.bok") == 0) {
        checkTypesListErrors4(expectedErrors);
    } else if (strcmp(inputTestFileName, "invalidInput5.bok") == 0) {
        checkTypesListErrors5(expectedErrors);
    } else if (strcmp(inputTestFileName, "invalidInput6.bok") == 0) {
        checkTypesListErrors6(expectedErrors);
    } else if (strcmp(inputTestFileName, "invalidInput7.bok") == 0) {
        checkTypesListErrors7(expectedErrors);
    } else if (strcmp(inputTestFileName, "invalidInput8.bok") == 0) {
        checkTypesListErrors8(expectedErrors);
    } else if (strcmp(inputTestFileName, "invalidInput9.bok") == 0) {
        checkTypesListErrors9(expectedErrors);
    } else if (strcmp(inputTestFileName, "invalidInput10.bok") == 0) {
        checkTypesListErrors10(expectedErrors);
    } else if (strcmp(inputTestFileName, "invalidInput11.bok") == 0) {
        checkTypesListErrors11(expectedErrors);
    } else if (strcmp(inputTestFileName, "invalidInput12.bok") == 0) {
        checkTypesListErrors12(expectedErrors);
    } else if (strcmp(inputTestFileName, "validInput1.bok") == 0) {
        checkTypesExpectedNodesCreator1(expectedNodes);
    } else if (strcmp(inputTestFileName, "validInput2.bok") == 0) {
        checkTypesExpectedNodesCreator2(expectedNodes);
    } else if (strcmp(inputTestFileName, "validInput3.bok") == 0) {
        checkTypesExpectedNodesCreator3(expectedNodes);
    }
}

void checkTypesListErrors1(ErrorNode** expectedErrors) {
    addOperationError(expectedErrors, 5, ASSIGNMENT);
    addOperationError(expectedErrors, 3, ASSIGNMENT);
} 

void checkTypesListErrors2(ErrorNode** expectedErrors) {
    addOperationError(expectedErrors, 17, ASSIGNMENT);
    addOperationError(expectedErrors, 16, ASSIGNMENT);
    addOperationError(expectedErrors, 16, AND);
    addOperationError(expectedErrors, 15, ASSIGNMENT);
    addOperationError(expectedErrors, 15, AND);
    addOperationError(expectedErrors, 14, ASSIGNMENT);
    addOperationError(expectedErrors, 14, AND);
    addOperationError(expectedErrors, 10, ASSIGNMENT);
    addOperationError(expectedErrors, 9, ASSIGNMENT);
    addOperationError(expectedErrors, 9, AND);
    addOperationError(expectedErrors, 8, ASSIGNMENT);
    addOperationError(expectedErrors, 8, AND);
    addOperationError(expectedErrors, 7, ASSIGNMENT);
    addOperationError(expectedErrors, 7, AND);
    addOperationError(expectedErrors, 5, ADD);
    addOperationError(expectedErrors, 4, ADD);
    addOperationError(expectedErrors, 3, ADD);

} 

void checkTypesListErrors3(ErrorNode** expectedErrors) {
    addOperationError(expectedErrors, 15, AND);
    addOperationError(expectedErrors, 14, AND);
    addOperationError(expectedErrors, 13, AND);
    addOperationError(expectedErrors, 10, AND);
    addOperationError(expectedErrors, 9, AND);
    addOperationError(expectedErrors, 8, AND);
    addOperationError(expectedErrors, 6, ASSIGNMENT);
    addOperationError(expectedErrors, 6, ADD);
    addOperationError(expectedErrors, 5, ASSIGNMENT);
    addOperationError(expectedErrors, 5, ADD);
    addOperationError(expectedErrors, 4, ASSIGNMENT);
    addOperationError(expectedErrors, 4, ADD);
    addOperationError(expectedErrors, 3, ASSIGNMENT);

}

void checkTypesListErrors4(ErrorNode** expectedErrors) {
    addOperationError(expectedErrors, 10, ADD);
    addOperationError(expectedErrors, 10, ADD);
    addOperationError(expectedErrors, 9, ADD);
    addOperationError(expectedErrors, 8, ADD);
    addOperationError(expectedErrors, 8, ADD);
    addOperationError(expectedErrors, 7, ADD);
    addOperationError(expectedErrors, 7, ADD);
    addOperationError(expectedErrors, 6, ADD);
    addOperationError(expectedErrors, 5, ADD);
    addOperationError(expectedErrors, 4, ADD);
} 

void checkTypesListErrors5(ErrorNode** expectedErrors) {
    addOperationError(expectedErrors, 9, AND);
    addOperationError(expectedErrors, 8, AND);
    addOperationError(expectedErrors, 7, AND);
    addOperationError(expectedErrors, 6, AND);
    addOperationError(expectedErrors, 6, AND);
    addOperationError(expectedErrors, 5, AND);
    addOperationError(expectedErrors, 5, AND);
    addOperationError(expectedErrors, 4, AND);
    addOperationError(expectedErrors, 3, AND);
    addOperationError(expectedErrors, 3, AND);
} 

void checkTypesListErrors6(ErrorNode** expectedErrors) {
    addOperationError(expectedErrors, 18, ADD);
    addOperationError(expectedErrors, 18, ADD);
    addOperationError(expectedErrors, 18, ADD);
    addOperationError(expectedErrors, 17, ADD);
    addOperationError(expectedErrors, 17, ADD);
    addOperationError(expectedErrors, 16, ADD);
    addOperationError(expectedErrors, 16, ADD);
    addOperationError(expectedErrors, 15, ADD);
    addOperationError(expectedErrors, 15, ADD);
    addOperationError(expectedErrors, 15, ADD);
    addOperationError(expectedErrors, 14, ADD);
    addOperationError(expectedErrors, 14, ADD);
    addOperationError(expectedErrors, 14, ADD);
    addOperationError(expectedErrors, 13, ADD);
    addOperationError(expectedErrors, 12, ADD);
    addOperationError(expectedErrors, 12, ADD);
    addOperationError(expectedErrors, 11, ADD);
    addOperationError(expectedErrors, 11, ADD);
    addOperationError(expectedErrors, 10, ADD);
    addOperationError(expectedErrors, 10, ADD);
    addOperationError(expectedErrors, 9, ADD);
    addOperationError(expectedErrors, 9, ADD);
    addOperationError(expectedErrors, 8, ADD);
    addOperationError(expectedErrors, 8, ADD);
    addOperationError(expectedErrors, 7, ADD);
    addOperationError(expectedErrors, 6, ADD);
    addOperationError(expectedErrors, 5, ADD);
    addOperationError(expectedErrors, 4, ADD);

} 

void checkTypesListErrors7(ErrorNode** expectedErrors) {
    addOperationError(expectedErrors, 17, AND);
    addOperationError(expectedErrors, 16, AND);
    addOperationError(expectedErrors, 15, AND);
    addOperationError(expectedErrors, 14, AND);
    addOperationError(expectedErrors, 13, AND);
    addOperationError(expectedErrors, 13, AND);
    addOperationError(expectedErrors, 12, AND);
    addOperationError(expectedErrors, 12, AND);
    addOperationError(expectedErrors, 11, AND);
    addOperationError(expectedErrors, 11, AND);
    addOperationError(expectedErrors, 10, AND);
    addOperationError(expectedErrors, 10, AND);
    addOperationError(expectedErrors, 9, AND);
    addOperationError(expectedErrors, 9, AND);
    addOperationError(expectedErrors, 8, AND);
    addOperationError(expectedErrors, 7, AND);
    addOperationError(expectedErrors, 7, AND);
    addOperationError(expectedErrors, 7, AND);
    addOperationError(expectedErrors, 6, AND);
    addOperationError(expectedErrors, 6, AND);
    addOperationError(expectedErrors, 6, AND);
    addOperationError(expectedErrors, 5, AND);
    addOperationError(expectedErrors, 5, AND);
    addOperationError(expectedErrors, 4, AND);
    addOperationError(expectedErrors, 4, AND);
    addOperationError(expectedErrors, 3, AND);
    addOperationError(expectedErrors, 3, AND);
    addOperationError(expectedErrors, 3, AND);  
} 

void checkTypesListErrors8(ErrorNode** expectedErrors) {

    addMethodCallError(expectedErrors, 3, "Type mismatch", "foo");
    addMethodCallError(expectedErrors, 3, "Type mismatch", "foo");
    addOperationError(expectedErrors, 11, NEGATIVE);
    addOperationError(expectedErrors, 10, NOT);
} 

void checkTypesListErrors9(ErrorNode** expectedErrors) {
    addOperationError(expectedErrors, 11, GREATER_THAN);
    addOperationError(expectedErrors, 14, RETURN);
} 

void checkTypesListErrors10(ErrorNode** expectedErrors) {
    addOperationError(expectedErrors, 12, ASSIGNMENT);
    addMethodCallError(expectedErrors, 12, "Type mismatch", "g");
    addMethodCallError(expectedErrors, 12, "Type mismatch", "g");
} 

void checkTypesListErrors11(ErrorNode** expectedErrors) {
    addMethodCallError(expectedErrors, 11, "Type mismatch", "g");
} 

void checkTypesListErrors12(ErrorNode** expectedErrors) {
    addMethodCallError(expectedErrors, 11, "Type mismatch", "foo");
}

void checkTypesListErrors13(ErrorNode** expectedErrors) {
    char* errorStr = "\033[1;31mLine: 1 Error:\033[0m Type mismatch\n";
    insertErrorNode(expectedErrors, errorStr);   
}

void checkTypesListErrors14(ErrorNode** expectedErrors) {
    char* errorStr = "\033[1;31mLine: 1 Error:\033[0m Type mismatch\n";
    insertErrorNode(expectedErrors, errorStr);   
}

void checkTypesListErrors15(ErrorNode** expectedErrors) {
    char* errorStr = "\033[1;31mLine: 1 Error:\033[0m Type mismatch\n";
    insertErrorNode(expectedErrors, errorStr);   
}

void checkTypesExpectedNodesCreator1(TestingNodeInfoList** expectedNodes) {
    NodeInfo* node;
    node = newNodeInfoWithoutValue(INTEGER, "a", VAR_DECL,0);
    addNodeToTestingList(expectedNodes, node);
}

void checkTypesExpectedNodesCreator2(TestingNodeInfoList** expectedNodes) {
    NodeInfo node;

}

void checkTypesExpectedNodesCreator3(TestingNodeInfoList** expectedNodes) {
    NodeInfo node;

}