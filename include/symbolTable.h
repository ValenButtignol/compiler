#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdio.h>
#include "nodeInfo.h"

typedef struct DeclNode {
    NodeInfo* data;
    struct DeclNode* nextNode;
}DeclNode;

typedef struct SymbolTable {
    DeclNode* decls;
    struct SymbolTable* prevLevel;
}SymbolTable;

void initializeSymbolTable(SymbolTable** table);

void addNodeToSymbolTable(SymbolTable** table, NodeInfo* node);

void addLevelToSymbolTable(SymbolTable** table);

void popLevelSymbolTable(SymbolTable** table);

NodeInfo* searchLocalLevelSymbolTable(SymbolTable** table, char* key);

NodeInfo* searchGlobalLevelSymbolTable(SymbolTable** table, char* key);

#endif