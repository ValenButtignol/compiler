#ifndef	THREE_ADDRES_CODE_LIST_H
#define THREE_ADDRES_CODE_LIST_H
#include <stdio.h>
#include "threeAddressCodeNode.h"
#include "nodeInfo.h"
#include "ast.h"

typedef struct ThreeAddressCodeList{
    ThreeAddressCodeNode* head;
    int size;
}ThreeAddressCodeList;

ThreeAddressCodeList *createEmptyTAC();

void createThreeAddressCodeList(TAst *ast, ThreeAddressCodeList *list, int* offset);

char* threeAddressListToString(ThreeAddressCodeList *list);

char *createTemportalID(int tempNumber);

void addToTAC(ThreeAddressCodeList* list,ThreeAddressCodeNode* node);

ThreeAddressCodeNode *getFromTAC(ThreeAddressCodeList *list, int index);

#endif