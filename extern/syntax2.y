%{

#include <stdlib.h>
#include <stdio.h>
#include "../include/ast.h"
#include "../include/nodeInfo.h"
#include "../include/enums.h"
#include "../include/symbolTable.h"
#include "../include/threeAddressCodeList.h"

extern int yylineno;
extern int yytypeCorrect;

SymbolTable* symbolTable;
TAst* globalAst;
int offset;
%}

%initial-action {
    offset = 0;
    initializeSymbolTable(&symbolTable);
}

%union {
    TAst* ast;
    enum TType* type;
    char* string;
    int integer;
    enum TBoolean* boolean;
    enum TTag* tag;
    enum TOperator* operator;
}

%token TProgram
%token TOpenCurlyBracket
%token TCloseCurlyBracket
%token TOpenParenthesis
%token TCloseParenthesis
%token TSemiColon
%token TComma
%token TType
%token TVoid
%token TIf
%token TThen
%token TElse
%token TWhile
%token TReturn
%token TExtern
%token TAssign
%token TNot
%token TAdd
%token TSub
%token TMul
%token TDiv
%token TMod
%token TLessThan
%token TGreaterThan
%token TEquals
%token TAnd
%token TOr
%token TBooleanLiteral
%token TIntegerLiteral
%token TId


%left TAnd TOr
%nonassoc TEquals TGreaterThan TLessThan
%left TAdd TSub
%left TMul TDiv TMod
%left TNot 
%left TNegative

%%

PROGRAM: TProgram TOpenCurlyBracket VAR_DECL_BLOCK METHOD_DECL_BLOCK TCloseCurlyBracket {

        }
    | TProgram TOpenCurlyBracket VAR_DECL_BLOCK TCloseCurlyBracket {

        }
    | TProgram TOpenCurlyBracket METHOD_DECL_BLOCK TCloseCurlyBracket {

        }
    ;

VAR_DECL_BLOCK: VAR_DECL_BLOCK VAR_DECL {

        }
    | VAR_DECL {

        }
    ;

VAR_DECL: TType TId TAssign EXPR TSemiColon {

        }
    ;

METHOD_DECL_BLOCK: METHOD_DECL_BLOCK TYPE_METHOD_DECL {

        }
    | TYPE_METHOD_DECL {

        }
    ;

TYPE_METHOD_DECL: TType METHOD_DECL {

        }
    | TVoid METHOD_DECL {

        }
    ;  

METHOD_DECL: TId TOpenParenthesis PARAMS_DECL TCloseParenthesis METHOD_DECL_ENDING {

        }
    ;

METHOD_DECL_ENDING: BLOCK {

        }
    | TExtern TSemiColon {

        }
    ;


PARAMS_DECL: PARAMS_LIST_DECL {

        }
    | /* LAMBDA */ {

        }
    ;

PARAMS_LIST_DECL: TType TId TComma PARAMS_LIST_DECL {

        }
    | TType TId {

        }
    ;

BLOCK: TOpenCurlyBracket VAR_DECL_BLOCK STATEMENT_BLOCK TCloseCurlyBracket {

        }
    | TOpenCurlyBracket STATEMENT_BLOCK TCloseCurlyBracket {

        }
    ;

STATEMENT_BLOCK: STATEMENT STATEMENT_BLOCK {

        }
    | /* LAMBDA */ {

        }
    ;

STATEMENT: ASSIGNMENT TSemiColon {

        }
    | METHOD_CALL TSemiColon {

        }
    | IF_STATEMENT {

        }
    | WHILE_STATEMENT {

        }
    | RETURN_STATEMENT TSemiColon {

        }
    | BLOCK {

        }
    | TSemiColon {

        }
    ;

ASSIGNMENT: TId TAssign EXPR {

        }
    ;

METHOD_CALL: TId TOpenParenthesis PARAMS_CALL TCloseParenthesis {

        }
    ;

PARAMS_CALL: PARAMS_LIST_CALL {

        }
    | /* LAMBDA */ {

        }
    ;

PARAMS_LIST_CALL: EXPR TComma PARAMS_LIST_CALL {

        }
    | EXPR {

        }
    ;

IF_STATEMENT: TIf TOpenParenthesis EXPR TCloseParenthesis TThen BLOCK {

        }
    | TIf TOpenParenthesis EXPR TCloseParenthesis TThen BLOCK TElse BLOCK {

        }
    ;

WHILE_STATEMENT: TWhile TOpenParenthesis EXPR TCloseParenthesis BLOCK {

        }
    ;

RETURN_STATEMENT: TReturn EXPR TSemiColon {

        }
    | TReturn TSemiColon {

        }
    ;

EXPR: EXPR TAdd EXPR {

        }
    | EXPR TSub EXPR {

        }
    | EXPR TMul EXPR {

        }
    | EXPR TDiv EXPR {

        }
    | EXPR TMod EXPR {

        }
    | EXPR TGreaterThan EXPR {

        }
    | EXPR TLessThan EXPR {

        }
    | EXPR TEquals EXPR {

        }
    | EXPR TAnd EXPR {

        }
    | EXPR TOr EXPR {

        }
    | TSub EXPR %prec TNegative {

        }
    | TNot EXPR {

        }
    | METHOD_CALL {

        }
    | LITERAL {

        }
    | TId {

        }
    | TOpenParenthesis EXPR TCloseParenthesis {

        }
    ;

LITERAL: TIntegerLiteral {

        }
    | TBooleanLiteral {

        }
    ;

%%

int getOffset() {
    return offset;
}

TAst* getGlobalAst() {
    return globalAst;
}

SymbolTable* getSymbolTable() {
    return symbolTable;
}
