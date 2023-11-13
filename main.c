#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "include/dataStructures/ast.h"
#include "include/dataStructures/nodeInfo.h"
#include "include/algorithms/checktypes.h"
#include "include/dataStructures/threeAddressCodeList.h"
extern FILE *yyin;
extern FILE *yyout;
extern int yyparse(void);
extern TAst* getGlobalAst();
extern ErrorNode* getErrors();
// extern int getOffset();
int main(int argc,char *argv[]) {
    ++argv,--argc;
	if (argc > 0)
        yyin = fopen(argv[0], "r");
	else
		yyin = stdin;
    yyparse();
    TAst* globalAst = getGlobalAst();
    ErrorNode* errors = getErrors();
    if (errors != NULL) {
        // printf("ERRORS:\n");
        // printf("---------------------------------------------:\n");
        printErrors(errors);
        freeErrorsList(errors);
    } 
    // printf("\n---------------------------------------------- \n");
    // printAst(globalAst);
    // printf("PARSE COMPLETE %d\n", 1);
    if (!checkTypes(globalAst, &errors)) {
        printErrors(errors);
        freeErrorsList(errors);
    }
    printf("CHEACK TYPES COMPLETE %d\n", 1);

    ThreeAddressCodeList *list = createEmptyTAC();

    int offset = 10;//getOffset();

    createThreeAddressCodeList(globalAst, list, &offset);
    printf("TERMINE\n");
    printf("\n--------------------------TAC--------------------------\n%s------------------------------------\n",threeAddressListToString(list));
}