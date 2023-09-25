#include "../include/symbolTable.h"
#include <assert.h>

static void testSymbolTable01() {
    assert(1);
    // If assert(0) -> Test failed.
}

static void testSymbolTableSuite() {
    testSymbolTable01();
    // Test 2, 3 ...
}