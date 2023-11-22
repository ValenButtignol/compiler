#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "include/dataStructures/ast.h"
#include "include/dataStructures/nodeInfo.h"
#include "include/algorithms/checktypes.h"
#include "include/dataStructures/threeAddressCodeList.h"
#include "include/dataStructures/nodeInfoStack.h"
#include "include/algorithms/assemblyCodeGenerator.h"

extern FILE *yyin;
extern FILE *yyout;
extern int yyparse(void);
extern TAst* getGlobalAst();
extern ErrorNode* getErrors();

int main(int argc,char *argv[]) {
    ++argv,--argc;
    char* filename = argv[0];
    if(!hasBokExtension(filename)){
        printf("\033[1;31mError:\033[0m file format not recognized\n");
        exit(1);
    }
	if (argc > 0)
        yyin = fopen(argv[0], "r");
	else
		yyin = stdin;
    yyparse();
    TAst* globalAst = getGlobalAst();
    ErrorNode* errors = getErrors();
    if (errors != NULL) {
        printErrors(errors);
        freeErrorsList(errors);
        exit(EXIT_FAILURE);
    } 
    // printf("\n---------------------------------------------- \n");
    if (!checkTypes(globalAst, &errors)) {
        printErrors(errors);
        freeErrorsList(errors);
        exit(EXIT_FAILURE);
    }
    // printf("CHEACK TYPES COMPLETE %d\n", 1);

    ThreeAddressCodeList *list = createEmptyTAC();

    int offset = 0;
    int labelCounter = 0;

    //printAst(globalAst);
    NodeInfoStack *parameterStack = createEmptyNodeInfoStack();
    createThreeAddressCodeList(globalAst, list, &offset, &labelCounter, parameterStack);
    // printf("PARSE COMPLETE %d\n", 1);
    // printf("TERMINE\n");
    // printf("\n--------------------------TAC--------------------------\n%s--------------------------------------------------------\n",threeAddressListToString(list));
    char* assemblyFilename = generateAssemblyFilename(filename);
    generateAssembly(list, assemblyFilename);
}