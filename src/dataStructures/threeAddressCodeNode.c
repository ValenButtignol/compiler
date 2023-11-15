#include "../../include/dataStructures/threeAddressCodeNode.h"

char *threeAddressCodeNodeToString(ThreeAddressCodeNode *node){     
    char *str = malloc(50);
    strcat(str, labelToString(node->label));
    strcat(str, " ");
    if(node->label == LOAD){
            if(node->first->id != NULL) strcat(str, node->first->id);
            if(node->first->value != NULL) strcat(str, valueToString(node->first)); 
            strcat(str, " ");
            sprintf(str + strlen(str), "%d", node->second->lineNumber);
            strcat(str, " ");
    }else if(node->label == METHOD_CALL){
            
            strcat(str, node->first->id);
            strcat(str, " ");
    }
    else if(node->first != NULL){
        if(node->first->tag != PARAM){
            strcat(str, node->first->id);
        }
        strcat(str, " ");
        if(node->label != RETURN && node->label != LOAD){
            if(node->second->value != NULL){
                strcat(str, valueToString(node->second));
            }
            else strcat(str, node->second->id);
            strcat(str, " ");
            if(node->label != ASSIGNMENT){
                if(node->third->value != NULL) strcat(str, valueToString(node->third));
                else strcat(str, node->third->id);
            }
        }
    }
    return str;
}

char *labelToString(enum TTag label){
    switch (label)
    {
    case ADD:
        return "SUM";
    case SUB:
        return "SUB";
    case MUL:
        return "MUL";
    case DIV:
        return "DIV";
    case ASSIGNMENT:
        return "MOV";
    case AND:
        return "AND";
    case OR:
        return "OR";
    case RETURN:
        return "RET";
    case JFALSE:
        return "JUMP_BY_FALSE";
    case JTRUE:
        return "JUMP_BY_TRUE";
    case LABEL:
        return "LABEL";
    case EQUALS:
        return "EQUALS";
    case GREATER_THAN:
        return "GREATER_THAN";
    case LESS_THAN:
        return "LESS_THAN";
    case LOAD:
        return "LOAD";
        break;
    case METHOD_CALL:
        return "CALL";
        break;
    default:
        return "UNDEFINED OPERATION";
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
    enum TTag label, NodeInfo *first, NodeInfo *second, NodeInfo *third){
        switch (label)
        {
        case ASSIGNMENT:
            return createThreeAddressCodeNode(label, first, second, newEmptyNodeInfo());
            break;
        case RETURN:
            return createThreeAddressCodeNode(label, first, newEmptyNodeInfo(), newEmptyNodeInfo());
            break;
        default:
            return createThreeAddressCodeNode(label, first, second, third);
            break;
        }
}

ThreeAddressCodeNode *createThreeAddressCodeNode(
    enum TTag label, NodeInfo *first, NodeInfo *second, NodeInfo *third){

        ThreeAddressCodeNode *node = malloc(sizeof(ThreeAddressCodeNode));
        node->label = label;
        node->first = first;
        node->second = second;
        node->third = third;
        return node;
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