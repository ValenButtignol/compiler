#ifndef	TYPE_H
#define TYPE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const enum TType {INTEGER, BOOLEAN};
const enum TTag {VARIABLE, CONSTANT, OPERATOR, NONTERMINAL};
const enum TBoolean {TRUE, FALSE};

typedef struct {
	void* value;
	char* id;
	enum TType type;
	enum TTag tag;
}NodeInfo;

NodeInfo *newInteger(int value, char* id, enum TTag tag);

//NodeInfo newBoolean(enum TBoolean value, char* id, enum TTag tag);

//NodeInfo newOperator(char* value, char* id, enum TTag tag);

//NodeInfo newNonTerminal(char* value, char* id, enum TTag tag);

NodeInfo *newNodeInfo(void* value, enum TType type, char* id, enum TTag tag);

void* getValue(NodeInfo* node, void* value, enum TType type);

void freeNodeInfo(NodeInfo* node);

#endif