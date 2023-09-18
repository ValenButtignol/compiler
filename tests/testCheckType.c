#include "../include/ast.h"
#include "utils/include/createInputs.h"
#include <assert.h>

static void testCheckType01(){
}


static void printSuccessMessage() {
    printf("\n");
    printf("\033[1;32m"); // Set text color to green
    printf("******************************************************************\n");
    printf("************ Check Type Tests completed successfully ************\n");
    printf("******************************************************************\n");
    printf("\n");
    printf("\n");

    printf("\033[0m"); // Reset text color to default
}


static void checkTypeTestSuite(char* inputTestFileName, TAst* globalAst) {
    testCheckType01();
    printSuccessMessage();
}