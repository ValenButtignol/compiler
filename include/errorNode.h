#ifndef ERRORNODE_H
#define ERRORNODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ErrorNode {
    char* data;
    struct ErrorNode* next;
} ErrorNode;

ErrorNode* createErrorNode(const char* data);

void insertErrorNode(ErrorNode** head, const char* data);

void printErrors(ErrorNode* head);

void freeErrorsList(ErrorNode* head);

#endif