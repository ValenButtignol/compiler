#ifndef ASSEMBLY_CODE_GENERATOR_H
#define ASSEMBLY_CODE_GENERATOR_H

#include <stdio.h>
#include <stdlib.h>
#include "threeAddressCodeList.h"
#include "nodeInfo.h"

void generateAssembly(ThreeAddressCodeList* list);
void generatePrologue(FILE* file, ThreeAddressCodeList* list);
void generateHeader(FILE* file, ThreeAddressCodeList* list);
void instructionFactory(FILE* file, ThreeAddressCodeNode* current);
void generateSum(FILE* file, char* firstValue, char* secondValue, char* thirdValue);
void generateSub(FILE* file, char* firstValue, char* secondValue, char* thirdValue);
void generateMul(FILE* file, char* firstValue, char* secondValue, char* thirdValue);
void generateDiv(FILE* file, char* firstValue, char* secondValue, char* thirdValue);
void generateAnd(FILE* file, char* firstValue, char* secondValue, char* thirdValue);
void generateOr(FILE* file, char* firstValue, char* secondValue, char* thirdValue);
void generateMov(FILE* file, char* firstValue, char* secondValue);
void generateRet(FILE* file, char* firstValue);
void generatePrint(FILE* file, char* valueToPrint);
char* generateValue(NodeInfo* value);

#endif