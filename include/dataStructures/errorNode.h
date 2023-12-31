#ifndef ERRORNODE_H
#define ERRORNODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/enums.h"

typedef struct ErrorNode {
    char* data;
    struct ErrorNode* next;
} ErrorNode;

ErrorNode* createErrorNode(const char* data);

void insertErrorNode(ErrorNode** head, const char* data);

void printErrors(ErrorNode* head);

void freeErrorsList(ErrorNode* head);

int equalsErrorNode(ErrorNode* error1, ErrorNode* error2);

void addOperationError(ErrorNode** errors, int lineNumber, enum TTag tag);

void addMethodCallError(ErrorNode** errors, int lineNumber, char* message, char* methodName);

void addDivByZeroError(ErrorNode** errors, int lineNumber, enum TTag tag);

void addVariableIDDeclaredError(ErrorNode** errors, int lineNumber, char* id);

void addProcedureIDDeclaredError(ErrorNode** errors, int lineNumber, char* id);

void addParameterIDDeclaredError(ErrorNode** errors, int lineNumber, char* id);

void addIDDeclaredError(ErrorNode** errors, int lineNumber, char* id, const char* typeOfID);

void addVariableIDNotDeclaredError(ErrorNode** errors, int lineNumber, char* id);

void addProcedureIDNotDeclaredError(ErrorNode** errors, int lineNumber, char* id);

void addIDNotDeclaredError(ErrorNode** errors, int lineNumber, char* id, const char* typeOfID);

#endif