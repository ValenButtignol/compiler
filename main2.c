#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern FILE *yyin;
extern FILE *yyout;
extern int yyparse(void);

int main(int argc,char *argv[]) {
    ++argv,--argc;
	if (argc > 0)
        yyin = fopen(argv[0], "r");
	else
		yyin = stdin;
    yyparse();
    //TAst* globalAst = getGlobalAst();

}