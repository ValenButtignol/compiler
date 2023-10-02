#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "include/ast.h"
#include "include/threeAddressCodeList.h"
#include "include/assemblyCodeGenerator.h"

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

    // evaluateAst(globalAst);
    ThreeAddressCodeList *list = createEmptyTAC();

    createThreeAddressCodeList(globalAst, list);
    printf("\n--------------------------TAC--------------------------\n%s------------------------------------\n",threeAddressListToString(list));
    
    generateAssembly(list);

    return 0;
}




/*
	.text
    .globl	main
	.type	main, @function
main:
    enter
    ...
    leave
    ret
    
.LFE6:
	.size	main, .-main
	.section	.note.GNU-stack,"",@progbits
*/