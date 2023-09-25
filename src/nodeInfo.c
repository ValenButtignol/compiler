#include "../include/nodeInfo.h"

NodeInfo *newNodeInfo(void* value, enum TType type, char* id, enum TTag tag) {
    NodeInfo *result = malloc(sizeof(NodeInfo*));  

    setValue(result, value, type);
    result->type = type;
    result->id = strdup(id);     // Remember to free this later.
    result->tag = tag;

    return result;
}

NodeInfo* newNodeInfoWithoutValue(enum TType type, char* id, enum TTag tag) {
    NodeInfo *result = malloc(sizeof(NodeInfo*));    

    result->value = malloc(sizeof(int*));
    result->value = NULL;
    result->type = type;
    result->id = strdup(id); 
    result->tag = tag;

    return result;
}

NodeInfo *newEmptyNodeInfo() {
    NodeInfo *result = malloc(sizeof(NodeInfo*));    

    result->value = malloc(sizeof(int*));
    result->value = NULL;
    result->type = NONETYPE;
    result->id = ""; 
    result->tag = NONETAG;

    return result;
}

void* setValue(NodeInfo* node, void* value, enum TType type) {
    node->value = malloc(sizeof(value));
    node->value = value;
}

char* nodeInfoToString(NodeInfo node) {
    char* string;
    string = malloc(sizeof(char*));
    switch (node.tag) 
    {
    case 0: // PROGRAM 
        strcpy(string, "");
        break;

    case 1: // DECL_BLOCK 
        strcpy(string, "");
        break;
    
    case 2: // DECL
        strcpy(string, "");
        break;
    
    case 3: // VAR_DECL
        char* t = malloc(sizeof(char*)); 
        t = typeToString(node.type);
        size_t totalLength = strlen(t) + strlen(node.id) + 5; // +5 for formatting characters
        string = malloc(totalLength*sizeof(char));
        snprintf(string, totalLength, "%s %s", t, node.id);
        break;
    
    case 4: // CONST_DECL
        strcpy(string, "const");    
        break;

    case 5: // STMT_BLOCK
        strcpy(string, "");
        break;
    
    case 6: // ASSIGNMENT_OP
        strcpy(string, "=");
        break;
    
    case 7: // RETURN
        strcpy(string, "return");
        break;
    
    case 8: // EXPR_OP
        strcpy(string, operatorToString(*(enum TOperator*)node.value));
        break;
    
    case 9: // CONST_VALUE
        strcpy(string, constExprToString(node));
        break;
    
    case 10: // NONETAG
        strcpy(string, "");
        break;
    
    default:
        return "DEFAULT";
    }
    return string;
}

char* constExprToString(NodeInfo node) {
    switch (node.type)
    {
    case 0:
        char* s = malloc(sizeof(char*));
        sprintf(s, "%d",(int*)node.value);
        return s;
        break;

    case 1:
        return boolToString(*(enum TBoolean*)node.value);
        break;

    default:
        break;
    }
}

void freeNodeInfo(NodeInfo* node) {
    free(node->value);  
    free(node->id);
}

int isEmptyNode(NodeInfo node) {
    return node.value == NULL && node.type == NONETYPE && node.id == "" && node.tag == NONETAG;
}

int equalsNodeInfo(NodeInfo node1, NodeInfo node2) {
    return (node1.type == node2.type && strcmp(node1.id, node2.id) == 0 && node1.tag == node2.tag && node1.value == node2.value);
}