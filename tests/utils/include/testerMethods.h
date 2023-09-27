#ifndef UTILS_TESTER_DFS_H
#define UTILS_TESTER_DFS_H

#include "../../../include/ast.h"
#include "../../../include/nodeInfo.h"
#include "../../../include/errorNode.h"
#include "testingNodeInfoList.h"

int testerDfs(TAst* ast, TestingNodeInfoList* expectedValues);

int testErrors(ErrorNode* errors, ErrorNode* expectedErrors);

#endif