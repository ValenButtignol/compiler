#include "../include/suiteMessages.h"

void printTestSuccessMessage(char* testType, char* inputFileName) {
    printf("\n");
    printf("\033[1;32m"); // Set text color to green
    printf("******************************************************************\n");
    printf("************\033[1m\033[32m %s\033[1;32m Tests completed successfully for %s ************\n", testType, inputFileName);
    printf("******************************************************************\n");
    printf("\033[0m"); // Reset text color to default
    printf("\n");
}

void printTestFailedMessage(char* testType, char* inputFileName) {
    printf("\n");
    printf("\033[31m"); // Set text color to red
    printf("**********************************************************************\n");
    printf("************\033[1m\033[31m %s\033[31m Tests failed in %s ************\n", testType, inputFileName);
    printf("**********************************************************************\n");
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

void printIncorrectTypeTestMessage(char* testType) {
    printf("\n");
    printf("\033[31m"); // Set text color to red
    printf("************ Test type '%s' not recognized ************\n", testType);
    printf("\033[0m"); // Reset text color to default
    printf("\n");
}
