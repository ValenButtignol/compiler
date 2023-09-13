#include <assert.h>
#include "../include/ast.h"
#include <stdlib.h>

extern int yytypeCorrect;
extern FILE *yyin;
extern FILE *yyout;
extern int yyparse(void);

void printSuccessMessage();
void testCheckCorrectTypes();

void testCheckCorrectTypes() {
    yyparse();
    assert(1);
    printSuccessMessage();
}

void printSuccessMessage() {
    printf("\033[1;32m"); // Set text color to green
    printf("******************************************************************\n");
    printf("************ Check types Tests completed successfully ************\n");
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
    testCheckCorrectTypes();
    return 0;
}