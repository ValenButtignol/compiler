#ifndef	TYPE_H
#define TYPE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/enums.h"

typedef struct{
	void* value;
	char* id;
	enum TType type;
	enum TTag tag;
	int lineNumber;
	int offset;
	enum TOperator operator;
}NodeInfo;

NodeInfo* newNodeInfo(void* value, enum TType type, char* id, enum TTag tag, int lineNumber);

NodeInfo *newNodeInfoWithOffset(void* value, enum TType type, char* id, enum TTag tag, int lineNumber, int offset);

NodeInfo* newNodeInfoWithoutValue(enum TType type, char* id, enum TTag tag, int lineNumber);

NodeInfo* newNodeInfoWithoutValueWithOffset(enum TType type, char* id, enum TTag tag, int lineNumber, int offset);

NodeInfo* newNodeInfoOperator(enum TType type, char* id, enum TTag tag, int lineNumber, enum TOperator operator);

NodeInfo* newEmptyNodeInfo();

void* setValue(NodeInfo** node, void* value, enum TType type);

void freeNodeInfo(NodeInfo* node);

char* nodeInfoToString(NodeInfo node);

char* constExprToString(NodeInfo node);

int equalsNodeInfo(NodeInfo node1, NodeInfo node2);

int isEmptyNode(NodeInfo node);

void createTemporalNodeInfo(char* id, enum TTag tag, NodeInfo *temp, int offset);
#endif