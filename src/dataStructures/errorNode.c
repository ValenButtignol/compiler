#include "../../include/dataStructures/errorNode.h"

ErrorNode* createErrorNode(const char* data) {
    ErrorNode* newNode = (ErrorNode*)malloc(sizeof(ErrorNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = strdup(data);  // Dynamically allocate memory for the string
    newNode->next = NULL;
    return newNode;
}

void insertErrorNode(ErrorNode** head, const char* data) {
    ErrorNode* newNode = createErrorNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        ErrorNode* tail = *head;
        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = newNode;
    }
}

void printErrors(ErrorNode* head) {
    ErrorNode* current = head;
    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }
}

void freeErrorsList(ErrorNode* head) {
    ErrorNode* current = head;
    while (current != NULL) {
        ErrorNode* temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
}

int equalsErrorNode(ErrorNode* error1, ErrorNode* error2) {
    if (error1 == NULL && error2 == NULL) {
        return 1;
    } else if (error1 == NULL || error2 == NULL) {
        return 0;
    } else {
        return strcmp(error1->data, error2->data) == 0;
    }
}

void addOperationError(ErrorNode** errors, int lineNumber, enum TTag tag){
    int errorStrLength = snprintf(NULL, 0, "\033[1;36mLine: %d \033[1;31mError:\033[0m Type mismatch in \'\033[1;36m %s \033[0m \' \n", lineNumber, operatorToString(tag));
    char* errorStr = malloc(errorStrLength + 1);
    sprintf(errorStr, "\033[1;36mLine: %d \033[1;31mError:\033[0m Type mismatch in \'\033[1;36m %s \033[0m\' \n", lineNumber, operatorToString(tag));
    insertErrorNode(errors, errorStr);
}

void addMethodCallError(ErrorNode** errors, int lineNumber, char* message, char* methodName){
    int errorStrLength = snprintf(NULL, 0, "\033[1;36mLine: %d \033[1;31mError:\033[0m %s in function \'\033[1;36m %s \033[0m\' \n", lineNumber, message, methodName);
    char* errorStr = malloc(errorStrLength + 1);
    sprintf(errorStr, "\033[1;36mLine: %d \033[1;31mError:\033[0m %s in function \'\033[1;36m %s \033[0m\' \n", lineNumber, message, methodName);
    insertErrorNode(errors, errorStr);
}

void addDivByZeroError(ErrorNode** errors, int lineNumber, enum TTag tag){
    int errorStrLength = snprintf(NULL, 0, "\033[1;36mLine: %d \033[1;31mError:\033[0m Division by zero in \'\033[1;36m %s \033[0m\' \n", lineNumber, operatorToString(tag));
    char* errorStr = malloc(errorStrLength + 1);
    sprintf(errorStr, "\033[1;36mLine: %d \033[1;31mError:\033[0m Division by zero in \'\033[1;36m %s \033[0m\' \n", lineNumber, operatorToString(tag));
    insertErrorNode(errors, errorStr);
}
