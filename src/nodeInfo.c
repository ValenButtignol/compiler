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

enum TBoolean getBooleanFromText(char* boolean) {
    if (strcmp(boolean, "true")) {
        return TRUE;
    } else if(strcmp(boolean, "false")) {
        return FALSE;
    }
}

char *boolToString(enum TBoolean boolean) {
    if (boolean) return "true";
    if (!boolean) return "false";
}

enum TType getTypeFromText(char* type) {
    if (strcmp(type, "int") == 0) {
        return INTEGER;
    } else if (strcmp(type, "boolean") == 0) {
        return BOOLEAN;
    }
}

char *typeToString(enum TType type) {
    switch (type)
    {
    case 0:
        return "int";

    case 1:
        return "boolean";
    
    case 2:
        return "";
    
    default:
        break;
    }
}

enum TTag getTagFromText(char* tag) {
    if (strcmp(tag, "const") == 0) {
        return CONST_DECL;
    } else if (strcmp(tag, "return") == 0) {
        return RETURN;
    }
}

char *tagToString(enum TTag tag) {
    switch (tag)
    {
    case 0:
        return "PROGRAM";
    
    case 1:
        return "DECL_BLOCK";
    
    case 2:
        return "DECL";
    
    case 3:
        return "VAR_DECL";
    
    case 4:
        return "CONST_DECL";
    
    case 5:
        return "STMT_BLOCK";
    
    case 6:
        return "ASSIGNMENT_OP";

    case 7:
        return "RETURN";

    case 8:
        return "EXPR_OP";
    
    case 9:
        return "CONST_VALUE";

    case 10:
        return "NONETAG";
    
    default:
        break;
    }
}

enum TOperator getOperatorFromText(char* op) {
    if (strcmp(op, "+") == 0) {
        return PLUS;
    } else if (strcmp(op, "-") == 0) {
        return MINUS;
    } else if (strcmp(op, "*") == 0) {
        return MULTIPLY;
    } else if (strcmp(op, "/") == 0) {
        return DIVIDE;
    } else if (strcmp(op, "=") == 0) {
        return ASSIGN;
    }
}

char *operatorToString(enum TOperator op) {
    switch (op) {
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

int isEmptyNode(NodeInfo node) {
    return node.value == NULL && node.type == NONETYPE && node.id == "" && node.tag == NONETAG;
}