#ifndef UTILS_EVALAST_INPUTS_H
#define UTILS_EVALAST_INPUTS_H

#include <string.h>
#include "../../../include/dataStructures/ast.h"
#include "../../../include/dataStructures/nodeInfo.h"
#include "../../../include/dataStructures/symbolTable.h"
#include "../../../include/utils/enums.h"
#include "testingNodeInfoList.h"

void evalAstExpectedNodesFactory(char* inputTestFileName, TestingNodeInfoList* expectedNodes);

#endif