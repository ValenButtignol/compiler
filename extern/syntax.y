%{

#include <stdlib.h>
#include <stdio.h>
#include "../include/ast.h"
#include "../include/type.h"
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

PROGRAM: DECLARATION_LIST STATEMENT_LIST { printf("\n---------------------\nArbol Sintactico\n%s\n--------------------\n\n", astToString); }
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

ASSIGNMENT: TId TAssign EXPRESSION TSemiColon {$$ = newAst(newSymbol($2), 
                                                           newLeaf(newSymbol($1)),
														   newAst(newSymbol($3), NULL, newLeaf(newSymbol($4)))
                                              );
											  }
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
