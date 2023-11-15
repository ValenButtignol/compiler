#include "../../include/algorithms/assemblyCodeGenerator.h"
#include <stdint.h>

void generateAssembly(ThreeAddressCodeList* list) {
    FILE* file = fopen("assembly.s", "w");
    if (file == NULL) {
        // Error handling code
        perror("Error opening the file");
        exit(1); // Return a non-zero value to indicate failure
    }

    generateHeader(file, list);
    generatePrologue(file, list);
    ThreeAddressCodeNode* current = list->head->next;

    while (current != NULL) {
        instructionFactory(file, current);
        current = current->next;
    }

    fprintf(file, "    leave\n");       // TODO: This is not correct, we need to generate the epilogue
    fprintf(file, "    ret\n");

    fclose(file);
}

void generatePrologue(FILE* file, ThreeAddressCodeList* list) {
    fprintf(file, "    pushq   %%rbp\n");
    fprintf(file, "    movq    %%rsp, %%rbp\n");
    fprintf(file, "    subq    $64, %%rsp\n\n");
}

void generateHeader(FILE* file, ThreeAddressCodeList* list) {     // Probably this would be converted into generatePrologue
    fprintf(file, "    .text\n");
    fprintf(file, "    .globl  main\n");
    fprintf(file, "    .type   main, @function\n");
    fprintf(file, "main:\n");
}


void instructionFactory(FILE* file, ThreeAddressCodeNode* current) {

    char* firstValue = generateValue(current->first);
    char* secondValue = generateValue(current->second);
    char* thirdValue = generateValue(current->third);

    // printf("LABEL = %s\n", labelToString(current->label));
    // printf("\n\n\nPRIMERO: %s\n", firstValue);
    // printf("SEGUNDO: %s\n", secondValue);
    // printf("TERCERO: %s\n\n\n", thirdValue);
    
    switch(current->label) {
        case ADD:
            generateAdd(file, firstValue, secondValue, thirdValue);
            break;
        case SUB:
            generateSub(file, firstValue, secondValue, thirdValue);
            break;
        case MUL:
            generateMul(file, firstValue, secondValue, thirdValue);
            break;
        case DIV:
            generateDiv(file, firstValue, secondValue, thirdValue);
            break;
        case AND:
            generateAnd(file, firstValue, secondValue, thirdValue);
            break;
        case OR:
            generateOr(file,  firstValue, secondValue, thirdValue);
            break;
        case ASSIGNMENT:
            generateMov(file, firstValue, secondValue);
            break;
        case RETURN:
            generateRet(file, firstValue);
            break;
        case LABEL:
            generateLabel(file, firstValue);
            break;
        case EQUALS:
            generateEquals(file, firstValue, secondValue, thirdValue);
            break;
        case GREATER_THAN:
            generateGreaterThan(file, firstValue, secondValue, thirdValue);
            break;
        case LESS_THAN:
            generateLessThan(file, firstValue, secondValue, thirdValue);
            break;
        /* 
        case JFALSE:
            break;
        case JTRUE:
            break;
        case MOD:
            break;
        case NEGATIVE:
            break;
        case NOT:
            break; */

        default:
            break;
    }

    free(firstValue);
    free(secondValue);
    free(thirdValue);
}

void generateAdd(FILE* file, char* firstValue, char* secondValue, char* thirdValue) {
    fprintf(file, "    movl    %s, %%rax\n", secondValue);
    fprintf(file, "    addl    %s, %%rax\n", thirdValue);
    fprintf(file, "    movl    %%rax, %s\n", firstValue);
    fprintf(file, "\n");
}


void generateSub(FILE* file, char* firstValue, char* secondValue, char* thirdValue) {
    fprintf(file, "    movl    %s, %%rax\n", secondValue);
    fprintf(file, "    subl    %s, %%rax\n", thirdValue);
    fprintf(file, "    movl    %%rax, %s\n", firstValue);
    fprintf(file, "\n");
}

void generateMul(FILE* file, char* firstValue, char* secondValue, char* thirdValue) {
    fprintf(file, "    movl    %s, %%rax\n", secondValue);
    fprintf(file, "    movl    %s, %%rbx\n", thirdValue);
    fprintf(file, "    imul    %%rax, %%rbx\n");
    fprintf(file, "    movl    %%rbx, %s\n", firstValue);
    fprintf(file, "\n");
}

void generateDiv(FILE* file, char* firstValue, char* secondValue, char* thirdValue) {
    fprintf(file, "    movl    %s, %%rax\n", secondValue);  // Dividend
    fprintf(file, "    movl    %s, %%rbx\n", thirdValue);   // Divisor
    fprintf(file, "    xor     %%rdx, %%rdx\n");            // Clear rdx to prepare for the result
    fprintf(file, "    div     %%rbx\n");                   // Divide rax by rbx, quotient in rax, remainder in rdx
    fprintf(file, "    movl    %%rax, %s\n", firstValue);   // Store value
    fprintf(file, "\n");
}

void generateAnd(FILE* file, char* firstValue, char* secondValue, char* thirdValue) {
    fprintf(file, "    movl    %s, %%rax\n", secondValue);
    fprintf(file, "    movl    %s, %%rbx\n", thirdValue);
    fprintf(file, "    andl    %%rbx, %%rax\n");
    fprintf(file, "    movl    %%rax, %s\n", firstValue);
    fprintf(file, "\n");
}

void generateOr(FILE* file, char* firstValue, char* secondValue, char* thirdValue) {
    fprintf(file, "    movl    %s, %%rax\n", secondValue);
    fprintf(file, "    movl    %s, %%rbx\n", thirdValue);
    fprintf(file, "    orl     %%rbx, %%rax\n");
    fprintf(file, "    movl    %%rax, %s\n", firstValue);
    fprintf(file, "\n");
}

void generateMov(FILE* file, char* firstValue, char* secondValue) {
    fprintf(file, "    movl    %s, %%rax\n", secondValue);
    fprintf(file, "    movl    %%rax, %s\n", firstValue);
    fprintf(file, "\n");
}

void generateRet(FILE* file, char* firstValue) {
    generatePrint(file, firstValue);

    fprintf(file, "    movl    %s, %%rax\n", firstValue);
    // fprintf(file, "    leave\n");       // TODO: This is not correct, we need to generate the epilogue
    // fprintf(file, "    ret\n");
    fprintf(file, "\n");

}

char* generateValue(NodeInfo* node) {
    // printf("ID: %s\n", node->id);
    // printf("VALUE: %d\n", ((int *)node->value)!=NULL?*((int *)node->value):-9999);
    // // printf("VALUE: %lu\n", (uintptr_t)node->value);
    // printf("TAG: %s\n",tagToString(node->tag));
    // printf("OFFSET: %d\n\n", node->offset);
    // printf("TYPE: %d\n\n",  node->type);
    char* result;
    result = (char*)malloc(20);
    if (result == NULL) {
        printf("Failed to allocate memory for result\n");
        exit(1);
    }
    if (node->tag == CONST_VALUE) {
        sprintf(result, "$%d", *((int*)node->value));
    } else if (node->tag == NONETAG) {
        sprintf(result, "%s" ,"");
    } else if (node->tag == LABEL){
        sprintf(result, "%s", node->id);
    } else {
        sprintf(result, "-%d(%%rbp)", node->offset*4);
    }
    return result;
}

void generatePrint(FILE* file, char* valueToPrint) {
    fprintf(file, "    movl    %s, %%rdi\n", valueToPrint);
    fprintf(file, "    call    print\n");
    fprintf(file, "\n");
}

void generateLabel(FILE* file, char* firstValue) {
    fprintf(file, ".%s:\n", firstValue);
}

void generateEquals(FILE* file, char* firstValue, char* secondValue, char* thirdValue) {
    
    fprintf(file, "    movl    %s, %%rax\n", secondValue);
    fprintf(file, "    movl    %s, %%rbx\n", thirdValue);
    fprintf(file, "    cmp     %%rax, %%rbx\n");
    fprintf(file, "    movl    $0, %%rbx\n");
    fprintf(file, "    movl    $1, %%rax\n");
    fprintf(file, "    cmove   %%rax %%rbx\n");
    fprintf(file, "    movl    %%rbx, %s\n", firstValue);
    fprintf(file, "\n");
    
}

void generateGreaterThan(FILE* file, char* firstValue, char* secondValue, char* thirdValue) {
    
    fprintf(file, "    movl    %s, %%rax\n", secondValue);
    fprintf(file, "    movl    %s, %%rbx\n", thirdValue);
    fprintf(file, "    cmp     %%rax, %%rbx\n");
    fprintf(file, "    movl    $0, %%rbx\n");
    fprintf(file, "    movl    $1, %%rax\n");
    fprintf(file, "    cmovg   %%rax %%rbx\n");
    fprintf(file, "    movl    %%rbx, %s\n", firstValue);
    fprintf(file, "\n");
    
}

void generateLessThan(FILE* file, char* firstValue, char* secondValue, char* thirdValue) {
    
    fprintf(file, "    movl    %s, %%rax\n", secondValue);
    fprintf(file, "    movl    %s, %%rbx\n", thirdValue);
    fprintf(file, "    cmp     %%rax, %%rbx\n");
    fprintf(file, "    movl    $0, %%rbx\n");
    fprintf(file, "    movl    $1, %%rax\n");
    fprintf(file, "    cmovl   %%rax %%rbx\n");
    fprintf(file, "    movl    %%rbx, %s\n", firstValue);
    fprintf(file, "\n");
    
}

/*

void generateJumpByFalse(FILE* file, char* firstValue, char* secondValue) {

}

void generateJumpByTrue(FILE* file, char* firstValue, char* secondValue) {

}

void generateGreaterThan(FILE* file, char* firstValue, char* secondValue, char* thirdValue) {

}

void generateLesserThan(FILE* file, char* firstValue, char* secondValue, char* thirdValue) {

}

void generateMod(FILE* file, char* firstValue, char* secondValue, char* thirdValue) {

}

void generateNegative(FILE* file, char* firstValue, char* secondValue) {

}

void generateNot(FILE* file, char* firstValue, char* secondValue) {

}
*/