#include "../include/dataStructures/ast.h"
#include "../include/dataStructures/errorNode.h"
#include "utils/include/testerMethods.h"
#include "utils/include/suiteMessages.h"
#include "utils/include/generateAstInputs.h"
#include <assert.h>

static void generateAstTestSuite(char* inputTestFileName, TAst* globalAst, ErrorNode* errors) {

    TestingNodeInfoList* expectedNodes = newTestingNodeInfoList(); 
    TestingNodeInfoList* nodesToFreeLater = expectedNodes;
    ErrorNode* expectedErrors = NULL;
    generateAstFactory(inputTestFileName, expectedNodes, &expectedErrors);  //TODO: Implement
    
    if (expectedNodes->head == NULL && errors == NULL) {
        printNoTestSuiteMessage(inputTestFileName);
        return ;
    }
    
    if ((testerDfs(globalAst, expectedNodes))) {
        printTestSuccessMessage("Generate AST", inputTestFileName);
        freeTestingNodeInfoList(nodesToFreeLater);

    } else if (errors != NULL) {
        if (testErrors(errors, expectedErrors)) 
            printTestSuccessMessage("Generate AST", inputTestFileName);
        
        freeErrorsList(expectedErrors);
    } else {
        printTestFailedMessage("Generate AST", inputTestFileName);
    }

    freeTestingNodeInfoList(nodesToFreeLater);
}