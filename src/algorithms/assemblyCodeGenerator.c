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
    ThreeAddressCodeNode* current = list->head->next;

    while (current != NULL) {
        instructionFactory(file, current);
        current = current->next;
    }

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
        case MOD:
            generateMod(file, firstValue, secondValue, thirdValue);
            break;
        case JFALSE:
            generateJumpByFalse(file, firstValue, secondValue);
            break;
        case JUMP:
            generateJump(file, firstValue);
            break;
        case NEGATIVE:
            generateNegative(file, firstValue, secondValue);
            break;
        case NOT:
            generateNot(file, firstValue, secondValue);
            break; 
        case METHOD_DECL:
            generateMethodDecl(file, current->first);
            break;
        case METHOD_CALL:
            generateMethodCall(file, firstValue, secondValue);
            break;
        case LOAD:
            generateLoad(file, firstValue, secondValue);
            break;
        case END_LABEL:
            generateEndLabel(file);
            break;
        default:
            break;
    }

    free(firstValue);
    free(secondValue);
    free(thirdValue);
}

void generateAdd(FILE* file, char* firstValue, char* secondValue, char* thirdValue) {
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
    fprintf(file, "    xor     %%rdx, %%rdx\n");            // Clear rdx to prepare for the result
    fprintf(file, "    idiv    %%ebx\n");                   // Divide eax by ebx, quotient in eax, remainder in rdx
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
    fprintf(file, "\n");

}

char* generateValue(NodeInfo* node) {
    // printf("ID: %s\n", node->id);
    // printf("VALUE: %d\n", ((int *)node->value)!=NULL?*((int *)node->value):-9999);
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
    } else if (node->tag == LABEL) {
        sprintf(result, "%s", node->id);
    } else if (node->tag == LOAD) {
        sprintf(result, "%d", node->lineNumber);
    } else if(node->tag == METHOD_DECL){
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
    fprintf(file, "%s:\n", firstValue);
}

void generateEquals(FILE* file, char* firstValue, char* secondValue, char* thirdValue) {
    
    fprintf(file, "    movl    %s, %%eax\n", secondValue);
    fprintf(file, "    movl    %s, %%ebx\n", thirdValue);
    fprintf(file, "    cmpl    %%eax, %%ebx\n");
    fprintf(file, "    movl    $0, %%ebx\n");
    fprintf(file, "    movl    $1, %%eax\n");
    fprintf(file, "    cmove   %%eax, %%ebx\n");
    fprintf(file, "    movl    %%ebx, %s\n", firstValue);
    fprintf(file, "\n");
    
}

void generateGreaterThan(FILE* file, char* firstValue, char* secondValue, char* thirdValue) {
    
    fprintf(file, "    movl    %s, %%eax\n", secondValue);
    fprintf(file, "    movl    %s, %%ebx\n", thirdValue);
    fprintf(file, "    cmpl    %%ebx, %%eax\n");
    fprintf(file, "    movl    $0, %%ebx\n");
    fprintf(file, "    movl    $1, %%eax\n");
    fprintf(file, "    cmovg   %%eax, %%ebx\n");
    fprintf(file, "    movl    %%ebx, %s\n", firstValue);
    fprintf(file, "\n");
    
}

void generateLessThan(FILE* file, char* firstValue, char* secondValue, char* thirdValue) {
    
    fprintf(file, "    movl    %s, %%eax\n", secondValue);
    fprintf(file, "    movl    %s, %%ebx\n", thirdValue);
    fprintf(file, "    cmpl    %%ebx, %%eax\n");
    fprintf(file, "    movl    $0, %%ebx\n");
    fprintf(file, "    movl    $1, %%eax\n");
    fprintf(file, "    cmovl   %%eax, %%ebx\n");
    fprintf(file, "    movl    %%ebx, %s\n", firstValue);
    fprintf(file, "\n");
    
}

void generateMod(FILE* file, char* firstValue, char* secondValue, char* thirdValue) {
    fprintf(file, "    movl    %s, %%eax\n", secondValue);  // Dividend
    fprintf(file, "    movl    %s, %%ebx\n", thirdValue);   // Divisor
    fprintf(file, "    xor     %%rdx, %%rdx\n");            // Clear rdx to prepare for the result
    fprintf(file, "    idiv    %%ebx\n");                   // Divide eax by ebx, quotient in eax, remainder in rdx
    fprintf(file, "    movl    %%rdx, %s\n", firstValue);   // Store value
    fprintf(file, "\n");
}

void generateJumpByFalse(FILE* file, char* firstValue, char* secondValue) {
    fprintf(file, "    cmpl    $0, %s\n", firstValue);
    fprintf(file, "    je    %s\n", secondValue);
    fprintf(file, "\n");
}

void generateJump(FILE* file, char* firstValue) {
    fprintf(file, "    jmp    %s\n", firstValue);
    fprintf(file, "\n");
}

void generateNegative(FILE* file, char* firstValue, char* secondValue) {
    fprintf(file, "    movl    %s, %%eax\n", secondValue);
    fprintf(file, "    negl    %%eax\n");
    fprintf(file, "    movl    %%eax, %s\n", firstValue);
    fprintf(file, "\n");
}

void generateNot(FILE* file, char* firstValue, char* secondValue) {
    fprintf(file, "    movl    %s, %%eax\n", secondValue);
    fprintf(file, "    notl    %%eax\n");
    fprintf(file, "    movl    %%eax, %s\n", firstValue);
    fprintf(file, "\n");
}

void generateLoad(FILE* file, char* firstValue, char* secondValue) {
    fprintf(file, "    movl    %s, %s\n", firstValue, getParamRegister(secondValue));
    fprintf(file, "\n");
}

void generateMethodCall(FILE* file, char* firstValue, char* secondValue) {
    fprintf(file, "    call    %s, %s\n", firstValue, secondValue);
    fprintf(file, "\n");
}

void generateMethodDecl(FILE* file, NodeInfo* method) {
    fprintf(file, "%s:\n", method->id);
    fprintf(file, "    pushq   %%rbp\n");
    fprintf(file, "    movq    %%rsp, %%rbp\n");
    fprintf(file, "    subq    $64, %%rsp\n");
    fprintf(file, "\n");
    unloadRegisters(file, method);
}

void unloadRegisters(FILE* file, NodeInfo* method) {
    NodeInfo* current = method->nextParams;
    char* registerString = (char*)malloc(2);
    int registerNumber = 1;
    while (current != NULL) {
        sprintf(registerString, "%d", registerNumber);
        fprintf(file, "    movl    %s, -%d(%%rbp)\n", getParamRegister(registerString), current->offset*4);
        current = current->nextParams;
        registerNumber++;
    }
    
}

void generateEndLabel(FILE* file) {

    fprintf(file, "movl -8(%%rbp), %%edi\n    call print\n");
    fprintf(file, "    leave\n");
    fprintf(file, "    ret\n");
}