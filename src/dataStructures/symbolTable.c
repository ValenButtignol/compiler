#include "../../include/dataStructures/symbolTable.h"


void initializeSymbolTable(SymbolTable** table) {
    *table = malloc(sizeof(SymbolTable));
    if (*table == NULL) {
        fprintf(stderr, "Failed to allocate memory for symbolTable\n");
        exit(1);
    }
    (*table)->decls = NULL;
    (*table)->prevLevel = NULL;
}

void addNodeToSymbolTable(SymbolTable** table, NodeInfo* node) {
    DeclNode* currentDecls = (*table)->decls;
    
    DeclNode* newDecl = malloc(sizeof(DeclNode));
    if (newDecl == NULL) {
        fprintf(stderr, "Failed to allocate memory for symbolTable\n");
        exit(1);
    }
    newDecl->data = node;
    newDecl->nextNode = currentDecls;
    (*table)->decls = newDecl;

}

void addLevelToSymbolTable(SymbolTable** table) {
    SymbolTable* newLevel = malloc(sizeof(SymbolTable));
    if (newLevel == NULL) {
        fprintf(stderr, "Failed to allocate memory for symbolTable\n");
        exit(1);
    }
    newLevel->decls = NULL;
    newLevel->prevLevel = *table;
    *table = newLevel;
}

void popLevelSymbolTable(SymbolTable** table) {
    *table = (*table)->prevLevel;
}

NodeInfo* searchLocalLevelSymbolTable(SymbolTable* table, char* key) {
    DeclNode* currentDecls = table->decls;
    while (currentDecls != NULL) {
        if (strcmp(currentDecls->data->id, key) == 0) {
            return currentDecls->data;
        }
        currentDecls = currentDecls->nextNode;
    }
    return NULL;
}

NodeInfo* searchGlobalLevelSymbolTable(SymbolTable* table, char* key) {
    SymbolTable* currentLevel = table;
    while (currentLevel != NULL) {
        NodeInfo* result = searchLocalLevelSymbolTable(currentLevel, key);
        if (result != NULL) {
            return result;
        }
        currentLevel = currentLevel->prevLevel;
    }
    return NULL;
}

void printSymbolTable(SymbolTable* table) {
    SymbolTable* currentLevel = table;
    int i = 0;
    printf("TOP -> ");
    while (currentLevel != NULL) {
        DeclNode* currentDecls = currentLevel->decls;
        (i == 0) ?  : printf("[] ->") ;
        while (currentDecls != NULL) {
            printf(" %s ->", currentDecls->data->id);
            currentDecls = currentDecls->nextNode;
        }
        printf(" NIL\n");
        i++;
        currentLevel = currentLevel->prevLevel;
    }    
    printf("\n");
    
}