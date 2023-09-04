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
    char* string;
    string = malloc(sizeof(char*));
    switch (node.tag)
    {
    case 0:
        strcpy(string, (char*)node.value);
        break;
    case 1:
        strcpy(string, constExpreToString(node));
        break;
    case 2:
        strcpy(string, operatorToString(*(enum TOperator*)node.value));
        break;
    case 3:
        strcpy(string, " ");
        break;
    case 4:
        strcpy(string, " ");
        break;
    case 5:
        strcpy(string, "const");
        break;
    case 6:
        strcpy(string, "return");
        break;
    default:
        return " ";
    }
    return string;
}

char* constExpreToString(NodeInfo node){
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
    if(strcmp(tag, "const") == 0){
        return CONSTANT_DEC;
    }else if(strcmp(tag, "return") == 0){
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