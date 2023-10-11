#ifndef UTILS_EVALAST_INPUTS_H
#define UTILS_EVALAST_INPUTS_H

#include <string.h>
#include "../../../include/ast.h"
#include "../../../include/nodeInfo.h"
#include "../../../include/enums.h"
#include "../../../include/symbolTable.h"
#include "testingNodeInfoList.h"

void evalAstExpectedNodesFactory(char* inputTestFileName, TestingNodeInfoList* expectedNodes);

#endif