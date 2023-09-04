%{

#include <stdlib.h>
#include <stdio.h>
#include "../include/ast.h"
#include "../include/nodeInfo.h"

#include "../include/symbolTable.h"

const SymbolTable* symbolTable = createSymbolTable();
%}


%union {
    TAst* ast;
    enum TType* type;
    char* string;
    int* integer;
    enum TBoolean* boolean;
    enum TTag* tag;
    enum TOperator* operator;
}

%token <string> TId
%token <type> TType
%token <tag> TConst
%token TSemiColon
%token <tag> TReturn
%token <operator> TAssign
%token <operator> TPlus
%token <operator>TMinus
%token <operator>TMultiply
%token <operator>TDivide
%token TOpenParenthesis
%token TCloseParenthesis
%token <integer>TInteger
%token <boolean>TBool

%type <ast>PROGRAM
%type <ast>EXPRESSION
%type <ast>DECLARATION_BLOCK
%type <ast>DECLARATION
%type <ast>STATEMENT_BLOCK
%type <ast>ASSIGNMENT
%type <ast>RETURN

%left '+' TPlus
%left '-' TMinus
%left '*' TMultiply
%left '/' TDivide

%%

PROGRAM: DECLARATION_BLOCK STATEMENT_BLOCK { 
            NodeInfo *p = newNodeInfo("Program", EMPTY, "Program", NONTERMINAL);
            printf("\n\n------------------------------------------\n\nAST\n%s\n--------------------------\n",
            astToString(newAst(p, $1, $2)));
            $$=newAst(p, $1, $2);
        }
    ;

DECLARATION_BLOCK: DECLARATION DECLARATION_BLOCK {
            NodeInfo *declarationInfo = newNodeInfo("declarationBlock", EMPTY, "declarationBlock", NONTERMINAL);
            $$ = newAst(declarationInfo,$1,$2);
        }
    | /* LAMBDA */ {
            NodeInfo *ni = newEmptyNodeInfo();
            $$ = newLeaf(ni);
        }
    ;

DECLARATION: TConst TType TId TAssign EXPRESSION TSemiColon {
            NodeInfo *varDecl = searchKey(symbolTable, $3);
            if (varDecl != NULL) {
                printf("Error: variable %s already declared\n", $3);
                exit(1);
            }

            NodeInfo *constantDecl = newNodeInfo("declaration", EMPTY, "=", NONTERMINAL);
            TAst *declaredID = newLeaf(newNodeInfo("constantDecl", *$2, $3, CONSTANT_DEC));
            $$ = newAst(constantDecl, declaredID, $5);
        }
    | TType TId TAssign EXPRESSION TSemiColon {
            NodeInfo *varDecl = searchKey(symbolTable, $2);
            if (varDecl != NULL) {
                printf("Error: variable %s already declared\n", $2);
                exit(1);
            }
            NodeInfo *varDecl = newNodeInfo("declaration", EMPTY, "=", NONTERMINAL);
            TAst *declaredID = newLeaf(newNodeInfo("variableDecl", *$1, $2, VARIABLE));
            addBlockToLevel(symbolTable, varDecl->value, varDecl->type, varDecl->id, varDecl->tag);
            $$ = newAst(varDecl, declaredID, $4);
        }
    ;


STATEMENT_BLOCK: ASSIGNMENT STATEMENT_BLOCK {
            NodeInfo *statement = newNodeInfo("statement", EMPTY, "assignStatement", NONTERMINAL);
            $$ = newAst(statement,$1, $2);
        }
    | RETURN STATEMENT_BLOCK {
            NodeInfo *statement = newNodeInfo("statement", EMPTY, "returnStatement", NONTERMINAL);
            $$ = newAst(statement,$1, $2);
        }
    | ASSIGNMENT { $$ = $1; }
    | RETURN { $$ = $1; }
    ;

ASSIGNMENT: TId TAssign EXPRESSION TSemiColon { 
            NodeInfo *tid = searchKey(symbolTable, $1);
            if (tid == NULL) {
                printf("Error: variable %s not declared\n", $1);
                exit(1);
            } 
            TAst *t = newLeaf(tid);
            NodeInfo *tassign = newNodeInfo($2, EMPTY, "=", OPERATOR);
            $$ = newAst(tassign, t, $3);

        }
    ;

RETURN: TReturn EXPRESSION TSemiColon { 
            NodeInfo *treturn = newNodeInfo($1, EMPTY, "return", RETURN);
            $$ = newAst(treturn, newEmptyAst(), $2);
        }
    ;

EXPRESSION: EXPRESSION TPlus EXPRESSION {
            NodeInfo *ni = newNodeInfo($2, EMPTY, "+", OPERATOR);
            TAst* ast = newAst(ni, $1, $3); 
            $$ = ast;
        }
    | EXPRESSION TMinus EXPRESSION  {
            NodeInfo *ni = newNodeInfo($2, EMPTY, "-", OPERATOR);
            $$ = newAst(ni, $1, $3);
        }
    | EXPRESSION TMultiply EXPRESSION {
            NodeInfo *ni = newNodeInfo($2, EMPTY, "*", OPERATOR);
            $$ = newAst(ni, $1, $3);
        }
    | EXPRESSION TDivide EXPRESSION {
            NodeInfo *ni = newNodeInfo($2, EMPTY, "/", OPERATOR);
            $$ = newAst(ni, $1, $3);
        }
    | TOpenParenthesis EXPRESSION TCloseParenthesis { $$ = $2; }
    | TInteger  { $$ = newLeaf(newNodeInfo($1, INTEGER, "INT", CONSTANT_EXPR)); }
    | TBool { $$ = newLeaf(newNodeInfo($1, BOOLEAN, "BOOL", CONSTANT_EXPR)); }
    | TId { 
            NodeInfo *tid = searchKey(symbolTable, $1);     // TODO
            if (tid == NULL) {
                printf("Error: variable %s not declared\n", $1);
                exit(1);
            }
            $$ = newLeaf(tid);
        }
    ;

%%
