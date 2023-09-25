#include "../include/ast.h"
#include "utils/include/suiteMessages.h"
#include "utils/include/checkTypesInputs.h"
#include <assert.h>

static void checkTypeTestSuite(char* inputTestFileName, TAst* globalAst) {
    TestingNodeInfoList* expectedNodes = newTestingNodeInfoList(); 
    TestingNodeInfoList* nodesToFreeLater = expectedNodes;
    checkTypesExpectedNodesFactory(inputTestFileName, expectedNodes);

    if (expectedNodes->head == NULL) {
        printNoTestSuiteMessage(inputTestFileName);
        return ;
    }
    
    if ((testerDfs(globalAst, expectedNodes))) {
        printTestSuccessMessage("CheckTypes", inputTestFileName);
    } else {
        printTestFailedMessage("CheckTypes", inputTestFileName);
    }

    freeTestingNodeInfoList(nodesToFreeLater);
    return ;
}