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

enum TType getTypeFromText(char* type){
    if(strcmp(type, "int") == 0){
        return INTEGER;
    }else if(strcmp(type, "boolean") == 0){
        return BOOLEAN;
    }
}
char *typeToString(enum TType type){
    switch (type)
    {
    case 0:
        return "int";
    case 1:
        return "boolean";
    default:
        break;
    }
}

enum TTag getTagFromText(char* tag){
    if(strcmp(tag, "const")){
        return CONSTANT_DEC;
    }else if(strcmp(tag, "return")){
        return RETURN;
    }
}
char *tagToString(enum TTag tag){
    switch (tag)
    {
    case 0:
        return "variable";
    case 1:
        return "const_expr";
    case 2:
        return "operator";
    case 3:
        return "no_terminal";
    case 4:
        return "lambda";
    case 5:
        return "const_dec";
    case 6:
        return "return";
    default:
        break;
    }
}

enum TOperator getOperatorFromText(char* op){
    if(strcmp(op, "+") == 0){
        return PLUS;
    }else if(strcmp(op, "-") == 0){
        return MINUS;
    }else if(strcmp(op, "*") == 0){
        return MULTIPLY;
    }else if(strcmp(op, "/") == 0){
        return DIVIDE;
    }else if(strcmp(op, "=") == 0){
        return ASSIGN;
    }
}
char *operatorToString(enum TOperator op){
    switch (op)
    {
    case 0:
        return "+";
    case 1:
        return "-";
    case 2:
        return "*";
    case 3:
        return "/";
    case 4:
        return "=";
    default:
        break;
    }
}