#ifndef	TYPE_H
#define TYPE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/enums.h"

typedef struct NodeInfo{
	void* value;
	char* id;
	enum TType type;
	enum TTag tag;
	int lineNumber;
	int offset;
	struct NodeInfo* nextParams;
}NodeInfo;

NodeInfo* newNodeInfo(void* value, enum TType type, char* id, enum TTag tag, int lineNumber);

NodeInfo *newNodeInfoWithOffset(void* value, enum TType type, char* id, enum TTag tag, int lineNumber, int offset);

NodeInfo* newNodeInfoWithoutValue(enum TType type, char* id, enum TTag tag, int lineNumber);

NodeInfo* newNodeInfoWithoutValueWithOffset(enum TType type, char* id, enum TTag tag, int lineNumber, int offset);

NodeInfo* newEmptyNodeInfo();

void setValue(NodeInfo** node, void* value);

void freeNodeInfo(NodeInfo* node);

char* nodeInfoToString(NodeInfo node);

char* constExprToString(NodeInfo node);

int isEmptyNode(NodeInfo node);

int equalsNodeInfo(NodeInfo* firstNode, NodeInfo* secondNode);

void createTemporalNodeInfo(char* id, NodeInfo *temp, int offset);

NodeInfo* createLabelNodeInfo(char* label, int labelNumber);

char* createIDNodeInfo(char* id, int labelNumber);

char* createEndThenTemporalNodeInfo(int labelNumber);

char* createTemporalID(int tempNumber);

int nodeInfoIDEquals(NodeInfo* t, NodeInfo* param);

/****************************** new constructors ********************************/

NodeInfo* newNodeInfoSimple(enum TTag tag, int lineNumber);

NodeInfo* newNodeInfoType(enum TType type, enum TTag tag, int lineNumber);

NodeInfo* newNodeInfoDeclaration(char* id, enum TType type, enum TTag tag, int lineNumber, int offset);

NodeInfo* newNodeInfoLiteral(void* value, enum TType type, enum TTag tag, int lineNumber);

NodeInfo* newNodeInfoRegisterNumber(int registerNumber);

NodeInfo* newNodeInfoTemporal(enum TTag tag);

int nodeInfoIDEquals(NodeInfo* t, NodeInfo* param);

void setNewOffset(NodeInfo** node, int offset);

void setNewTag(NodeInfo** node, enum TTag tag);

#endif