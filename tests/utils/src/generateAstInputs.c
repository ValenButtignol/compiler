#include "../include/generateAstInputs.h"


void generateAstFactory(char* fileName, TestingNodeInfoList** expectedNodes, ErrorNode** expectedErrors) {
    
    if (strcmp(fileName, "invalidInput1.bok") == 0) {
        generateAstListErrors1(expectedErrors);
    } else if (strcmp(fileName, "invalidInput2.bok") == 0) {
        generateAstListErrors2(expectedErrors);
    } else if (strcmp(fileName, "invalidInput3.bok") == 0) {
        generateAstListErrors3(expectedErrors);
    } else if (strcmp(fileName, "invalidInput4.bok") == 0) {
        generateAstListErrors4(expectedErrors);
    } else if (strcmp(fileName, "invalidInput5.bok") == 0) {
        generateAstListErrors5(expectedErrors);
    } else if (strcmp(fileName, "invalidInput6.bok") == 0) {
        generateAstListErrors6(expectedErrors);
    } else if (strcmp(fileName, "invalidInput7.bok") == 0) {
        generateAstListErrors7(expectedErrors);
    } else if (strcmp(fileName, "invalidInput8.bok") == 0) {
        generateAstListErrors8(expectedErrors);
    } else if (strcmp(fileName, "invalidInput9.bok") == 0) {
        generateAstListErrors9(expectedErrors);
    } else if (strcmp(fileName, "invalidInput10.bok") == 0) {
        generateAstListErrors10(expectedErrors);
    } else if (strcmp(fileName, "invalidInput11.bok") == 0) {
        generateAstListErrors11(expectedErrors);
    } else if (strcmp(fileName, "invalidInput12.bok") == 0) {
        generateAstListErrors12(expectedErrors);
    } else if (strcmp(fileName, "invalidInput13.bok") == 0) {
        generateAstListErrors13(expectedErrors);
    } else if (strcmp(fileName, "invalidInput14.bok") == 0) {
        generateAstListErrors14(expectedErrors);
    } else if (strcmp(fileName, "invalidInput15.bok") == 0) {
        generateAstListErrors15(expectedErrors);
    } else if (strcmp(fileName, "validInput1.bok") == 0) {
        generateAstExpectedNodesCreator1(expectedNodes);
    } else if (strcmp(fileName, "validInput2.bok") == 0) {
        generateAstExpectedNodesCreator2(expectedNodes);
    } else if (strcmp(fileName, "validInput3.bok") == 0) {
        generateAstExpectedNodesCreator3(expectedNodes);
    } else if (strcmp(fileName, "validInput4.bok") == 0) {
        generateAstExpectedNodesCreator4(expectedNodes);
    } else if (strcmp(fileName, "validInput5.bok") == 0) {
        generateAstExpectedNodesCreator5(expectedNodes);
    }
}


void generateAstListErrors1(ErrorNode** expectedErrors) {
    char* errorStr = "\033[1;31mLine: 1 Error:\033[0m Type mismatch\n";
    insertErrorNode(expectedErrors, errorStr);   
} 

void generateAstListErrors2(ErrorNode** expectedErrors) {
    char* errorStr = "\033[1;31mLine: 1 Error:\033[0m Type mismatch\n";
    insertErrorNode(expectedErrors, errorStr);   
} 

void generateAstListErrors3(ErrorNode** expectedErrors) {
    char* errorStr = "\033[1;31mLine: 1 Error:\033[0m Type mismatch\n";
    insertErrorNode(expectedErrors, errorStr);   
}

void generateAstListErrors4(ErrorNode** expectedErrors) {
    char* errorStr = "\033[1;31mLine: 1 Error:\033[0m Type mismatch\n";
    insertErrorNode(expectedErrors, errorStr);   
} 

void generateAstListErrors5(ErrorNode** expectedErrors) {
    char* errorStr = "\033[1;31mLine: 1 Error:\033[0m Type mismatch\n";
    insertErrorNode(expectedErrors, errorStr);   
} 

void generateAstListErrors6(ErrorNode** expectedErrors) {
    char* errorStr = "\033[1;31mLine: 1 Error:\033[0m Type mismatch\n";
    insertErrorNode(expectedErrors, errorStr);   
} 

void generateAstListErrors7(ErrorNode** expectedErrors) {
    char* errorStr = "\033[1;31mLine: 1 Error:\033[0m Type mismatch\n";
    insertErrorNode(expectedErrors, errorStr);   
} 

void generateAstListErrors8(ErrorNode** expectedErrors) {
    char* errorStr = "\033[1;31mLine: 1 Error:\033[0m Type mismatch\n";
    insertErrorNode(expectedErrors, errorStr);   
} 

void generateAstListErrors9(ErrorNode** expectedErrors) {
    char* errorStr = "\033[1;31mLine: 1 Error:\033[0m Type mismatch\n";
    insertErrorNode(expectedErrors, errorStr);   
} 

void generateAstListErrors10(ErrorNode** expectedErrors) {
    char* errorStr = "\033[1;31mLine: 1 Error:\033[0m Type mismatch\n";
    insertErrorNode(expectedErrors, errorStr);   
} 

void generateAstListErrors11(ErrorNode** expectedErrors) {
    char* errorStr = "\033[1;31mLine: 1 Error:\033[0m Type mismatch\n";
    insertErrorNode(expectedErrors, errorStr);   
} 

void generateAstListErrors12(ErrorNode** expectedErrors) {
    char* errorStr = "\033[1;31mLine: 1 Error:\033[0m Type mismatch\n";
    insertErrorNode(expectedErrors, errorStr);   
}

void generateAstListErrors13(ErrorNode** expectedErrors) {
    char* errorStr = "\033[1;31mLine: 1 Error:\033[0m Type mismatch\n";
    insertErrorNode(expectedErrors, errorStr);   
}

void generateAstListErrors14(ErrorNode** expectedErrors) {
    char* errorStr = "\033[1;31mLine: 1 Error:\033[0m Type mismatch\n";
    insertErrorNode(expectedErrors, errorStr);   
}

void generateAstListErrors15(ErrorNode** expectedErrors) {
    char* errorStr = "\033[1;31mLine: 1 Error:\033[0m Type mismatch\n";
    insertErrorNode(expectedErrors, errorStr);   
}

void generateAstExpectedNodesCreator1(TestingNodeInfoList** expectedNodes) {
    NodeInfo* node;
    node = newNodeInfoWithoutValue(INTEGER, "a", VAR_DECL,0);
    addNodeToTestingList(expectedNodes, node);
}

void generateAstExpectedNodesCreator2(TestingNodeInfoList** expectedNodes) {
    NodeInfo node;

}

void generateAstExpectedNodesCreator3(TestingNodeInfoList** expectedNodes) {
    NodeInfo node;

}

void generateAstExpectedNodesCreator4(TestingNodeInfoList** expectedNodes) {
    NodeInfo node;

}

void generateAstExpectedNodesCreator5(TestingNodeInfoList** expectedNodes) {
    NodeInfo node;

}