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
        return TProgram;
    }

"{" {
        return TOpenCurlyBracket;
    }

"}" {
        return TCloseCurlyBracket;
    }

"(" {
        return TOpenParenthesis;
    }

")" {
        return TCloseParenthesis;
    }

";" {
        return TSemiColon;
    }

"," {
        return TComma;
    }

"integer"|"bool" {
        yylval.type = malloc(sizeof(enum TType*));
        *yylval.type = getTypeFromText(yytext);
        return TType;
    }

"void" {
        yylval.type = malloc(sizeof(enum TType*));
        *yylval.type = getTypeFromText(yytext);
        return TVoid;
    }

"if" {
        return TIf;
    }

"then" {
        return TThen;
    }

"else" {
        return TElse;
    }

"while" {
        return TWhile;
    }

"return" {
        return TReturn;
    }

"extern" {
        return TExtern;
    }

"=" {
        return TAssign;
    }

"!" {
        return TNot;
    }

"+" {
        return TAdd;
    }

"-" {
        return TSub;
    }

"*" {
        return TMul;
    }

"/" {
        return TDiv;
    }

"%" {
        return TMod;
    }

"<" {
        return TLessThan;
    }   

">" {
        return TGreaterThan;
    }

"==" {
        return TEquals;
    }

"&&" {
        return TAnd;
    }

"||" {
        return TOr;
    }

"true"|"false" {
        void* boolean = malloc(sizeof(enum TBoolean));
        *((int*) boolean) = getBooleanFromText(yytext);
        yylval.literal = boolean;
        return TBooleanLiteral;
    }

{digit}+ {
        void* num = malloc(sizeof(int));
        *((int*)num) = atoi(yytext);
        yylval.literal = num;
        return TIntegerLiteral;
    }

{letter}({letter}|{digit}|"_")* {
        yylval.string=(char *) malloc(sizeof(yytext)*yyleng);
        strcpy(yylval.string,yytext);
        return TId;
    }
"/\*"(.*|.*\n|\n)*"\*/"     ; /* ignore comments */
"//"(.)*\n ;

.|\n ;



%%

void yyerror(){
    printf("ERROR SINTACTICO %d\n", yylineno);
    exit(1);
}