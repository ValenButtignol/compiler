#ifndef	TYPE_H
#define TYPE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum TType {INTEGER, BOOLEAN, EMPTY};
enum TTag {VARIABLE, CONSTANT, OPERATOR, NONTERMINAL, LAMBDA};
enum TBoolean {TRUE, FALSE};

typedef struct{
	void* value;
	char* id;
	enum TType type;
	enum TTag tag;
}NodeInfo;

NodeInfo *newNodeInfo(void* value, enum TType type, char* id, enum TTag tag);

NodeInfo *newEmptyNodeInfo();

void* setValue(NodeInfo* node, void* value, enum TType type);

void freeNodeInfo(NodeInfo* node);

char* nodeInfoToString(NodeInfo node);

enum TBoolean getBooleanFromText(char* boolean);
char *boolToString(enum TBoolean boolean);
#endif