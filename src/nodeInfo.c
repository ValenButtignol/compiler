#include "../include/nodeInfo.h"

NodeInfo newInteger(int value, char* id, enum TTag tag){
    NodeInfo result;    

    
    result.value = malloc(sizeof(int));
    *((int*)result.value) = value;

    result.id = strdup(id);     // Remember to free this later.
    result.type = INTEGER;
    result.tag = tag;

    return result;
}

NodeInfo newBoolean(enum TBoolean value, char* id, enum TTag tag) {

}

NodeInfo newOperator(char* value, char* id, enum TTag tag);

NodeInfo newNonTerminal(char* value, char* id, enum TTag tag);

char* nodeInfoToString(NodeInfo type){
    char *string = "";
    if(type.boolean != NULL){
        strcat(string, type.boolean ? "true" : "false");
    }
    if(type.integer != NULL){
        char str[] = ""; 
        sprintf(str, "%d", type.integer);
        strcat(string, str);
    }
    if(type.symbol != NULL){
        printf("\n\n%s\n\n", type.symbol);
        strcat(string, type.symbol);
    }
    return string;
}

void freeNodeInfo(NodeInfo* node) {
    free(node->value);  
    free(node->id);
}