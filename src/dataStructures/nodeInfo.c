#include "../../include/dataStructures/nodeInfo.h"

NodeInfo *newNodeInfo(void* value, enum TType type, char* id, enum TTag tag, int lineNumber) {
    NodeInfo *result = malloc(sizeof(NodeInfo*));  

    setValue(&result, value);
    result->type = type;
    result->id = strdup(id);     // Remember to free this later.
    result->tag = tag;
    result->operatorVar = NONOPERATOR;
    result->lineNumber = lineNumber;
    return result;
}

NodeInfo *newNodeInfoWithOffset(void* value, enum TType type, char* id, enum TTag tag, int lineNumber, int offset) {
    NodeInfo* result = newNodeInfo(value, type, id, tag, lineNumber);
    result->offset = offset;
    return result;
}

NodeInfo* newNodeInfoWithoutValue(enum TType type, char* id, enum TTag tag, int lineNumber) {
    NodeInfo *result = malloc(sizeof(NodeInfo*));    

    result->value = malloc(sizeof(int*));
    result->value = NULL;
    result->type = type;
    result->id = strdup(id); 
    result->tag = tag;
    result->operatorVar = NONOPERATOR;
    result->lineNumber = lineNumber;
    return result;
}

NodeInfo* newNodeInfoWithoutValueWithOffset(enum TType type, char* id, enum TTag tag, int lineNumber, int offset) {
    NodeInfo* result = newNodeInfoWithoutValue(type, id, tag, lineNumber);
    result->offset = offset;
    return result; 
}

NodeInfo* newNodeInfoOperator(enum TType type, char* id, enum TTag tag, int lineNumber, enum TOperator operator){
    NodeInfo* node = newNodeInfoWithoutValue(type, id, tag, lineNumber);
    node->operatorVar = operator;
    return node;    
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

void setValue(NodeInfo** node, void* value) {
    (*node)->value = malloc(sizeof(void*));
    (*node)->value = value;
}

char* nodeInfoToString(NodeInfo node) {
    char* string;
    string = (char*)malloc(20);
    strcpy(string, tagToString(node.tag));
    return string;
}

char* constExprToString(NodeInfo node) {
    switch (node.type)
    {
    case 0:
        char* s = malloc(sizeof(char*));
        sprintf(s, "%d",*(int*)node.value);
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
    // printf("value %d\n", (int*)node1.value!=NULL? *(int*)node1.value : -9999);
    // printf("%d == %d\n", *(int*)node1.value, node2.value);
    return (node1.type == node2.type && strcmp(node1.id, node2.id) == 0 && node1.tag == node2.tag && 
    ((int*)node1.value!=NULL? *(int*)node1.value : NULL) == node2.value);
}

void createTemporalNodeInfo(char* id, enum TTag tag, NodeInfo *temp, int offset){
    free(temp->id);
    temp->id = malloc(20);
    strcpy(temp->id, id);
    temp->tag = tag;
    temp->offset = offset;
}

/****************************** new constructors ********************************/

NodeInfo* newNodeInfoSimple(enum TTag tag, int lineNumber) {
    NodeInfo *result = malloc(sizeof(NodeInfo));    

    result->value = NULL;
    result->type = NONETYPE;
    result->operatorVar = NONOPERATOR;
    result->tag = tag;
    result->lineNumber = lineNumber;
    result->offset = 0;
    return result;
}

NodeInfo* newNodeInfoType(enum TType type, enum TTag tag, int lineNumber) {
    NodeInfo* result = newNodeInfoSimple(tag, lineNumber);
    result->type = type;
    return result;
}

NodeInfo* newNodeInfoDeclaration(char* id, enum TType type, enum TTag tag, int lineNumber, int offset) {
    NodeInfo* result = newNodeInfoSimple(tag, lineNumber);
    result->type = type;
    result->id = (char*)malloc(strlen(id)*sizeof(char)); 
    strcpy(result->id, id);
    result->offset = offset; 
    return result;
}

NodeInfo* newNodeInfoLiteral(void* value, enum TType type, enum TTag tag, int lineNumber) {
    NodeInfo* result = newNodeInfoSimple(tag, lineNumber);
    result->type = type;
    setValue(&result, value);
    return result;
}
