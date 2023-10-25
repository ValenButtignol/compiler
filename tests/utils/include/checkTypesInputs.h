#ifndef UTILS_CHECKTYPES_INPUTS_H
#define UTILS_CHECKTYPES_INPUTS_H

#include <string.h>
#include "../../../include/dataStructures/ast.h"
#include "../../../include/dataStructures/errorNode.h"
#include "../../../include/dataStructures/nodeInfo.h"
#include "../../../include/utils/enums.h"
#include "testingNodeInfoList.h"

void checkTypesFactory(char* inputTestFileName, TestingNodeInfoList* expectedNodes, ErrorNode** errors);
//void checkTypesExpectedNodesCreator1(TestingNodeInfoList* expectedNodes);
//void checkTypesExpectedNodesCreator2(TestingNodeInfoList* expectedNodes);
//void checkTypesErrorListCreator1(ErrorNode** errors);

#endif