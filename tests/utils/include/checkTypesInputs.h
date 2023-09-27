#ifndef UTILS_CHECKTYPES_INPUTS_H
#define UTILS_CHECKTYPES_INPUTS_H

#include <string.h>
#include "../../../include/ast.h"
#include "../../../include/errorNode.h"
#include "../../../include/nodeInfo.h"
#include "../../../include/enums.h"
#include "../../../include/symbolTable.h"
#include "testingNodeInfoList.h"

void checkTypesFactory(char* inputTestFileName, TestingNodeInfoList* expectedNodes, ErrorNode** errors);
void checkTypesExpectedNodesCreator1(TestingNodeInfoList* expectedNodes);
void checkTypesExpectedNodesCreator2(TestingNodeInfoList* expectedNodes);
void checkTypesExpectedNodesCreator3(TestingNodeInfoList* expectedNodes);
void checkTypesExpectedNodesCreator4(TestingNodeInfoList* expectedNodes);
void checkTypesExpectedNodesCreator5(TestingNodeInfoList* expectedNodes);
void checkTypesExpectedNodesCreator6(TestingNodeInfoList* expectedNodes);
void checkTypesExpectedNodesCreator7(TestingNodeInfoList* expectedNodes);
void checkTypesExpectedNodesCreator8(TestingNodeInfoList* expectedNodes);
void checkTypesExpectedNodesCreator9(TestingNodeInfoList* expectedNodes);
void checkTypesErrorListCreator1(ErrorNode** errors);
void checkTypesErrorListCreator2(ErrorNode** errors);
void checkTypesErrorListCreator3(ErrorNode** errors);
void checkTypesErrorListCreator4(ErrorNode** errors);


#endif