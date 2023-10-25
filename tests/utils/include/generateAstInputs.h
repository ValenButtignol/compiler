#ifndef UTILS_GENAST_INPUTS_H
#define UTILS_GENAST_INPUTS_H

#include "../../../include/dataStructures/ast.h"
#include "../../../include/dataStructures/errorNode.h"
#include "../../../include/dataStructures/nodeInfo.h"
#include "../../../include/utils/enums.h"
#include "testingNodeInfoList.h"

void generateAstFactory(char* fileName, TestingNodeInfoList* expectedNodes, ErrorNode* expectedErrors);

#endif