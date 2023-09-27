#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "include/ast.h"
#include "include/threeAddressCodeList.h"

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

    ErrorNode* errors = NULL;
    checkTypes(globalAst, &errors);

    //printf("Chequeo de tipos = %d");
    // checkType(globalAst);
    // evaluateAst(globalAst);
    ThreeAddressCodeList *list = createEmptyTAC();
    //createThreeAddressCodeList(globalAst, list);
    printf("\n--------------------------TAC--------------------------\n%s------------------------------------\n",threeAddressListToString(list));
    return 0;
}