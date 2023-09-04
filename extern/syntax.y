%{

#include <stdlib.h>
#include <stdio.h>
#include "../include/ast.h"
#include "../include/nodeInfo.h"
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
%type <ast>DECLARATION_LIST
%type <ast>ENTITY
%type <ast>STATEMENT_LIST
%type <ast>ASSIGNMENT
%type <ast>RETURN



%left '+' TPlus
%left '-' TMinus
%left '*' TMultiply
%left '/' TDivide




%%

PROGRAM: DECLARATION_LIST STATEMENT_LIST { 
    NodeInfo *p = newNodeInfo("Program", EMPTY, "Program", NONTERMINAL);
    $$=newAst(p, $1, $2); 
    }
    ;

DECLARATION_LIST: ENTITY ASSIGNMENT DECLARATION_LIST {
                    NodeInfo *declarationInfo = newNodeInfo("declaration", EMPTY, "declaration", NONTERMINAL);
                    TAst* ast = newAst(declarationInfo,$1,$2);
                    NodeInfo *nextDeclInfo = newNodeInfo("declaration", EMPTY, "nextDeclaration", NONTERMINAL);
                    $$ = newAst(nextDeclInfo, ast, $3);
                }
    | /* LAMBDA */{
        NodeInfo *ni = newEmptyNodeInfo();
        $$ = newLeaf(ni);
    }
    ;

ENTITY: TConst TType{
            NodeInfo *tconst = newNodeInfo($1, EMPTY, "const", CONSTANT_DEC);
            NodeInfo *ttype = newNodeInfo($2, EMPTY, "value", CONSTANT_DEC);
            TAst *t = newLeaf(ttype);
            $$ = newAst(tconst, newEmptyAst(), t);
        }
    | TType{
        NodeInfo *ttype = newNodeInfo($1, EMPTY, "value", CONSTANT_DEC);
        $$ = newLeaf(ttype);
    }    
    ;

STATEMENT_LIST: ASSIGNMENT STATEMENT_LIST{
                    NodeInfo *statement = newNodeInfo("statement", EMPTY, "assignStatement", NONTERMINAL);
                    $$ = newAst(statement,$1, $2);
                }
    | RETURN STATEMENT_LIST{
                    NodeInfo *statement = newNodeInfo("statement", EMPTY, "returnStatement", NONTERMINAL);
                    $$ = newAst(statement,$1, $2);
                }
    | ASSIGNMENT{$$=$1;}
    | RETURN{$$=$1;}
    ;

ASSIGNMENT: TId TAssign EXPRESSION TSemiColon { 
            NodeInfo *tid = newNodeInfo($1, EMPTY, $1, CONSTANT_DEC);
            TAst *t = newLeaf(tid);
            NodeInfo *tassign = newNodeInfo($2, EMPTY, "=", OPERATOR);
            $$ = newAst(tassign, t, $3);

            }
    ;

RETURN: TReturn EXPRESSION TSemiColon { 
            NodeInfo *treturn = newNodeInfo($1, EMPTY, "return", CONSTANT_DEC);
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
                                    $$ = newAst(ni, (TAst*)&$1, (TAst*)&$3);
                                    }
    | EXPRESSION TMultiply EXPRESSION {
                                        NodeInfo *ni = newNodeInfo($2, EMPTY, "*", OPERATOR);
                                        $$ = newAst(ni, (TAst*)&$1, (TAst*)&$3);
                                      }
    | EXPRESSION TDivide EXPRESSION {
                                    NodeInfo *ni = newNodeInfo($2, EMPTY, "/", OPERATOR);
                                    $$ = newAst(ni, (TAst*)&$1, (TAst*)&$3);
                                    }
    | TOpenParenthesis EXPRESSION TCloseParenthesis { $$ = $2;}
    | TInteger  { $$ = newLeaf(newNodeInfo($1, INTEGER, "INT", CONSTANT_DEC)); }
    | TBool { $$ = newLeaf(newNodeInfo($1, BOOLEAN, "BOOL", CONSTANT_DEC)); }
    | TId { $$ = newLeaf(newNodeInfo($1, EMPTY, $1, VARIABLE));  }
    ;
%%
