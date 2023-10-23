%{

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../include/dataStructures/ast.h"
#include "../include/dataStructures/nodeInfo.h"
#include "syntax.tab.h"

%}

%option noyywrap
%option yylineno

letter [a-zA-Z]      
digit [0-9]


%%

"boolean"|"int" {
        yylval.type = malloc(sizeof(enum TType*));
        *yylval.type = getTypeFromText(yytext);
        // printf("TType: %s\n", typeToString(*yylval.type));
        return TType;
    }

"const" {
        yylval.tag = malloc(sizeof(enum TType*));
        *yylval.tag = getTagFromText(yytext);
        // printf("TTag: %s\n", tagToString(*yylval.type));
        return TConst;
    }

";" {  
        // printf("TSemiColon: %s\n",yytext);
        return TSemiColon;
    }

"return" {
        yylval.tag = malloc(sizeof(enum TTag*));
        *yylval.tag = getTagFromText(yytext);
        // printf("TTag: %s\n", tagToString(*yylval.tag));
        return TReturn;
    }

"=" {  
        yylval.operator = malloc(sizeof(enum TOperator*));
        *yylval.operator = getOperatorFromText(yytext);
        // printf("\n\noperator: %d %s\n", *yylval.operator, yytext);
        // printf("TOperator: %s\n", operatorToString(*yylval.type));
        return TAssign;
    }

"+" {  
        yylval.operator = malloc(sizeof(enum TOperator*));
        *yylval.operator = getOperatorFromText(yytext);
        // printf("TOperator: %s\n", operatorToString(*yylval.type));
        return TPlus;
    }

"-" {  
        yylval.operator = malloc(sizeof(enum TOperator*));
        *yylval.operator = getOperatorFromText(yytext);
        // printf("TOperator: %s\n", operatorToString(*yylval.type));
        return TMinus;
    }    

"*" {  
        yylval.operator = malloc(sizeof(enum TOperator*));
        *yylval.operator = getOperatorFromText(yytext);
        // printf("TOperator: %s\n", operatorToString(*yylval.type));
        return TMultiply;
    }

"/" {  
        yylval.operator = malloc(sizeof(enum TOperator*));
        *yylval.operator = getOperatorFromText(yytext);
        // printf("TOperator: %s\n", operatorToString(*yylval.type));
        return TDivide;
    }

"(" {  
        // printf("TOpenParenthesis: %s\n",yytext);
        return TOpenParenthesis;
    }

")" {  
        // printf("TCloseParenthesis: %s\n",yytext);
        return TCloseParenthesis;
    }

{digit}+ { 
        void* number = malloc(sizeof(int));
        *((int*)number) = atoi(yytext);
        yylval.value = number; // Assuming yylval has a field named 'value'
        return TInteger;
    }

"false"|"true" {
        void* boolean = malloc(sizeof(TBool));
        *((int*) boolean) = getBooleanFromText(yytext);
        yylval.value = boolean;
        return TBool;
    }

{letter}({letter}|{digit})* { 
        yylval.string=(char *) malloc(sizeof(yytext)*yyleng);
        strcpy(yylval.string,yytext);
        return TId;
    }

.|\n ; /* ignore all the rest */

%%

void yyerror(){
    printf("\033[1;31m");
	printf("%s%d\n","-> Syntax ERROR at: ",yylineno);
    printf("\033[0m"); // Reset text color to default
    exit(1);
}