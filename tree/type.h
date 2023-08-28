#include <stdio.h>

typedef struct{
	int integer;
	int boolean;
	char* token;
}Type;

Type newInteger(int integer);
Type newBoolean(int boolean);
Type newToken(char* token);
