#include "../include/testerDfs.h"


int testerDfs(TAst* globalAst, TestingNodeInfoList* expectedNodes) {

    printf("Ast value: %d\n", globalAst->data.value);
    printf("Ast id: %s\n", globalAst->data.id);
    printf("Ast type: %d\n", globalAst->data.type);
    printf("Ast tag: %d\n\n", globalAst->data.tag);
    
    /* printf("List value: %d\n", expectedNodes->head->data.value);
    printf("List id: %s\n", expectedNodes->head->data.id);
    printf("List type: %d\n", expectedNodes->head->data.type);
    printf("List tag: %d\n\n\n", expectedNodes->head->data.tag); */
    if (globalAst->ls == NULL && globalAst->rs == NULL) {
        return 1;
        //return equalsNodeInfo(globalAst->data, expectedNodes->head->data);
    }

/*     if (!equalsNodeInfo(globalAst->data, expectedNodes->head->data)) {
        return 0;
    } */

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