#ifndef ENUMS_H
#define ENUMS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


enum TBoolean {TRUE, FALSE};
enum TBoolean getBooleanFromText(char* boolean);
char *boolToString(enum TBoolean boolean);

enum TType {INTEGER, BOOLEAN, VOID, NONETYPE, ERROR};
enum TType getTypeFromText(char* type);
char *typeToString(enum TType type);

enum TTag {PROGRAM, VAR_DECL_BLOCK, VAR_DECL, VAR, METHOD_DECL_BLOCK, METHOD_DECL, METHOD_CALL, PARAM, BLOCK, 
                STMT_BLOCK, ASSIGNMENT, IF, IF_ELSE, IF_BLOCKS, WHILE, RETURN, ADD, SUB, MUL, 
                DIV, MOD, GREATER_THAN, LESS_THAN, EQUALS, AND, OR, NEGATIVE, NOT, CONST_VALUE, LABEL, JFALSE, JTRUE, NONETAG
        };
enum TTag getTagFromText(char* tag);
char *tagToString(enum TTag tag);
int isTypeableTag(enum TTag tag);
int isArithmeticOperatorTag(enum TTag tag);
int isRelationalOperatorTag(enum TTag tag);
int isComparatorTag(enum TTag tag);
int isBooleanOperatorTag(enum TTag tag);
int isUnaryOperatorTag(enum TTag tag);
int isAssignTag(enum TTag tag);
char *operatorToString(enum TTag tag);
int isReturnTag(enum TTag tag);
int isIf(enum TTag tag);
int isIfElse(enum TTag tag);
int isWhile(enum TTag tag);
int isArithmeticOrBooleanTag(enum TTag tag);
int isMethodCallTag(enum TTag tag);

#endif