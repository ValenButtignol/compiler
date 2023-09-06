#include "../include/symbolTable.h"
#include <assert.h>

void testCreateSymbolTable() {
    SymbolTable* table = initializeSymbolTable();

    assert(table->head == NULL);
    assert(table->size == 0);
    assert(table->head->level = 0);
    assert(table->head->nextBlock = NULL);
    assert(table->head->nextLevel = NULL);
}