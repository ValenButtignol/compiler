#include "../include/testingNodeInfoList.h"

// Function to initialize a new empty linked list
TestingNodeInfoList* newTestingNodeInfoList() {
    TestingNodeInfoList* list = (TestingNodeInfoList*)malloc(sizeof(TestingNodeInfoList));
    if (list != NULL) {
        list->head = NULL;
    }
    return list;
}

// Function to add a NodeInfo to the linked list
void addNodeToTestingList(TestingNodeInfoList* list, NodeInfo* data) {
    TestingNode* newNode = (TestingNode*)malloc(sizeof(TestingNode));
    if (newNode != NULL) {
        newNode->data = data;
        newNode->next = list->head;
        list->head = newNode;
    } else {
        fprintf(stderr, "Memory allocation failed for new node.\n");
    }
}


// Function to free the entire linked list
void freeTestingNodeInfoList(TestingNodeInfoList* list) {
    TestingNode* current = list->head;
    while (current != NULL) {
        TestingNode* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}
