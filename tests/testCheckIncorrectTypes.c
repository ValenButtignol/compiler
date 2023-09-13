#include <assert.h>
#include "../include/ast.h"
#include <stdlib.h>

extern FILE *yyin;
extern FILE *yyout;
extern int yyparse(void);

void printFailMessage();
void testCheckIncorrectTypes();

void testCheckIncorrectTypes() {
    yyparse();
    printFailMessage();
    assert(0);
}

void printFailMessage() {
    printf("\033[1;31m"); // Set text color to green
    printf("******************************************************************\n");
    printf("************ Check types Tests FAIL ************\n");
    printf("******************************************************************\n");
    printf("\033[0m"); // Reset text color to default
    printf("\033[1;34m"); // Set text color to green
    printf("----------------------------------------------------------------\n");
    printf("\033[0m"); // Reset text color to default
}

int main(int argc,char *argv[]) {
    ++argv,--argc;
	if (argc > 0)
		yyin = fopen(argv[0],"r");
	else
		yyin = stdin;
    testCheckIncorrectTypes();
    return 0;
}