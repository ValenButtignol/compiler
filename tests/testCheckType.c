#include "../include/ast.h"
#include "../include/errorNode.h"
#include "utils/include/testerMethods.h"
#include "utils/include/suiteMessages.h"
#include "utils/include/checkTypesInputs.h"
#include <assert.h>

static void checkTypeTestSuite(char* inputTestFileName, TAst* globalAst, ErrorNode** errors) {
    TestingNodeInfoList* expectedNodes = newTestingNodeInfoList(); 
    TestingNodeInfoList* nodesToFreeLater = expectedNodes;
    ErrorNode* expectedErrors = NULL;
    checkTypesFactory(inputTestFileName, expectedNodes, &expectedErrors);
    if (expectedNodes->head == NULL && *errors == NULL) {
        printNoTestSuiteMessage(inputTestFileName);
        return ;
    }

    
    if (expectedNodes->head != NULL) {
        if (testerDfs(globalAst, expectedNodes)){
            printTestSuccessMessage("CheckTypes", inputTestFileName);
            freeTestingNodeInfoList(nodesToFreeLater);
        }else {
            printTestFailedMessage("CheckTypes", inputTestFileName);
        }
    } else if (*errors != NULL) {
        if (testErrors(*errors, expectedErrors)) 
            printTestSuccessMessage("CheckTypes", inputTestFileName);
            freeErrorsList(expectedErrors);
    } else {
        printTestFailedMessage("CheckTypes", inputTestFileName);
    }
    
    return ;
}