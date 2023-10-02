#include "../include/assemblyCodeGenerator.h"


void generateAssembly(ThreeAddressCodeList* list) {
    FILE* file = fopen("assembly.s", "w");
    if (file == NULL) {
        // Error handling code
        perror("Error opening the file");
        exit(1); // Return a non-zero value to indicate failure
    }

    generateMain(file, list);
    ThreeAddressCodeNode* current = list->head->next;

    while (current != NULL) {
        instructionFactory(file, current);
        current = current->next;
    }

    generateFooter(file);

    fclose(file);
}


void generateMain(FILE* file, ThreeAddressCodeList* list) {     // Probably this would be converted into generatePrologue
    fprintf(file, "    .text\n");
    fprintf(file, ".globl main\n");
    fprintf(file, "main:\n");
}

void generateFooter(FILE* file) {                               // Probably this would be converted into generateEpilogue
    fprintf(file, "    leave\n");
    fprintf(file, "    ret\n");
}


void instructionFactory(FILE* file, ThreeAddressCodeNode* current) {

    char* firstValue = generateValue(current->first);
    char* secondValue = generateValue(current->second);
    char* thirdValue = generateValue(current->third);
    
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
    fprintf(file, "    mov %s, %s\n", firstValue, secondValue);
    fprintf(file, "    add %s, %s\n", firstValue, thirdValue);
    fprintf(file, "\n");

}


void generateSub(FILE* file, char* firstValue, char* secondValue, char* thirdValue) {
    fprintf(file, "    mov %s, %s\n", firstValue, secondValue);
    fprintf(file, "    sub %s, %s\n", firstValue, thirdValue);
    fprintf(file, "\n");

}

void generateMul(FILE* file, char* firstValue, char* secondValue, char* thirdValue) {
    fprintf(file, "    mov eax, %s\n", secondValue);
    fprintf(file, "    mov ebx, %s\n", thirdValue);
    fprintf(file, "    imul eax, ebx\n");
    fprintf(file, "    mov %s, eax\n", firstValue);
    fprintf(file, "\n");

}

void generateDiv(FILE* file, char* firstValue, char* secondValue, char* thirdValue) {
    fprintf(file, "    mov eax, %s\n", secondValue);        // Dividend
    fprintf(file, "    mov ebx, %s\n", thirdValue);         // Divisor
    fprintf(file, "    xor edx, edx\n");                    // Clear EDX to prepare for the result
    fprintf(file, "    div ebx\n");                         // Divide EAX by EBX, quotient in EAX, remainder in EDX
    fprintf(file, "    mov %s, eax\n", firstValue);         // Store value
    fprintf(file, "\n");

}

void generateAnd(FILE* file, char* firstValue, char* secondValue, char* thirdValue) {
    fprintf(file, "    mov %s, %s\n", firstValue, secondValue);
    fprintf(file, "    and %s, %s\n", firstValue, thirdValue);
    fprintf(file, "\n");
}

void generateOr(FILE* file, char* firstValue, char* secondValue, char* thirdValue) {
    fprintf(file, "    mov %s, %s\n", firstValue, secondValue);
    fprintf(file, "    or %s, %s\n", firstValue, thirdValue);
    fprintf(file, "\n");

}

void generateMov(FILE* file, char* firstValue, char* secondValue) {
    fprintf(file, "    mov %s, %s\n", firstValue, secondValue);
    fprintf(file, "\n");

}

void generateRet(FILE* file, char* firstValue) {
    fprintf(file, "    mov eax, %s\n", firstValue);
    fprintf(file, "    leave\n");       // TODO: This is not correct, we need to generate the epilogue
    fprintf(file, "    ret\n");
    fprintf(file, "\n");

}

char* generateValue(NodeInfo* node) {
    printf("ID: %s\n", node->id);
    printf("VALUE: %d\n", node->value);
    printf("TAG: %d\n", node->tag);
    printf("OFFSET: %d\n", node->offset);
    printf("TYPE: %d\n\n", node->type);
    char* result;
    result = (char*)malloc(20);
    if (result == NULL) {
        printf("Failed to allocate memory for result\n");
        exit(1);
    }
    if (node->tag == CONST_VALUE) {
        sprintf(result, "$%d", node->value);
    } else if (node->tag == NONETAG) {
        sprintf(result, "");
    } {
        sprintf(result, "%d(%%ebp)", node->offset*4);
    }

    return result;
}

