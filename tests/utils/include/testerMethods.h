#ifndef UTILS_TESTER_DFS_H
#define UTILS_TESTER_DFS_H

#include "../../../include/dataStructures/ast.h"
#include "../../../include/dataStructures/nodeInfo.h"
#include "../../../include/dataStructures/errorNode.h"
#include "testingNodeInfoList.h"

int testerDfs(TAst* ast, TestingNodeInfoList* expectedValues);

int testErrors(ErrorNode* errors, ErrorNode* expectedErrors);

int testerOutputs(char *filename, int expectedOutput[]);
#endif