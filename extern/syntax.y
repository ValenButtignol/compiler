%{

#include <stdlib.h>
#include <stdio.h>
#include "../include/ast.h"
#include "../include/nodeInfo.h"
#include "../include/enums.h"
#include "../include/symbolTable.h"
extern int yylineno;
SymbolTable* symbolTable = NULL;
%}

%initial-action {
    symbolTable = malloc(sizeof(SymbolTable));
    if (symbolTable == NULL) {
        fprintf(stderr, "Failed to allocate memory for symbolTable\n");
        exit(1);
    }
    symbolTable->head = NULL;
    symbolTable->size = 0;
       
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

%token <string> TId
%token <type> TType
%token <tag> TConst
%token TSemiColon
%token <tag> TReturn
%token <operator>TAssign
%token <operator>TPlus
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
%left '=' TAssign

%%

PROGRAM: DECLARATION_BLOCK STATEMENT_BLOCK { 
            NodeInfo *p = newNodeInfoWithoutValue(NONE, "Program", PROGRAM);
            printf("\n\n------------------------------------------\n\nAST\n\n--------------------------\n");
            TAst* ast =newAst(p, $1, $2);
           checkType(ast);
            // eval(ast);
        }
    ;

DECLARATION_BLOCK: DECLARATION DECLARATION_BLOCK {
            NodeInfo *declarationInfo = newNodeInfoWithoutValue(NONE, "declarationBlock", DECL_BLOCK);
            $$ = newAst(declarationInfo,$1,$2);
        }
    | /* LAMBDA */ {
            NodeInfo *ni = newEmptyNodeInfo();
            $$ = newLeaf(ni);
        }
    ;

DECLARATION: TConst TType TId TAssign EXPRESSION TSemiColon {
            NodeInfo *constantDecl = newNodeInfo($4, EMPTY, "=", DECL);

            NodeInfo* constId = searchKey(symbolTable, $3);
            if (constId != NULL) {
                printf("Error: const identifier %s already declared\n", $3);
                exit(1);
            }

            constId = newNodeInfo("constantDecl", *$2, $3, CONST_DECL);
            TAst *declaredID = newLeaf(constId);
            addNodeInfoToBlock(&(symbolTable->head), constId);

            $$ = newAst(constantDecl, declaredID, $5);
        }
    | TType TId TAssign EXPRESSION TSemiColon {
            NodeInfo *varDecl = newNodeInfo($3, EMPTY, "=", DECL);

            NodeInfo* varId = searchKey(symbolTable, $2);
            if (varId != NULL) {
                printf("Error: var identifier %s already declared\n", $2);
                exit(1);
            }

            varId = newNodeInfo("variableDecl", *$1, $2, VAR_DECL);
            addNodeInfoToBlock(&(symbolTable->head), varId);
            TAst *declaredID = newLeaf(varId);

            $$ = newAst(varDecl, declaredID, $4);
        }
    ;


STATEMENT_BLOCK: ASSIGNMENT STATEMENT_BLOCK {
            NodeInfo *statement = newNodeInfo("statement", EMPTY, "assignStatement", STMT_BLOCK);
            $$ = newAst(statement,$1, $2);
        }
    | RETURN STATEMENT_BLOCK {
            NodeInfo *statement = newNodeInfo("statement", EMPTY, "returnStatement", STMT_BLOCK);
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
            NodeInfo *tassign = newNodeInfo($2, EMPTY, "=", ASSIGNMENT_OP);
            $$ = newAst(tassign, t, $3);

        }
    ;

RETURN: TReturn EXPRESSION TSemiColon { 
            NodeInfo *treturn = newNodeInfo($1, EMPTY, "return", RETURN);
            $$ = newAst(treturn, newEmptyAst(), $2);
        }
    ;

EXPRESSION: EXPRESSION TPlus EXPRESSION {
            NodeInfo *ni = newNodeInfo($2, EMPTY, "+", EXPR_OP);
            TAst* ast = newAst(ni, $1, $3); 
            $$ = ast;
        }
    | EXPRESSION TMinus EXPRESSION  {
            NodeInfo *ni = newNodeInfo($2, EMPTY, "-", EXPR_OP);
            $$ = newAst(ni, $1, $3);
        }
    | EXPRESSION TMultiply EXPRESSION {
            NodeInfo *ni = newNodeInfo($2, EMPTY, "*", EXPR_OP);
            $$ = newAst(ni, $1, $3);
        }
    | EXPRESSION TDivide EXPRESSION {
            NodeInfo *ni = newNodeInfo($2, EMPTY, "/", EXPR_OP);
            $$ = newAst(ni, $1, $3);
        }
    | TOpenParenthesis EXPRESSION TCloseParenthesis { $$ = $2; }
    | TInteger  { 
            char* num = malloc(sizeof(char*));
            sprintf(num, "%d", $1);
            $$ = newLeaf(newNodeInfo($1, INTEGER, num, CONST_VALUE)); 
        }
    | TBool { $$ = newLeaf(newNodeInfo($1, BOOLEAN, "BOOL", CONST_VALUE)); }
    | TId { 
            NodeInfo *tid = searchKey(symbolTable, $1);
            if (tid == NULL) {
                printf("Error: variable %s not declared\n", $1);
                exit(1);
            }
            $$ = newLeaf(tid);
        }
    ;

%%
