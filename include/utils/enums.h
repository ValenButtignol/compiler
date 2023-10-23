#ifndef ENUMS_H
#define ENUMS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


enum TBoolean {TRUE, FALSE};
enum TBoolean getBooleanFromText(char* boolean);
char *boolToString(enum TBoolean boolean);


enum TType {INTEGER, BOOLEAN, NONETYPE, ERROR};
enum TType getTypeFromText(char* type);
char *typeToString(enum TType type);

enum TTag {
            PROGRAM, DECL_BLOCK, DECL, 
            VAR_DECL, CONST_DECL, STMT_BLOCK, 
            ASSIGNMENT_OP, RETURN, EXPR_OP, 
            CONST_VALUE, NONETAG, VAR_DECL_BLOCK, 
            VAR, METHOD_DECL_BLOCK, METHOD, 
            PARAM, BLOCK, ASSIGNMENT,
            IF, IF_ELSE, IF_BLOCKS,
            WHILE, ADD, SUB, 
            MUL, DIV, MOD, 
            GREATER_THAN, LESS_THAN, EQUALS,
             AND, OR, NEGATIVE, NOT
        };
enum TTag getTagFromText(char* tag);
char *tagToString(enum TTag tag);
int isTypeableTag(enum TTag tag);

enum TOperator {PLUS, MINUS, MULTIPLY, DIVIDE, ASSIGN, NONOPERATOR};
enum TOperator getOperatorFromText(char* op);
char *operatorToString(enum TOperator op);

#endif