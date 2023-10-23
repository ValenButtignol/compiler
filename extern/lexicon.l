%{

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "syntax.tab.h"
#include "../include/utils/enums.h"

%}

%option noyywrap
%option yylineno

letter [a-zA-Z]      
digit [0-9]

%%

"Program" {
        printf("%s\n",yytext);

        return TProgram;
    }

"{" {
        printf("%s\n",yytext);
        return TOpenCurlyBracket;
    }

"}" {
        printf("%s\n",yytext);
        return TCloseCurlyBracket;
    }

"(" {
        printf("%s\n",yytext);
        return TOpenParenthesis;
    }

")" {
        printf("%s\n",yytext);
        return TCloseParenthesis;
    }

";" {
        printf("%s\n",yytext);
        return TSemiColon;
    }

"," {
        printf("%s\n",yytext);
        return TComma;
    }

"integer"|"bool" {
        printf("%s\n",yytext);
        yylval.type = malloc(sizeof(enum TType*));
        *yylval.type = getTypeFromText(yytext);
        return TType;
    }

"void" {
        printf("%s\n",yytext);
        yylval.type = malloc(sizeof(enum TType*));
        *yylval.type = getTypeFromText(yytext);
        return TVoid;
    }

"if" {
        printf("%s\n",yytext);
        return TIf;
    }

"then" {
        printf("%s\n",yytext);
        return TThen;
    }

"else" {
        printf("%s\n",yytext);
        return TElse;
    }

"while" {
        printf("%s\n",yytext);
        return TWhile;
    }

"return" {
        printf("%s\n",yytext);
        return TReturn;
    }

"extern" {
        printf("%s\n",yytext);
        return TExtern;
    }

"=" {
        printf("%s\n",yytext);
        return TAssign;
    }

"!" {
        printf("%s\n",yytext);
        return TNot;
    }

"+" {
        printf("%s\n",yytext);
        return TAdd;
    }

"-" {
        printf("%s\n",yytext);
        return TSub;
    }

"*" {
        printf("%s\n",yytext);
        return TMul;
    }

"/" {
        printf("%s\n",yytext);
        return TDiv;
    }

"%" {
        printf("%s\n",yytext);
        return TMod;
    }

"<" {
        printf("%s\n",yytext);
        return TLessThan;
    }   

">" {
        printf("%s\n",yytext);
        return TGreaterThan;
    }

"==" {
        printf("%s\n",yytext);
        return TEquals;
    }

"&&" {
        printf("%s\n",yytext);
        return TAnd;
    }

"||" {
        printf("%s\n",yytext);
        return TOr;
    }

"true"|"false" {
        printf("%s\n",yytext);
        void* boolean = malloc(sizeof(enum TBoolean));
        *((int*) boolean) = getBooleanFromText(yytext);
        yylval.boolean = boolean;
        return TBooleanLiteral;
    }

{digit}+ {
        printf("%s\n",yytext);
        int number = atoi(yytext);
        yylval.integer = number;
        return TIntegerLiteral;
    }

{letter}({letter}|{digit}|"_")* {
        printf("%s\n",yytext);
        yylval.string=(char *) malloc(sizeof(yytext)*yyleng);
        strcpy(yylval.string,yytext);
        return TId;
    }

"//"(.)*\n ;

.|\n ;



%%

void yyerror(){
    printf("\033[1;31m");
	printf("%s%d\n","-> Syntax ERROR at: ",yylineno);
    printf("\033[0m"); // Reset text color to default
    exit(1);
}