%{

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../include/ast.h"
#include "../include/nodeInfo.h"
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
        printf("TType: %s\n", typeToString(*yylval.type));
        return TType;
    }

"const" {
        yylval.tag = malloc(sizeof(enum TType*));
        *yylval.tag = getTagFromText(yytext);
        printf("TTag: %s\n", tagToString(*yylval.type));
        return TConst;
    }

";" {  
        printf("TSemiColon: %s\n",yytext);
        return TSemiColon;
    }

"return" {
        yylval.tag = malloc(sizeof(enum TTag*));
        *yylval.tag = getTagFromText(yytext);
        printf("TTag: %s\n", tagToString(*yylval.tag));
        return TReturn;
    }

"=" {  
        yylval.operator = malloc(sizeof(enum TOperator*));
        *yylval.operator = getOperatorFromText(yytext);
        printf("TOperator: %s\n", operatorToString(*yylval.type));
        return TAssign;
    }

"+" {  
        yylval.operator = malloc(sizeof(enum TOperator*));
        *yylval.operator = getOperatorFromText(yytext);
        printf("TOperator: %s\n", operatorToString(*yylval.type));
        return TPlus;
    }

"-" {  
        yylval.operator = malloc(sizeof(enum TOperator*));
        *yylval.operator = getOperatorFromText(yytext);
        printf("TOperator: %s\n", operatorToString(*yylval.type));
        return TMinus;
    }    

"*" {  
        yylval.operator = malloc(sizeof(enum TOperator*));
        *yylval.operator = getOperatorFromText(yytext);
        printf("TOperator: %s\n", operatorToString(*yylval.type));
        return TMultiply;
    }

"/" {  
        yylval.operator = malloc(sizeof(enum TOperator*));
        *yylval.operator = getOperatorFromText(yytext);
        printf("TOperator: %s\n", operatorToString(*yylval.type));
        return TDivide;
    }

"(" {  
        printf("TOpenParenthesis: %s\n",yytext);
        return TOpenParenthesis;
    }

")" {  
        printf("TCloseParenthesis: %s\n",yytext);
        return TCloseParenthesis;
    }

{digit}+ { 
        printf("TInteger: %d\n",atoi(yytext)); 
        return TInteger;
    }

"false"|"true" {
        yylval.boolean = malloc(sizeof(enum TBool*));
        *yylval.boolean = getBooleanFromText(yytext);
        printf("TBoolean: %s\n", boolToString(*yylval.type));
        return TBool;
    }

{letter}({letter}|{digit})* { 
        yylval.string=(char *) malloc(sizeof(yytext)*yyleng);
        strcpy(yylval.string,yytext);
        printf("ID : %s\n",yytext);
        return TId;
    }

.|\n ; /* ignore all the rest */

%%

void yyerror(){
	printf("%s%d\n","-> Syntax ERROR at: ",yylineno);
}

int main(int argc,char *argv[]){
	++argv,--argc;
	if (argc > 0)
		yyin = fopen(argv[0],"r");
	else
		yyin = stdin;

	yyparse();

}