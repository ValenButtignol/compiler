#ifndef UTILS_SUITE_MESSAGES_H
#define UTILS_SUITE_MESSAGES_H

#include <stdio.h>
#include <stdlib.h>

void printTestSuccessMessage(char* testType, char* inputFileName);

void printTestFailedMessage(char* testType, char* inputFileName);

void printNoTestSuiteMessage(char* inputFileName);

#endif