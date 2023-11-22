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
    } else if (strcmp(type, "bool") == 0) {
        return BOOLEAN;
    } else if (strcmp(type, "void") == 0) {
        return VOID;
    }
}

char *typeToString(enum TType type) {
    switch (type) {
    case INTEGER:
        return "integer";
    case BOOLEAN:
        return "boolean";
    case VOID:
        return "VOID";
    case NONETYPE:
        return "NONETYPE";
    case ERROR:
        return "ERROR";
    default:
        return "MAYBE NULL :/";
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
    switch (tag) {
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
        return "LABEL";
    case 30:
        return "JFALSE";
    case 31:
        return "JUMP";
    case 32:
        return "LOAD";
    case 33:
        return "END_LABEL";
    case 34:
        return "EXTERN_METHOD_DECL";
    case 35:
        return "NONETAG";
    default:
        return "NULL";
    }
}

char *operatorToString(enum TTag tag) {
    switch (tag) {
    case 2:
        return "=";
    case 10:
        return "=";
    case 15:
        return "RETURN";
    case 16:
        return "+";
    case 17:
        return "-";
    case 18:
        return "*";
    case 19:
        return "/";
    case 20:
        return "%";
    case 21:
        return ">";
    case 22:
        return "<";
    case 23:
        return "==";
    case 24:
        return "&&";
    case 25:
        return "||";
    case 26:
        return "-";
    case 27:
        return "!";
    default:
        return "NO OPERATOR";
    }
}

int isTypeableTag(enum TTag tag){
    return  tag == ASSIGNMENT || tag ==  ADD || tag == SUB || tag ==  MUL || tag == DIV || tag ==  MOD
        || tag ==  GREATER_THAN || tag ==  LESS_THAN || tag ==  EQUALS || tag ==  AND || tag == OR
        || tag ==  NEGATIVE || tag ==  NOT || tag == VAR_DECL;
}

int isAssignTag(enum TTag tag){
    return  tag == ASSIGNMENT || tag == VAR_DECL;
}

int isArithmeticOperatorTag(enum TTag tag){
    return  tag ==  ADD || tag == SUB || tag ==  MUL || tag == DIV || tag ==  MOD;
}

int isRelationalOperatorTag(enum TTag tag){
    return tag ==  GREATER_THAN || tag ==  LESS_THAN || tag == EQUALS;
}

int isComparatorTag(enum TTag tag){
    return tag ==  EQUALS;
}

int isBooleanOperatorTag(enum TTag tag){
    return tag ==  AND || tag == OR;
}

int isUnaryOperatorTag(enum TTag tag){
    return tag ==  NEGATIVE || tag ==  NOT;
}

int isReturnTag(enum TTag tag){
    return tag ==  RETURN;
}

int isIf(enum TTag tag) {
    return tag == IF;
}

int isIfElse(enum TTag tag) {
    return tag == IF_ELSE;
}

int isWhile(enum TTag tag) {
    return tag == WHILE;
}

int isMethodCallTag(enum TTag tag){
    return tag == METHOD_CALL; 
}

int isMethodDeclTag(enum TTag tag){
    return tag == METHOD_DECL; 
}

int isArithmeticOrBooleanTag(enum TTag tag){
    return isBooleanOperatorTag(tag) || isArithmeticOperatorTag(tag);
}