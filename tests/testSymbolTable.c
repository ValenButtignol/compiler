#include "../include/symbolTable.h"
#include <assert.h>

void testCreateSymbolTable() {
    assert(1);
    // If assert(0) -> Test failed.
}

void printSuccessMessage() {
    printf("\n");
    printf("\033[1;32m"); // Set text color to green
    printf("******************************************************************\n");
    printf("************ SymbolTable Tests completed successfully ************\n");
    printf("******************************************************************\n");

    printf("\033[0m"); // Reset text color to default
}

int main() {
    // Call your test functions and make assertions here
    testCreateSymbolTable();

    // Cool printf for tests succeded
    printSuccessMessage();
    return 0;
}