#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "include/ast.h"

extern FILE *yyin;
extern FILE *yyout;
extern int yyparse(void);
extern TAst* getGlobalAst(void);


int main(int argc,char *argv[]) {
    ++argv,--argc;
	if (argc > 0)
        yyin = fopen(argv[0], "r");
	else
		yyin = stdin;
    yyparse();
    TAst* globalAst = getGlobalAst();
    checkType(globalAst);
    evaluateAst(globalAst);
    return 0;
}