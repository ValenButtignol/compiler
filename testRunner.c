#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "include/ast.h"
#include "tests/testEvalAst.c"
#include "tests/testCheckType.c"

extern FILE *yyin;
extern FILE *yyout;
extern int yyparse(void);
extern TAst* getGlobalAst(void);

static char* getFileName(char* path) {
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
        if (strcmp(argv[0], "z.txt") == 0) {
            return 0;
        }
        yyin = fopen(argv[0], "r");
    } else {
        yyin = stdin;
    }
    
    yyparse();
    TAst* globalAst = getGlobalAst();
    
    char* fileName = getFileName(argv[0]);
    char* testType = argv[1];
    

    ErrorNode* errors = NULL;

    if(strcmp(testType, "type") == 0){
        // if (checkTypes(globalAst, &errors)) {
        //     printf("Chequeo de tipos = OK\n");
        // } else {
        //     printf("Chequeo de tipos = ERROR\n");
        //     printErrors(errors);
        // }
        checkTypes(globalAst, &errors);
        checkTypeTestSuite(fileName, globalAst, &errors);
    }
    else if(strcmp(testType, "eval") == 0){
        if (checkTypes(globalAst, &errors)) {
            printf("Chequeo de tipos = OK\n");
            evaluateAst(globalAst);;
            evalAstTestSuite(fileName, globalAst);
        } else {
            printTestFailedMessage("CheckTypes", fileName);
        }
    }else{
        printIncorrectTypeTestMessage(testType);
    }
    freeErrorsList(errors);
    return 0;

}
