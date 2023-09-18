#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdio.h>
#include "nodeInfo.h"

typedef struct SymbolTableNode{
    int level;
    NodeInfo* data;
    struct SymbolTableNode* nextBlock;
    struct SymbolTableNode* nextLevel;

}SymbolTableNode;

typedef struct {
    SymbolTableNode* head;
    int size;
}SymbolTable;

SymbolTableNode* createSymbolNode(void* value, enum TType type, char* id, enum TTag tag);

void initializeSymbolTable(SymbolTable** table);

void addBlockToLevel(SymbolTableNode **level, void* value, enum TType type, char* id, enum TTag tag);

void addNodeInfoToBlock(SymbolTableNode **level, NodeInfo* node);

void addLevelToBlock(SymbolTableNode **block, void* value, enum TType type, char* id, enum TTag tag);

void deleteBlock(SymbolTableNode** block);

void deleteLevelsFromBlock(SymbolTableNode** block);

NodeInfo* searchKey(SymbolTable* block, char* key);

#endif