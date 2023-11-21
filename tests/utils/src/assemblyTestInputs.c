
#include "../include/assemblyTestInputs.h"

void assembleExpectedOutputsFactory(char* inputTestFileName,  int expectedNodes[MAXOUTPUTS]){
    if(strstr(inputTestFileName, "invalid")!=NULL){
        return;
    }
    if (strcmp(inputTestFileName, "validInput1.bok") == 0) {
        assemblyExpectedOutputCreator1(expectedNodes);
    }else if (strcmp(inputTestFileName, "validInput2.bok") == 0) {
        assemblyExpectedOutputCreator2(expectedNodes);
    }else if (strcmp(inputTestFileName, "validInput3.bok") == 0) {
        assemblyExpectedOutputCreator3(expectedNodes);
    }else if (strcmp(inputTestFileName, "validInput4.bok") == 0) {
        assemblyExpectedOutputCreator4(expectedNodes);
    }else if (strcmp(inputTestFileName, "validInput5.bok") == 0) {
        assemblyExpectedOutputCreator5(expectedNodes);
    }/*else if (strcmp(inputTestFileName, "validInput6.txt") == 0) {
        assemblyExpectedOutputCreator6(expectedNodes);
    }else if (strcmp(inputTestFileName, "validInput7.txt") == 0) {
        assemblyExpectedOutputCreator7(expectedNodes);
    }else if (strcmp(inputTestFileName, "validInput8.txt") == 0) {
        assemblyExpectedOutputCreator8(expectedNodes);
    }else if (strcmp(inputTestFileName, "validInput9.txt") == 0) {
        assemblyExpectedOutputCreator9(expectedNodes);
    }*/
    return NULL ;
}

void assemblyExpectedOutputCreator1(int expectedNodes[MAXOUTPUTS]){
    expectedNodes[0] = 1;
    expectedNodes[1] = 2;
    expectedNodes[2] = 8;
    expectedNodes[3] = 89;
    expectedNodes[4] = 10946;
    expectedNodes[5] = -999999;
}

void assemblyExpectedOutputCreator2(int expectedNodes[MAXOUTPUTS]){
    expectedNodes[0] = 1;
    expectedNodes[1] = 2;
    expectedNodes[2] = 120;
    expectedNodes[3] = 3628800;
    expectedNodes[4] = -999999;
}

void assemblyExpectedOutputCreator3(int expectedNodes[MAXOUTPUTS]){
    expectedNodes[0] = 1;
    expectedNodes[1] = 1;
    expectedNodes[2] = 0;
    expectedNodes[3] = 1;
    expectedNodes[4] = -999999;
}

void assemblyExpectedOutputCreator4(int expectedNodes[MAXOUTPUTS]){
    expectedNodes[0] = 0;
    expectedNodes[1] = 1;
    expectedNodes[2] = 1;
    expectedNodes[3] = 1;
    expectedNodes[4] = 0;
    expectedNodes[5] = 2;
    expectedNodes[6] = 1;
    expectedNodes[7] = -999999;
}

void assemblyExpectedOutputCreator5(int expectedNodes[MAXOUTPUTS]){
    expectedNodes[0] = 0;
    expectedNodes[1] = 1;
    expectedNodes[2] = 2;
    expectedNodes[3] = 3;
    expectedNodes[4] = 4;
    expectedNodes[5] = 5;
    expectedNodes[6] = 6;
    expectedNodes[7] = 7;
    expectedNodes[8] = 8;
    expectedNodes[9] = 9;
    expectedNodes[10] = 1;
    expectedNodes[11] = -999999;
}

void assemblyExpectedOutputCreator6(int expectedNodes[MAXOUTPUTS]){
    expectedNodes[0] = 0;
    expectedNodes[1] = -999999;
}

void assemblyExpectedOutputCreator7(int expectedNodes[MAXOUTPUTS]){
    expectedNodes[0] = 1;
    expectedNodes[1] = -999999;
}

void assemblyExpectedOutputCreator8(int expectedNodes[MAXOUTPUTS]){
    expectedNodes[0] = 1;
    expectedNodes[1] = -999999;
}

void assemblyExpectedOutputCreator9(int expectedNodes[MAXOUTPUTS]){
    expectedNodes[0] = -999999;
}