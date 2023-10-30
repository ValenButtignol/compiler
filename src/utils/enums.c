#include "../../include/utils/enums.h"

enum TBoolean getBooleanFromText(char* boolean) {
    if (strcmp(boolean, "true")) {
        return TRUE;
    } else if (strcmp(boolean, "false")) {
        return FALSE;
    }
}

char *boolToString(enum TBoolean boolean) {
    if (boolean) return "true";
    if (!boolean) return "false";
}

enum TType getTypeFromText(char* type) {
    if (strcmp(type, "integer") == 0) {
        return INTEGER;
    } else if (strcmp(type, "boolean") == 0) {
        return BOOLEAN;
    } else if (strcmp(type, "void") == 0) {
        return VOID;
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
        return "NOTYPE";
    
    case 3:
        return "ERROR";
    default:
        return "MAYBE NULL :/";
        break;
    }
}

enum TTag getTagFromText(char* tag) {
    if (strcmp(tag, "const") == 0) {
        return CONST_VALUE;
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
        return "VAR_DECL_BLOCK";
    
    case 2:
        return "VAR_DECL";
    
    case 3:
        return "VAR";
    
    case 4:
        return "METHOD_DECL_BLOCK";
    
    case 5:
        return "METHOD_DECL";
    
    case 6:
        return "METHOD_CALL";

    case 7:
        return "PARAM";

    case 8:
        return "BLOCK";
    
    case 9:
        return "STMT_BLOCK";

    case 10:
        return "ASSIGNMENT";
    case 11:
        return "IF";

    case 12:
        return "IF_ELSE";
    case 13:
        return "IF_BLOCKS";
    case 14:
        return "WHILE";
    case 15:
        return "RETURN";
    case 16:
        return "ADD";
    case 17:
        return "SUB";
    case 18:
        return "MUL";
    case 19:
        return "DIV";
    case 20:
        return "MOD";
    case 21:
        return "GREATER_THAN";
    case 22:
        return "LESS_THAN";
    case 23:
        return "EQUALS";
    case 24:
        return "AND";
    case 25:
        return "OR";
    case 26:
        return "NEGATIVE";
    case 27:
        return "NOT";
    case 28:
        return "CONST_VALUE";
    case 29:
        return "NONETAG";
    default:
        return "NULL";
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
        return "NO OPERATOR";
        break;
    }
}

int isTypeableTag(enum TTag tag){
    return tag == VAR || tag == METHOD_DECL || tag ==  METHOD_CALL || tag == PARAM || tag == ASSIGNMENT
            || tag == RETURN || tag ==  ADD || tag == SUB || tag ==  MUL || tag == DIV || tag ==  MOD
            || tag ==  GREATER_THAN || tag ==  LESS_THAN || tag ==  EQUALS || tag ==  AND || tag == OR
            || tag ==  NEGATIVE || tag ==  NOT || tag ==  CONST_VALUE;
}