#include "../include/symbolTable.h"
#include <assert.h>

static void testSymbolTable01() {
    assert(1);
    // If assert(0) -> Test failed.
}


static void printSymbolTableTestsSuccessMessage() {
    printf("\n");
    printf("\033[1;32m"); // Set text color to green
    printf("******************************************************************\n");
    printf("************ SymbolTable Tests completed successfully ************\n");
    printf("******************************************************************\n");
    printf("\n");
    printf("\n");

    printf("\033[0m"); // Reset text color to default
}


static void testSymbolTableSuite() {
    testSymbolTable01();
    // Test 2, 3 ...
    printSymbolTableTestsSuccessMessage();
}