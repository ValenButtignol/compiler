#include "testCheckType.c"
#include "testSymbolTable.c"


static void runTests() {
    testCheckTypeSuite();
    testSymbolTableSuite();

    return ;
}