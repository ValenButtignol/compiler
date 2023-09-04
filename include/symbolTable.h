#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdio.h>

typedef struct {
    int level;
    NodeInfo data;
    SymbolTableNode* nextBlock;
    SymbolTableNode* nextLevel;

}SymbolTableNode;

typedef struct {
    SymbolTableNode* head;
    int size;
}SymbolTable;

SymbolTableNode* createSymbolNode(void* value, enum TType type, char* id, enum TTag tag);

SymbolTable* createSymbolTable();

void addBlockToLevel(SymbolTableNode **level, void* value, enum TType type, char* id, enum TTag tag);

void addLevelToBlock(SymbolTableNode **block, void* value, enum TType type, char* id, enum TTag tag);

void deleteBlock(SymbolTableNode** block);

void deleteLevelsFromBlock(SymbolTableNode** block);

#endif