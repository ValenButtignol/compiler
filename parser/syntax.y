%{

#include <stdlib.h>
#include <stdio.h>

%}

%token TId
%token TType
%token TConst
%token TSemiColon
%token TReturn
%token TAssign
%token TPlus
%token TMinus
%token TMultiply
%token TDivide
%token TOpenParenthesis
%token TCloseParenthesis
%token TInteger
%token TBool

%type PROGRAM
%type EXPRESSION

%left '+' TPlus
%left '-' TMinus
%left '*' TMultiply
%left '/' TDivide

%%

PROGRAM: DECLARATION_LIST STATEMENT_LIST { printf("No errors.\n"); }
    ;

DECLARATION_LIST: ENTITY ASSIGNMENT DECLARATION_LIST
    | /* LAMBDA */
    ;

ENTITY: TConst TType
    | TType    
    ;

STATEMENT_LIST: ASSIGNMENT STATEMENT_LIST
    | RETURN STATEMENT_LIST
    | ASSIGNMENT
    | RETURN
    ;

ASSIGNMENT: TId TAssign EXPRESSION TSemiColon
    ;

RETURN: TReturn EXPRESSION TSemiColon
    ;

EXPRESSION: EXPRESSION TPlus EXPRESSION
    | EXPRESSION TMinus EXPRESSION
    | EXPRESSION TMultiply EXPRESSION
    | EXPRESSION TDivide EXPRESSION
    | TOpenParenthesis EXPRESSION TCloseParenthesis
    | TInteger
    | TBool
    | TId
    ;
%%