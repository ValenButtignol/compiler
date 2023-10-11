#include <string.h>
#include <assert.h>
#include "utils/include/suiteMessages.h"
#include "utils/include/assemblyTestInputs.h"
#include "utils/include/testerMethods.h"
#include "utils/include/testingNodeInfoList.h"
#include "../include/ast.h"

static void assemblyTestSuite(char* inputTestFileName) {

    int expectedOutput[MAXOUTPUTS] = {-999999};
    
    assembleExpectedOutputsFactory(inputTestFileName, expectedOutput);
    
    if (expectedOutput == NULL) {
        printNoTestSuiteMessage(inputTestFileName);
        return ;
    }
    
    if ((testerOutputs("out.txt", expectedOutput))) {
        printTestSuccessMessage("Assembly", inputTestFileName);
    } else {
        printTestFailedMessage("Assembly", inputTestFileName);
    }

    return ;
}