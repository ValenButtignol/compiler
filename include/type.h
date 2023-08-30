#include <stdio.h>

typedef struct{
	int integer;
	int boolean;
	char* symbol;
}Type;

Type newInteger(int integer);
Type newBoolean(int boolean);
Type newSymbol(char* symbol);
