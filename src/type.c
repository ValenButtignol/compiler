#include "../include/type.h"

Type newInteger(int integer){
    Type *t = malloc(sizeof(Type));
    t->integer = integer;
    return *t;
}

Type newBoolean(int boolean){
    Type *t = malloc(sizeof(Type));
    t->boolean = boolean;
    return *t;
}

Type newSymbol(char* symbol){
    Type *t = malloc(sizeof(Type));
    t->symbol = symbol;
    return *t;
}

char* typeToString(Type type){
    char *string = "";
    if(type.boolean != NULL){
        strcat(string, type.boolean ? "true" : "false");
    }
    if(type.integer != NULL){
        char str[] = ""; 
        sprintf(str, "%d", type.integer);
        strcat(string, str);
    }
    if(type.symbol != NULL){
        printf("\n\n%s\n\n", type.symbol);
        strcat(string, type.symbol);
    }
    return string;
}