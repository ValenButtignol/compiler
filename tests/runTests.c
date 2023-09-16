#include "testCheckType.c"
#include "testSymbolTable.c"


int main() {
    // Call your test functions and make assertions here
    testSymbolTableSuite();
    testCheckTypeSuite();

    return 0;
}