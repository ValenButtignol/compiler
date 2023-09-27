#include <string.h>
#include <assert.h>
#include "utils/include/suiteMessages.h"
#include "utils/include/evalAstInputs.h"
#include "utils/include/testerMethods.h"
#include "utils/include/testingNodeInfoList.h"
#include "../include/ast.h"

static void evalAstTestSuite(char* inputTestFileName, TAst* globalAst) {

    TestingNodeInfoList* expectedNodes = newTestingNodeInfoList(); 
    TestingNodeInfoList* nodesToFreeLater = expectedNodes;
    evalAstExpectedNodesFactory(inputTestFileName, expectedNodes);

    if (expectedNodes->head == NULL) {
        printNoTestSuiteMessage(inputTestFileName);
        return ;
    }
    
    if ((testerDfs(globalAst, expectedNodes))) {
        printTestSuccessMessage("EvalAst", inputTestFileName);
    } else {
        printTestFailedMessage("EvalAst", inputTestFileName);
    }

    freeTestingNodeInfoList(nodesToFreeLater);
    return ;
}