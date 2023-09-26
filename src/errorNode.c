#include "../include/errorNode.h"

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