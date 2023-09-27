#include "../include/testerMethods.h"


int testerDfs(TAst* globalAst, TestingNodeInfoList* expectedNodes) {
 
    if (globalAst->ls == NULL && globalAst->rs == NULL) {
        return equalsNodeInfo(globalAst->data, expectedNodes->head->data);
    }

    if (!equalsNodeInfo(globalAst->data, expectedNodes->head->data)) {
        return 0;
    }

    int result;
    if (expectedNodes->head->next != NULL) {
        expectedNodes->head = expectedNodes->head->next;
        result = testerDfs(globalAst->ls, expectedNodes);
    } else {
        return 0;
    }

    if (expectedNodes->head->next != NULL) {
        expectedNodes->head = expectedNodes->head->next;
        result = result && testerDfs(globalAst->rs, expectedNodes);
    } else {
        return 0;
    }

    return result;
}


int testErrors(ErrorNode* errors, ErrorNode* expectedErrors) {
    ErrorNode* currentError = errors;
    ErrorNode* currentExpectedError = expectedErrors;
    while (currentError != NULL && currentExpectedError != NULL) {
        if (!equalsErrorNode(currentError, currentExpectedError)) {
            return 0;
        }
        currentError = currentError->next;
        currentExpectedError = currentExpectedError->next;
    }
    return currentError == NULL && currentExpectedError == NULL;
}
