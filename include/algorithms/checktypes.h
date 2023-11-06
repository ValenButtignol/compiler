#ifndef CHECKTYPES_H
#define CHECKTYPES_H
#include <stdio.h>
#include "../dataStructures/ast.h"
#include "../dataStructures/nodeInfo.h"
#include "../dataStructures/errorNode.h"
#include "../utils/enums.h"
#include "../utils/utils.h"

int checkTypes(TAst* ast, ErrorNode** errors);

void checkForTypeErrors(TAst* ast, ErrorNode** errors);

enum TType getAstType(TAst* ast);

#endif