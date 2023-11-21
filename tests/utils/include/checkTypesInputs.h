#ifndef UTILS_CHECKTYPES_INPUTS_H
#define UTILS_CHECKTYPES_INPUTS_H

#include <string.h>
#include "../../../include/dataStructures/ast.h"
#include "../../../include/utils/utils.h"
#include "../../../include/dataStructures/errorNode.h"
#include "../../../include/dataStructures/nodeInfo.h"
#include "../../../include/utils/enums.h"
#include "testingNodeInfoList.h"

int checkTypesFactory(char* inputTestFileName, ErrorNode** errors);
void checkTypesListErrors1(ErrorNode** expectedErrors);
void checkTypesListErrors2(ErrorNode** expectedErrors);
void checkTypesListErrors3(ErrorNode** expectedErrors);
void checkTypesListErrors4(ErrorNode** expectedErrors);
void checkTypesListErrors5(ErrorNode** expectedErrors);
void checkTypesListErrors6(ErrorNode** expectedErrors);
void checkTypesListErrors7(ErrorNode** expectedErrors);
void checkTypesListErrors8(ErrorNode** expectedErrors);
void checkTypesListErrors9(ErrorNode** expectedErrors);
void checkTypesListErrors10(ErrorNode** expectedErrors);
void checkTypesListErrors11(ErrorNode** expectedErrors);
void checkTypesListErrors12(ErrorNode** expectedErrors);

#endif