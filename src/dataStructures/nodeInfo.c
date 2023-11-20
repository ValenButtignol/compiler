#include "../../include/dataStructures/nodeInfo.h"

NodeInfo *newNodeInfo(void* value, enum TType type, char* id, enum TTag tag, int lineNumber) {
    NodeInfo *result = malloc(sizeof(NodeInfo*));  

    setValue(&result, value);
    result->type = type;
    result->id = strdup(id);     // Remember to free this later.
    result->tag = tag;
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
    result->lineNumber = lineNumber;
    return result;
}

NodeInfo* newNodeInfoWithoutValueWithOffset(enum TType type, char* id, enum TTag tag, int lineNumber, int offset) {
    NodeInfo* result = newNodeInfoWithoutValue(type, id, tag, lineNumber);
    result->offset = offset;
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

void setValue(NodeInfo** node, void* value) {
    (*node)->value = malloc(sizeof(void*));
    (*node)->value = value;
}

char* nodeInfoToString(NodeInfo node) {
    char* string;
    string = (char*)malloc(20);
    strcpy(string, tagToString(node.tag));
    strcat(string, " ");
    strcat(string, node.id);
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

void createTemporalNodeInfo(char* id, NodeInfo *temp, int offset){
    free(temp->id);
    temp->id = malloc(strlen(id));
    strcpy(temp->id, id);
    temp->offset = offset;
}

NodeInfo* createLabelNodeInfo(char* label, int labelNumber) {
    NodeInfo* node = newNodeInfoSimple(LABEL, 0);
    node->id = (char*)malloc(strlen(label)+1); 
    strcpy(node->id, createIDNodeInfo(label, labelNumber));
    return node;
}

char* createIDNodeInfo(char* id, int number){
    char* newId = malloc(strlen(id) + 1);
    char* num = malloc(2);
    strcpy(newId, id);
    sprintf(num, "%d", number);
    strcat(newId, num);
    return newId;
}

char* createTemporalID(int tempNumber){
    return createIDNodeInfo("temp", tempNumber);
}


int equalsNodeInfo(NodeInfo* firstNode, NodeInfo* secondNode) {

    int idsComp = (firstNode->id && secondNode->id) ? strcmp(firstNode->id, secondNode->id) : 0;
    if ((firstNode->id != NULL && secondNode->id == NULL) || (firstNode->id == NULL && secondNode->id != NULL)) {
        idsComp = 1;
    }

    return (*(int*)firstNode->value == *(int*)secondNode->value) && (idsComp == 0) &&
           (firstNode->type == secondNode->type) &&
           (firstNode->tag == secondNode->tag);
}

/****************************** new constructors ********************************/

NodeInfo* newNodeInfoSimple(enum TTag tag, int lineNumber) {
    NodeInfo *result = malloc(sizeof(NodeInfo));    

    result->value = NULL;
    result->type = NONETYPE;
    result->tag = tag;
    result->lineNumber = lineNumber;
    result->offset = 0;
    result->nextParams = NULL;
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

NodeInfo* newNodeInfoRegisterNumber(int registerNumber){
    NodeInfo* result = newNodeInfoSimple(LOAD, 0);
    result->lineNumber = registerNumber;
    return result;
}

NodeInfo* newNodeInfoTemporal(enum TTag tag) {
    NodeInfo* result = newNodeInfoSimple(tag, 0);
    result->id = (char*)malloc(strlen(" ")*sizeof(char)); 
    strcpy(result->id, " ");
    return result;
}

int nodeInfoIDEquals(NodeInfo* t, NodeInfo* param){
    printf("comparando %s %s comp = %d\n", t->id, param->id);
    if(t->id == NULL || param->id == NULL) return 0;
    return strcmp(t->id, param->id) == 0;
}

void setNewOffset(NodeInfo** node, int offset){
    (*node)->offset = offset;
}