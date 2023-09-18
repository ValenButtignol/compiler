#include <string.h>
#include <assert.h>
#include "../include/ast.h"

static void testValidInput1(TAst* globalAst) {
    

    assert(1);
}

static void evalAstTestSuite(char* inputTestFileName, TAst* globalAst) {
    if (strcmp(inputTestFileName, "validInput1.txt") == 0) {
        testValidInput1(globalAst);
    }
    return ;
}