#include "../include/nodeInfo.h"

NodeInfo *newNodeInfo(void* value, enum TType type, char* id, enum TTag tag){
    NodeInfo *result = malloc(sizeof(NodeInfo*));  

    setValue(result, value, type);

    result->type = type;
    result->id = strdup(id);     // Remember to free this later.
    result->tag = tag;

    return result;
}

NodeInfo *newEmptyNodeInfo(){
    NodeInfo *result = malloc(sizeof(NodeInfo*));    
    result->value = malloc(sizeof(int*));

    result->value = NULL;
    result->type = EMPTY;
    result->id = "";     // Remember to free this later.
    result->tag = LAMBDA;

    return result;
}

void* setValue(NodeInfo* node, void* value, enum TType type) {
    node->value = malloc(sizeof(value));
    switch(type){
        case INTEGER:
            node->value = value;
        case BOOLEAN:
            node->value = value;

    }

}

//NodeInfo newBoolean(enum TBoolean value, char* id, enum TTag tag);

//NodeInfo newOperator(char* value, char* id, enum TTag tag);

//NodeInfo newNonTerminal(char* value, char* id, enum TTag tag);

char* nodeInfoToString(NodeInfo node){
    return "\n-------------------------------------\nImplementalo vago\n\n";
}

void freeNodeInfo(NodeInfo* node) {
    free(node->value);  
    free(node->id);
}

enum TBoolean getBooleanFromText(char* boolean){
    if(strcmp(boolean, "true")){
        return TRUE;
    }else if(strcmp(boolean, "false")){
        return FALSE;
    }
}

char *boolToString(enum TBoolean boolean){
    if(boolean) return "true";
    if(!boolean) return "false";

}
