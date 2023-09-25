#ifndef UTILS_CHECKTYPES_INPUTS_H
#define UTILS_CHECKTYPES_INPUTS_H

#include <string.h>
#include "../../../include/ast.h"
#include "../../../include/nodeInfo.h"
#include "../../../include/enums.h"
#include "../../../include/symbolTable.h"
#include "testingNodeInfoList.h"

void checkTypesExpectedNodesFactory(char* inputTestFileName, TestingNodeInfoList* expectedNodes);
void checkTypesExpectedNodesCreator1(TestingNodeInfoList* expectedNodes);
//TAst* createCorrectAst3();
//TAst* createCorrectAst4();
//TAst* createCorrectAst5();
//TAst* createCorrectAst6();
//TAst* createCorrectAst7();
//TAst* createCorrectAst8();
//TAst* createCorrectAst9();

#endif