#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "include/dataStructures/ast.h"
#include "include/dataStructures/nodeInfo.h"
#include "include/algorithms/checktypes.h"
extern FILE *yyin;
extern FILE *yyout;
extern int yyparse(void);
extern TAst* getGlobalAst();
int main(int argc,char *argv[]) {
    ++argv,--argc;
	if (argc > 0)
        yyin = fopen(argv[0], "r");
	else
		yyin = stdin;
    yyparse();
    TAst* globalAst = getGlobalAst();
    ErrorNode* errors = NULL;
    printf("PARSE COMPLETE %d\n", globalAst==NULL);
    printf("\n---------------------------------------------- \n");
    printAst(globalAst);
    if(!checkTypes(globalAst, &errors)){
        printErrors(errors);
    }
    
}