#ifndef UTILS_ASSEMBLYTEST_INPUTS_H
#define UTILS_ASSEMBLYTEST_INPUTS_H

#define MAXOUTPUTS 100

#include <string.h>
#include "../../../include/ast.h"
#include "../../../include/nodeInfo.h"
#include "../../../include/enums.h"
#include "../../../include/symbolTable.h"
#include "testingNodeInfoList.h"

void assembleExpectedOutputsFactory(char* inputTestFileName, int expectedNodes[MAXOUTPUTS]);

#endif