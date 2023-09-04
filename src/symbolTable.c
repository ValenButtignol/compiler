#include "../include/symbolTable.h"
#include "../include/nodeInfo.h"
#include <stdio.h>
#include <stdlib.h>

// Function to create a new node with a given data value
SymbolTableNode* createSymbolNode(void* value, enum TType type, char* id, enum TTag tag) {
    SymbolTableNode* newNode = (SymbolTableNode*)malloc(sizeof(SymbolTableNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    newNode->data = newNodeInfo(value, type, id, tag);
    newNode->level = 0;
    newNode->nextBlock = NULL;
    newNode->nextLevel = NULL;

    return newNode;
}

SymbolTable* createSymbolTable() {
    SymbolTable* table = (SymbolTable*)malloc(sizeof(SymbolTable));
    table->head = NULL;
    table->size = 0;
    return table;
}

// Adds a new block to a reference of the actual level.
void addBlockToLevel(SymbolTableNode **level, void* value, enum TType type, char* id, enum TTag tag) {
    SymbolTableNode* newBlock = createSymbolNode(value, type, id, tag);
    if (*level == NULL) {
        *level = newBlock;
        return;
    }
    SymbolTableNode* current = *level;
    while (current->nextBlock != NULL) {
        current = current->nextBlock;
    }
    current->nextBlock = newBlock;
}

// Adds a new level to a reference of the actual block.
void addLevelToBlock(SymbolTableNode **block, void* value, enum TType type, char* id, enum TTag tag) {
    if (*block == NULL) {
        printf("Can't add a new level to NULL block.\n");
        exit(1);
    }
    SymbolTableNode* newLevel = createSymbolNode(value, type, id, tag);
    SymbolTableNode* current = *block;
    if (current->nextLevel == NULL) {
        current->nextLevel = newLevel;
        newLevel->level = current->level + 1;
    }
}



void deleteBlock(SymbolTableNode** block) {
    SymbolTableNode* current = *block;
    if (current != NULL) {
        *block = current->nextBlock;
        deleteLevelsFromBlock(&block);  // Before deleting the block, delete all it's levels.
        free(current);
        return;
    }
}


// Function to delete a node of a given index
void deleteLevelsFromBlock(SymbolTableNode** block) {
    
    SymbolTableNode* currentLevel = (*block)->nextLevel;

    while (currentLevel != NULL) {
        SymbolTableNode* currentBlock = currentLevel->nextBlock;
        SymbolTableNode* levelToDelete = currentLevel;
        
        // Delete every block of the current level.
        while (currentBlock != NULL) {
            SymbolTableNode* blockToDelete = currentBlock;
            currentBlock = currentBlock->nextBlock;
            deleteBlock(&blockToDelete);
        }
        
        currentLevel = currentLevel->nextLevel;
        free(levelToDelete);
    }

}

