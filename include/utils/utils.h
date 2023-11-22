#ifndef	UTILS_H
#define UTILS_H
#include <stdio.h>
#include "../dataStructures/ast.h"
#include "../dataStructures/nodeInfo.h"
#include "../dataStructures/errorNode.h"

void setParamsToNodeInfo(NodeInfo** node, TAst* ast);

int checkReturnTypes(TAst *ast);

int checkSonsTypes(TAst *ast);

int checkSonsFatherTypes(TAst *ast);

void checkDivByZero(TAst *ast, ErrorNode** errors);

void copyMethodName(char **methodName,TAst *ast);

enum TType getAstType(TAst* ast);

int checkFatherLeftSonTypes(TAst *ast);

char* getParamRegister(char* paramRegister);

int hasBokExtension(const char* fileName);

char* generateAssemblyFilename(const char* fileName);

#endif