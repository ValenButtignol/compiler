#ifndef	THREE_ADDRES_CODE_LIST_H
#define THREE_ADDRES_CODE_LIST_H
#include <stdio.h>
#include "threeAddressCodeNode.h"
#include "nodeInfo.h"
#include "ast.h"
#include "nodeInfoStack.h"

typedef struct ThreeAddressCodeList{
    ThreeAddressCodeNode* head;
    int size;
}ThreeAddressCodeList;

ThreeAddressCodeList *createEmptyTAC();

ThreeAddressCodeNode *getFromTAC(ThreeAddressCodeList *list, int index);

void createThreeAddressCodeList(TAst *ast, ThreeAddressCodeList *list, int* offset, int* labelCounter, NodeInfoStack *parameterStack);

char* threeAddressListToString(ThreeAddressCodeList *list);

void addToTAC(ThreeAddressCodeList* list,ThreeAddressCodeNode* node);

#endif