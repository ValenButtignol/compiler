#include "../include/dataStructures/ast.h"
#include "../include/dataStructures/errorNode.h"
#include "utils/include/testerMethods.h"
#include "utils/include/suiteMessages.h"
#include "utils/include/checkTypesInputs.h"
#include <assert.h>

static void evalAstTestSuite(char* inputTestFileName, TAst* globalAst) {

    TestingNodeInfoList* expectedNodes = newTestingNodeInfoList(); 
    TestingNodeInfoList* nodesToFreeLater = expectedNodes;
    generateAstExpectedNodesFactory(inputTestFileName, expectedNodes);  //TODO: Implement
    
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