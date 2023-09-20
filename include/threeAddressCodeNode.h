#ifndef	THREE_ADDRES_CODE_NODE_H
#define THREE_ADDRES_CODE_NODE_H
#include <stdio.h>
#include "nodeInfo.h"


enum TLabel{SUM, SUB, MUL, DIV, AND, OR, ASS, RET};

typedef struct ThreeAddressCodeNode{
    struct ThreeAddressCodeNode *next;
    enum TLabel label;
    NodeInfo *first;
    NodeInfo *second;
    NodeInfo *third;
} ThreeAddressCodeNode;

char *threeAddressCodeNodeToString(ThreeAddressCodeNode *node);
ThreeAddressCodeNode *threeAddressCodeNodeFactory(
    enum TLabel label, NodeInfo *first, NodeInfo *second, NodeInfo *third);
ThreeAddressCodeNode *createThreeAddressCodeNode(
    enum TLabel label, NodeInfo *first, NodeInfo *second, NodeInfo *third);
enum TLabel getLabelFromID(char *id, enum TType type);
NodeInfo *getFirst(ThreeAddressCodeNode *node);
ThreeAddressCodeNode *newEmtyNodeTAC();
char *valueToString(NodeInfo *node);
char *labelToString(enum TLabel label);
#endif