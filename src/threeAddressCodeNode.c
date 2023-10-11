#include "../include/threeAddressCodeNode.h"

char *threeAddressCodeNodeToString(ThreeAddressCodeNode *node){
    if(node->first != NULL){
        char *str = malloc(50);
        strcat(str, labelToString(node->label));
        strcat(str, " ");
        strcat(str, node->first->id);
        strcat(str, " ");
        
        if(node->label != RET){
            // printf("ID: %s\n", node->second);
            if(strcmp(node->second->id, "") == 0){
                strcat(str, valueToString(node->second));
            }
            else strcat(str, node->second->id);
            strcat(str, " ");
            if(node->label != MOV){
                if(strcmp(node->third->id, "") == 0) strcat(str, valueToString(node->third));
                else strcat(str, node->third->id);
            }
        }
        return str;
    }
    return "";
}

char *labelToString(enum TLabel label){
    switch (label)
    {
    case SUM:
        return "SUM";
        break;
    case SUB:
        return "SUB";
        break;
    case MUL:
        return "MUL";
        break;
    case DIV:
        return "DIV";
        break;
    case MOV:
        return "MOV";
        break;
    case AND:
        return "AND";
        break;
    case OR:
        return "OR";
        break;
    case RET:
        return "RET";
        break;
    default:
        return "UNDEFINED OPERATION";
        break;
    }
}

char *valueToString(NodeInfo *node){
    char *str = malloc(10*sizeof(int));
    int *value = (int*)node->value;
    if(node->type == INTEGER){
        sprintf(str, "%d", *(int*)node->value);
    }else if(node->type == BOOLEAN){
        // int value = (int*)node->value;
        strcat(str, boolToString(*value));
    }
    return str;
}

ThreeAddressCodeNode *threeAddressCodeNodeFactory(
    enum TLabel label, NodeInfo *first, NodeInfo *second, NodeInfo *third){
        switch (label)
        {
        case SUM:
            return createThreeAddressCodeNode(label, first, second, third);
            break;
        case SUB:
            return createThreeAddressCodeNode(label, first, second, third);
            break;
        case MUL:
            return createThreeAddressCodeNode(label, first, second, third);
            break;
        case DIV:
            return createThreeAddressCodeNode(label, first, second, third);
            break;
        case AND:
            return createThreeAddressCodeNode(label, first, second, third);
            break;
        case OR:
            return createThreeAddressCodeNode(label, first, second, third);
            break;
        case MOV:
            return createThreeAddressCodeNode(label, first, second, newEmptyNodeInfo());
            break;
        case RET:
            return createThreeAddressCodeNode(label, first, newEmptyNodeInfo(), newEmptyNodeInfo());
            break;
        default:
            break;
        }
}

ThreeAddressCodeNode *createThreeAddressCodeNode(
    enum TLabel label, NodeInfo *first, NodeInfo *second, NodeInfo *third){

        ThreeAddressCodeNode *node = malloc(sizeof(ThreeAddressCodeNode));
        node->label = label;
        node->first = first;
        node->second = second;
        node->third = third;
        return node;
}

enum TLabel getLabelFromOperator(enum TOperator op, enum TType type){
    
    if(op == PLUS && type == INTEGER) return SUM;
    if(op == MINUS && type == INTEGER) return SUB;
    if(op == MULTIPLY && type == INTEGER) return MUL;
    if(op == DIVIDE && type == INTEGER) return DIV;
    if(op == PLUS && type == BOOLEAN) return OR;//falta determinar cuando es un and o un OR
    if(op == MULTIPLY && type == BOOLEAN) return AND;//podriamos pasar el tipo de la operacion asi es facil
    if(op == 0) return MOV;
}

NodeInfo *getFirst(ThreeAddressCodeNode *node){
    return node->first;
}

ThreeAddressCodeNode *newEmtyNodeTAC(){
        ThreeAddressCodeNode *node = malloc(sizeof(ThreeAddressCodeNode));
        node->label = 0;
        node->first = NULL;
        node->second = NULL;
        node->third = NULL;
        node->next = NULL;
        return node;
}