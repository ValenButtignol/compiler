#ifndef UTILS_EVALAST_INPUTS_H
#define UTILS_EVALAST_INPUTS_H

#include <string.h>
#include "../../../include/ast.h"
#include "../../../include/nodeInfo.h"
#include "../../../include/enums.h"
#include "../../../include/symbolTable.h"
#include "testingNodeInfoList.h"

void evalAstExpectedNodesFactory(char* inputTestFileName, TestingNodeInfoList* expectedNodes);
void evalAstExpectedNodesCreator1(TestingNodeInfoList* expectedNodes);
//TAst* createCorrectAst3();
//TAst* createCorrectAst4();
//TAst* createCorrectAst5();
//TAst* createCorrectAst6();
//TAst* createCorrectAst7();
//TAst* createCorrectAst8();
//TAst* createCorrectAst9();

#endif