#ifndef UTILS_ASSEMBLYTEST_INPUTS_H
#define UTILS_ASSEMBLYTEST_INPUTS_H

#define MAXOUTPUTS 100

#include <string.h>
#include "../../../include/dataStructures/ast.h"
#include "../../../include/dataStructures/nodeInfo.h"
#include "../../../include/utils/enums.h"
#include "testingNodeInfoList.h"

void assembleExpectedOutputsFactory(char* inputTestFileName, int expectedNodes[MAXOUTPUTS]);

#endif