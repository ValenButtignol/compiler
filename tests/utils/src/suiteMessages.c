#include "../include/suiteMessages.h"

void printTestSuccessMessage(char* testType, char* inputFileName) {
    printf("\n");
    printf("\033[1;32m"); // Set text color to green
    printf("******************************************************************\n");
    printf("************ %s Tests completed successfully for %s ************\n", testType, inputFileName);
    printf("******************************************************************\n");
    printf("\033[0m"); // Reset text color to default
    printf("\n");
}

void printTestFailedMessage(char* testType, char* inputFileName) {
    printf("\n");
    printf("\033[31m"); // Set text color to green
    printf("******************************************************************\n");
    printf("************ %s Tests failed for %s ************\n", testType, inputFileName);
    printf("******************************************************************\n");
    printf("\033[0m"); // Reset text color to default
    printf("\n");
}

void printNoTestSuiteMessage(char* inputFileName) {
    printf("\n");
    printf("\033[33m"); // Set text color to yellow
    printf("******************************************************************\n");
    printf("************ No tests implemented for %s ************\n", inputFileName);
    printf("******************************************************************\n");
    printf("\033[0m"); // Reset text color to default
    printf("\n");
}