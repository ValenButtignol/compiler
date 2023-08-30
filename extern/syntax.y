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

PROGRAM: DECLARATION_LIST STATEMENT_LIST { 
    printf("\n---------------------\nArbol Sintactico\n%s\n--------------------\n\n", 
    astToString(newAst(newSymbol("program"), $1, $2))); 
    }
    ;

DECLARATION_LIST: ENTITY ASSIGNMENT DECLARATION_LIST {
    $$ = newAst(newSymbol("declaration"), 
                newAst(newSymbol("definition"),$1, $2), 
                $3));}
    | /* LAMBDA */  // PODRÍA SER { $$ = NULL }
    ;

ENTITY: TConst TType
    | TType    
    ;

STATEMENT_LIST: ASSIGNMENT STATEMENT_LIST
    | RETURN STATEMENT_LIST
    | ASSIGNMENT
    | RETURN
    ;

ASSIGNMENT: TId TAssign EXPRESSION TSemiColon { 
        $$ = newAst(newSymbol($2), 
            newLeaf(newSymbol($1)), 
            newAst(newSymbol($3), NULL, newLeaf(newSymbol($4)))
        );
    }
    ;

RETURN: TReturn EXPRESSION TSemiColon { $$ = newAst(newSymbol($1), $2, NULL); }
    ;

EXPRESSION: EXPRESSION TPlus EXPRESSION { $$ = newAst(newSymbol($2),$1, $3); }
    | EXPRESSION TMinus EXPRESSION  { $$ = newAst(newSymbol($2),$1, $3); }
    | EXPRESSION TMultiply EXPRESSION { $$ = newAst(newSymbol($2),$1, $3); }
    | EXPRESSION TDivide EXPRESSION { $$ = newAst(newSymbol($2), $1, $3); }
    | TOpenParenthesis EXPRESSION TCloseParenthesis { $$ = newLeaf(newSymbol($2)); }
    | TInteger  { $$ = newLeaf(newSymbol($1)); }
    | TBool { $$ = newLeaf(newSymbol($1)); }
    | TId { $$ = newLeaf(newSymbol($1)); }
    ;
%%
