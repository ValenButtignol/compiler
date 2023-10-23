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
        case SUM:
            generateSum(file, firstValue, secondValue, thirdValue);
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
        case MOV:
            generateMov(file, firstValue, secondValue);
            break;
        case RET:
            generateRet(file, firstValue);
            break;
        default:
            break;
    }

    free(firstValue);
    free(secondValue);
    free(thirdValue);
}

void generateSum(FILE* file, char* firstValue, char* secondValue, char* thirdValue) {
    fprintf(file, "    movl    %s, %%eax\n", secondValue);
    fprintf(file, "    addl    %s, %%eax\n", thirdValue);
    fprintf(file, "    movl    %%eax, %s\n", firstValue);
    fprintf(file, "\n");
}


void generateSub(FILE* file, char* firstValue, char* secondValue, char* thirdValue) {
    fprintf(file, "    movl    %s, %%eax\n", secondValue);
    fprintf(file, "    subl    %s, %%eax\n", thirdValue);
    fprintf(file, "    movl    %%eax, %s\n", firstValue);
    fprintf(file, "\n");
}

void generateMul(FILE* file, char* firstValue, char* secondValue, char* thirdValue) {
    fprintf(file, "    movl    %s, %%eax\n", secondValue);
    fprintf(file, "    movl    %s, %%ebx\n", thirdValue);
    fprintf(file, "    imul    %%eax, %%ebx\n");
    fprintf(file, "    movl    %%ebx, %s\n", firstValue);
    fprintf(file, "\n");
}

void generateDiv(FILE* file, char* firstValue, char* secondValue, char* thirdValue) {
    fprintf(file, "    movl    %s, %%eax\n", secondValue);  // Dividend
    fprintf(file, "    movl    %s, %%ebx\n", thirdValue);   // Divisor
    fprintf(file, "    xor     %%edx, %%edx\n");            // Clear EDX to prepare for the result
    fprintf(file, "    div     %%ebx\n");                   // Divide EAX by EBX, quotient in EAX, remainder in EDX
    fprintf(file, "    movl    %%eax, %s\n", firstValue);   // Store value
    fprintf(file, "\n");
}

void generateAnd(FILE* file, char* firstValue, char* secondValue, char* thirdValue) {
    fprintf(file, "    movl    %s, %%eax\n", secondValue);
    fprintf(file, "    movl    %s, %%ebx\n", thirdValue);
    fprintf(file, "    andl    %%ebx, %%eax\n");
    fprintf(file, "    movl    %%eax, %s\n", firstValue);
    fprintf(file, "\n");
}

void generateOr(FILE* file, char* firstValue, char* secondValue, char* thirdValue) {
    fprintf(file, "    movl    %s, %%eax\n", secondValue);
    fprintf(file, "    movl    %s, %%ebx\n", thirdValue);
    fprintf(file, "    orl     %%ebx, %%eax\n");
    fprintf(file, "    movl    %%eax, %s\n", firstValue);
    fprintf(file, "\n");
}

void generateMov(FILE* file, char* firstValue, char* secondValue) {
    fprintf(file, "    movl    %s, %%eax\n", secondValue);
    fprintf(file, "    movl    %%eax, %s\n", firstValue);
    fprintf(file, "\n");
}

void generateRet(FILE* file, char* firstValue) {
    generatePrint(file, firstValue);

    fprintf(file, "    movl    %s, %%eax\n", firstValue);
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
    } else {
        sprintf(result, "-%d(%%rbp)", node->offset*4);
    }
    return result;
}

void generatePrint(FILE* file, char* valueToPrint) {
    fprintf(file, "    movl    %s, %%edi\n", valueToPrint);
    fprintf(file, "    call    print\n");
    fprintf(file, "\n");
}
