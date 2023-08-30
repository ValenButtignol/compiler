#ifndef	TYPE_H
#define TYPE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
	int integer;
	int boolean;
	char* symbol;
}Type;

// 
// Type -> struct {TIPO = ENUM (BOOL, CHAR, INT), VALUE = (PUEDE SER NULL), NOMBRE = (PUEDE TENER O NO), TAG = ENUM(SYMBOL, VARIABLE, CONSTANT)}

Type newInteger(int integer);

Type newBoolean(int boolean);

Type newSymbol(char* symbol);

#endif