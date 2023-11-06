#include "../include/checkTypesInputs.h"

void checkTypesFactory(char* inputTestFileName, TestingNodeInfoList* expectedNodes, ErrorNode** expectedErrors) {
    
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
    } else if (strcmp(inputTestFileName, "validInput1.bok") == 0) {
        checkTypesExpectedNodesCreator1(expectedNodes);
    } else if (strcmp(inputTestFileName, "validInput2.bok") == 0) {
        checkTypesExpectedNodesCreator2(expectedNodes);
    } else if (strcmp(inputTestFileName, "validInput3.bok") == 0) {
        checkTypesExpectedNodesCreator3(expectedNodes);
    }
}

void checkTypesListErrors1(ErrorNode** expectedErrors) {
    char* errorStr = "\033[1;31mLine: 1 Error:\033[0m Type mismatch\n";
    insertErrorNode(expectedErrors, errorStr);   
} 

void checkTypesListErrors2(ErrorNode** expectedErrors) {
    char* errorStr = "\033[1;31mLine: 1 Error:\033[0m Type mismatch\n";
    insertErrorNode(expectedErrors, errorStr);   
} 

void checkTypesListErrors3(ErrorNode** expectedErrors) {
    char* errorStr = "\033[1;31mLine: 1 Error:\033[0m Type mismatch\n";
    insertErrorNode(expectedErrors, errorStr);   
}

void checkTypesListErrors4(ErrorNode** expectedErrors) {
    char* errorStr = "\033[1;31mLine: 1 Error:\033[0m Type mismatch\n";
    insertErrorNode(expectedErrors, errorStr);   
} 

void checkTypesListErrors5(ErrorNode** expectedErrors) {
    char* errorStr = "\033[1;31mLine: 1 Error:\033[0m Type mismatch\n";
    insertErrorNode(expectedErrors, errorStr);   
} 

void checkTypesListErrors6(ErrorNode** expectedErrors) {
    char* errorStr = "\033[1;31mLine: 1 Error:\033[0m Type mismatch\n";
    insertErrorNode(expectedErrors, errorStr);   
} 

void checkTypesListErrors7(ErrorNode** expectedErrors) {
    char* errorStr = "\033[1;31mLine: 1 Error:\033[0m Type mismatch\n";
    insertErrorNode(expectedErrors, errorStr);   
} 

void checkTypesListErrors8(ErrorNode** expectedErrors) {
    char* errorStr = "\033[1;31mLine: 1 Error:\033[0m Type mismatch\n";
    insertErrorNode(expectedErrors, errorStr);   
} 

void checkTypesListErrors9(ErrorNode** expectedErrors) {
    char* errorStr = "\033[1;31mLine: 1 Error:\033[0m Type mismatch\n";
    insertErrorNode(expectedErrors, errorStr);   
} 

void checkTypesListErrors10(ErrorNode** expectedErrors) {
    char* errorStr = "\033[1;31mLine: 1 Error:\033[0m Type mismatch\n";
    insertErrorNode(expectedErrors, errorStr);   
} 

void checkTypesListErrors11(ErrorNode** expectedErrors) {
    char* errorStr = "\033[1;31mLine: 1 Error:\033[0m Type mismatch\n";
    insertErrorNode(expectedErrors, errorStr);   
} 

void checkTypesListErrors12(ErrorNode** expectedErrors) {
    char* errorStr = "\033[1;31mLine: 1 Error:\033[0m Type mismatch\n";
    insertErrorNode(expectedErrors, errorStr);   
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

void checkTypesExpectedNodesCreator1(TestingNodeInfoList* expectedNodes) {
    NodeInfo* node;
    node = newNodeInfoWithoutValue(INTEGER, "a", VAR_DECL,0);
    addNodeToTestingList(expectedNodes, node);
}

void checkTypesExpectedNodesCreator2(TestingNodeInfoList* expectedNodes) {
    NodeInfo node;

}

void checkTypesExpectedNodesCreator3(TestingNodeInfoList* expectedNodes) {
    NodeInfo node;

}

void checkTypesExpectedNodesCreator4(TestingNodeInfoList* expectedNodes) {
    NodeInfo node;

}

void checkTypesExpectedNodesCreator5(TestingNodeInfoList* expectedNodes) {
    NodeInfo node;

}