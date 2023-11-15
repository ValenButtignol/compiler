#ifndef ASSEMBLY_CODE_GENERATOR_H
#define ASSEMBLY_CODE_GENERATOR_H

#include <stdio.h>
#include <stdlib.h>
#include "../dataStructures/threeAddressCodeList.h"
#include "../dataStructures/nodeInfo.h"
#include "../utils/enums.h"

void generateAssembly(ThreeAddressCodeList* list);

void generatePrologue(FILE* file, ThreeAddressCodeList* list);

void generateHeader(FILE* file, ThreeAddressCodeList* list);

void instructionFactory(FILE* file, ThreeAddressCodeNode* current);

void generateAdd(FILE* file, char* firstValue, char* secondValue, char* thirdValue);

void generateSub(FILE* file, char* firstValue, char* secondValue, char* thirdValue);

void generateMul(FILE* file, char* firstValue, char* secondValue, char* thirdValue);

void generateDiv(FILE* file, char* firstValue, char* secondValue, char* thirdValue);

void generateAnd(FILE* file, char* firstValue, char* secondValue, char* thirdValue);

void generateOr(FILE* file, char* firstValue, char* secondValue, char* thirdValue);

void generateMov(FILE* file, char* firstValue, char* secondValue);

void generateRet(FILE* file, char* firstValue);

void generatePrint(FILE* file, char* valueToPrint);

char* generateValue(NodeInfo* value);

void generateLabel(FILE* file, char* firstValue);

void generateEquals(FILE* file, char* firstValue, char* secondValue, char* thirdValue);

void generateGreaterThan(FILE* file, char* firstValue, char* secondValue, char* thirdValue);

void generateLessThan(FILE* file, char* firstValue, char* secondValue, char* thirdValue);

void generateMod(FILE* file, char* firstValue, char* secondValue, char* thirdValue);

void generateJumpByFalse(FILE* file, char* firstValue, char* secondValue);

void generateJump(FILE* file, char* firstValue);

/*

void generateNegative(FILE* file, char* firstValue, char* secondValue);

void generateNot(FILE* file, char* firstValue, char* secondValue);
*/


#endif