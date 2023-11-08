#include "../include/dataStructures/ast.h"
#include "../include/dataStructures/errorNode.h"
#include "utils/include/testerMethods.h"
#include "utils/include/suiteMessages.h"
#include "utils/include/checkTypesInputs.h"
#include <assert.h>

static void checkTypeTestSuite(char* inputTestFileName, TAst* globalAst, ErrorNode* errors) {
    ErrorNode* expectedErrors = NULL;

    int inputIsValid = checkTypesFactory(inputTestFileName, &expectedErrors);

    if (expectedErrors != NULL) {
        if (testErrors(errors, expectedErrors)) {
            printTestSuccessMessage("CheckTypes", inputTestFileName);
            freeErrorsList(expectedErrors);
            return;
        } else {
            printTestFailedMessage("CheckTypes", inputTestFileName);
            return ;
        }
    }

    if (inputIsValid) {
        printTestSuccessMessage("CheckTypes", inputTestFileName);
    } else {
        printNoTestSuiteMessage(inputTestFileName);
    }
    
    return ;
}