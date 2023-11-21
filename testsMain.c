#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "include/dataStructures/ast.h"
#include "include/dataStructures/threeAddressCodeList.h"
#include "include/algorithms/checktypes.h"
#include "tests/testGenerateAst.c"
#include "tests/testCheckType.c"
#include "tests/assemblyTestSuite.c"
#include "tests/utils/include/suiteMessages.h"

extern FILE *yyin;
extern FILE *yyout;
extern int yyparse(void);
extern TAst* getGlobalAst(void);
extern ErrorNode* getErrors(void);

static char* getFileName(char* path, char* testType) {
    char* fileName = strrchr(path, '/');
    if (fileName == NULL) {
        fileName = path;
    } else {
        fileName++;
    }
    return fileName;
}

int main(int argc,char *argv[]) {

    ++argv,--argc;
    if (argc > 0) {
        yyin = fopen(argv[0], "r");
    } else {
        yyin = stdin;
    }
    
    yyparse();


    TAst* globalAst = getGlobalAst();
    ErrorNode* errors = getErrors();
    char* testType = argv[1];
    char* fileName = getFileName(argv[0], testType);
    //printAst(globalAst);
    
    if (strcmp(testType, "syntax") == 0) {
        generateAstTestSuite(fileName, globalAst, errors);

    } else if (strcmp(testType, "type") == 0) {
        // if errors != NULL, then there are syntax errors
        checkTypes(globalAst, &errors);
        checkTypeTestSuite(fileName, globalAst, errors);

    } else if (strcmp(testType, "assemble") == 0){
        if (checkTypes(globalAst, &errors)) {
            assemblyTestSuite(fileName);
        } else {
            printTestFailedMessage("Can't assemble, check type FAIL", fileName);
        }
    
    } else {
        printIncorrectTypeTestMessage(testType);
    }
    
    freeErrorsList(errors);
    return 0;

}
