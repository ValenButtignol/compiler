#include "../include/enums.h"

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