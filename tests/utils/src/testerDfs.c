#include "../include/testerDfs.h"


int testerDfs(TAst* globalAst, TestingNodeInfoList* expectedNodes) {
 
    /* printf("TREE value: %d\n", (int*)globalAst->data.value);
    printf("TREE id: %s\n", globalAst->data.id);
    printf("TREE type: %d\n", globalAst->data.type);
    printf("TREE tag: %d\n\n", globalAst->data.tag);

    printf("EXPECTED value: %d\n", expectedNodes->head->data.value);
    printf("EXPECTED id: %s\n", expectedNodes->head->data.id);
    printf("EXPECTED type: %d\n", expectedNodes->head->data.type);
    printf("EXPECTED tag: %d\n\n", expectedNodes->head->data.tag); */

    

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