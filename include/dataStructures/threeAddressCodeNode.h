#ifndef	THREE_ADDRES_CODE_NODE_H
#define THREE_ADDRES_CODE_NODE_H
#include <stdio.h>
#include "nodeInfo.h"
#include "../utils/enums.h"

typedef struct ThreeAddressCodeNode{
    struct ThreeAddressCodeNode *next;
    enum TTag label;
    NodeInfo *first;
    NodeInfo *second;
    NodeInfo *third;
} ThreeAddressCodeNode;

char *threeAddressCodeNodeToString(ThreeAddressCodeNode *node);

ThreeAddressCodeNode *threeAddressCodeNodeFactory(
    enum TTag label, NodeInfo *first, NodeInfo *second, NodeInfo *third
);

ThreeAddressCodeNode *createThreeAddressCodeNode(
    enum TTag label, NodeInfo *first, NodeInfo *second, NodeInfo *third
);

NodeInfo *getFirst(ThreeAddressCodeNode *node);

ThreeAddressCodeNode *newEmtyNodeTAC();

char *valueToString(NodeInfo *node);

char *labelToString(enum TTag label);

#endif