#ifndef UTILS_GENAST_INPUTS_H
#define UTILS_GENAST_INPUTS_H

#include "../../../include/dataStructures/ast.h"
#include "../../../include/dataStructures/errorNode.h"
#include "../../../include/dataStructures/nodeInfo.h"
#include "../../../include/utils/enums.h"
#include "testingNodeInfoList.h"

void generateAstFactory(char* fileName, TestingNodeInfoList* expectedNodes, ErrorNode** expectedErrors);
void generateAstListErrors1(ErrorNode** expectedErrors);
void generateAstListErrors2(ErrorNode** expectedErrors);
void generateAstListErrors3(ErrorNode** expectedErrors);
void generateAstListErrors4(ErrorNode** expectedErrors);
void generateAstListErrors5(ErrorNode** expectedErrors);
void generateAstListErrors6(ErrorNode** expectedErrors);
void generateAstListErrors7(ErrorNode** expectedErrors);
void generateAstListErrors8(ErrorNode** expectedErrors);
void generateAstListErrors9(ErrorNode** expectedErrors);
void generateAstListErrors10(ErrorNode** expectedErrors);
void generateAstListErrors11(ErrorNode** expectedErrors);
void generateAstListErrors12(ErrorNode** expectedErrors);
void generateAstListErrors13(ErrorNode** expectedErrors);
void generateAstListErrors14(ErrorNode** expectedErrors);
void generateAstListErrors15(ErrorNode** expectedErrors);
void generateAstExpectedNodesCreator1(TestingNodeInfoList* expectedNodes);
void generateAstExpectedNodesCreator2(TestingNodeInfoList* expectedNodes);
void generateAstExpectedNodesCreator3(TestingNodeInfoList* expectedNodes);
void generateAstExpectedNodesCreator4(TestingNodeInfoList* expectedNodes);
void generateAstExpectedNodesCreator5(TestingNodeInfoList* expectedNodes);


#endif