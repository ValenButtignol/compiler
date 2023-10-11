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
    initializeSymbolTable(&symbolTable); // TODO: Initialize symbol table with block 0.
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
%token<type> TType
%token<type> TVoid
%token TIf
%token TThen
%token TElse
%token TWhile
%token TReturn
%token TExtern
%token TAssign
%token<operator> TNot
%token<operator> TAdd
%token<operator> TSub
%token<operator> TMul
%token<operator> TDiv
%token<operator> TMod
%token<operator> TLessThan
%token<operator> TGreaterThan
%token<operator> TEquals
%token<operator> TAnd
%token<operator> TOr
%token<boolean> TBooleanLiteral
%token<integer> TIntegerLiteral
%token<string> TId

%type<ast> PROGRAM
%type<ast> VAR_DECL_BLOCK
%type<ast> VAR_DECL
%type<ast> METHOD_DECL_BLOCK
%type<ast> METHOD_DECL
%type<ast> PARAMS_DECL
%type<ast> PARAMS_LIST_DECL
%type<ast> BLOCK
%type<ast> STATEMENT_BLOCK
%type<ast> STATEMENT
%type<ast> ASSIGNMENT
%type<ast> METHOD_CALL
%type<ast> PARAMS_CALL
%type<ast> PARAMS_LIST_CALL
%type<ast> IF_STATEMENT
%type<ast> WHILE_STATEMENT
%type<ast> RETURN_STATEMENT
%type<ast> EXPR
%type<ast> LITERAL


%left TAnd TOr
%nonassoc TEquals TGreaterThan TLessThan
%left TAdd TSub
%left TMul TDiv TMod
%left TNot 
%left TNegative

%%

PROGRAM: TProgram TOpenCurlyBracket VAR_DECL_BLOCK METHOD_DECL_BLOCK TCloseCurlyBracket {
            NodeInfo* programNode = newNodeInfo(NONETYPE, PROGRAM, yylineno);
            $$ = newAst(programNode, $3, $4);
            globalAst = $$;
            popLevelSymbolTable(&symbolTable);
        }
    | TProgram TOpenCurlyBracket VAR_DECL_BLOCK TCloseCurlyBracket {
            NodeInfo* programNode = newNodeInfo(NONETYPE, PROGRAM, yylineno);
            $$ = newAst(programNode, $3, newEmptyAst());
            globalAst = $$;
            popLevelSymbolTable(&symbolTable);
        }
    | TProgram TOpenCurlyBracket METHOD_DECL_BLOCK TCloseCurlyBracket {
            NodeInfo* programNode = newNodeInfo(NONETYPE, PROGRAM, yylineno);
            $$ = newAst(programNode, newEmptyAst(), $3);
            globalAst = $$;

            popLevelSymbolTable(&symbolTable);
        }
    ;

VAR_DECL_BLOCK: VAR_DECL_BLOCK VAR_DECL {
            NodeInfo* varDeclBlockNode = newNodeInfo(NONETYPE, VAR_DECL_BLOCK, yylineno);
            $$ = newAst(varDeclBlockNode, $2, $1);
        }
    | VAR_DECL {
            $$ = $1;
        }
    ;

VAR_DECL: TType TId TAssign EXPR TSemiColon {
            NodeInfo* alreadyDeclared = searchLocalLevelSymbolTable(symbolTable, $2);
            if (alreadyDeclared != NULL) {
                printf("\033[1;31mLine: %d Error:\033[0m const identifier %s already declared\n",yylineno, $3);
                exit(1);
            }

            offset++;
            NodeInfo* varNode = newNodeInfoDeclaration($1, $2, VAR, yylineno, offset);
            addToSymbolTable(&symbolTable, varNode);
            TAst* declaredVariable = newLeaf(&varNode);            

            NodeInfo* varDecl = newNodeInfo(NONETYPE, VAR_DECL, yylineno);

            $$ = newAst(varDecl, declaredVariable, $4);
        }
    ;

METHOD_DECL_BLOCK: METHOD_DECL_BLOCK METHOD_DECL {
            NodeInfo* methodDeclBlock = newNodeInfo(NONETYPE, METHOD_DECL_BLOCK, yylineno);
            $$ = newAst(methodDeclBlock, $2, $1);
        }
    | METHOD_DECL {
            $$ = $1;
        }
    ;

METHOD_DECL: TType TId TOpenParenthesis {
                NodeInfo* alreadyDeclared = searchLocalLevelSymbolTable(symbolTable, $2);
                if (alreadyDeclared != NULL) {
                    printf("\033[1;31mLine: %d Error:\033[0m const identifier %s already declared\n",yylineno, $3);
                    exit(1);
                }

                offset++;
                NodeInfo* methodNode = newNodeInfoDeclaration($1, $2, METHOD, yylineno, offset);
                addNodeToSymbolTable(&symbolTable, methodNode);
                
                addLevelToSymbolTable(&symbolTable);

            } PARAMS_DECL TCloseParenthesis {
                
                NodeInfo* methodNode = searchGlobalLevelSymbolTable(symbolTable, $2); 
                setParamsNodeInfo(methodNode, $4);
                
            } BLOCK {            
                NodeInfo* methodNode = searchGlobalLevelSymbolTable(symbolTable, $2);
                $$ = newLeaf(&methodNode);
                popLevelSymbolTable(&symbolTable);      // Pop the level created for params.
        }
    | TType TId TOpenParenthesis {
                NodeInfo* alreadyDeclared = searchLocalLevelSymbolTable(symbolTable, $2);
                if (alreadyDeclared != NULL) {
                    printf("\033[1;31mLine: %d Error:\033[0m const identifier %s already declared\n",yylineno, $3);
                    exit(1);
                }

                offset++;
                NodeInfo* methodNode = newNodeInfoDeclaration($1, $2, METHOD, yylineno, offset);
                addNodeToSymbolTable(&symbolTable, methodNode);
                
                addLevelToSymbolTable(&symbolTable);

            } PARAMS_DECL TCloseParenthesis TExtern TSemiColon {

                NodeInfo* methodNode = searchGlobalLevelSymbolTable(symbolTable, $2); 
                setParamsNodeInfo(methodNode, $4);
                $$ = newLeaf(&methodNode);
                popLevelSymbolTable(&symbolTable);

        }
    | TVoid TId TOpenParenthesis {
                NodeInfo* alreadyDeclared = searchLocalLevelSymbolTable(symbolTable, $2);
                if (alreadyDeclared != NULL) {
                    printf("\033[1;31mLine: %d Error:\033[0m const identifier %s already declared\n",yylineno, $3);
                    exit(1);
                }

                offset++;
                NodeInfo* methodNode = newNodeInfoDeclaration($1, $2, METHOD, yylineno, offset);
                addNodeToSymbolTable(&symbolTable, methodNode);
                
                addLevelToSymbolTable(&symbolTable);

            } PARAMS_DECL TCloseParenthesis {
                
                NodeInfo* methodNode = searchGlobalLevelSymbolTable(symbolTable, $2); 
                setParamsNodeInfo(methodNode, $4);
                
            } BLOCK {            
                NodeInfo* methodNode = searchGlobalLevelSymbolTable(symbolTable, $2);
                $$ = newLeaf(&methodNode);
                popLevelSymbolTable(&symbolTable);      // Pop the level created for params.
        }
    | TVoid TId TOpenParenthesis {
                NodeInfo* alreadyDeclared = searchLocalLevelSymbolTable(symbolTable, $2);
                if (alreadyDeclared != NULL) {
                    printf("\033[1;31mLine: %d Error:\033[0m const identifier %s already declared\n",yylineno, $3);
                    exit(1);
                }

                offset++;
                NodeInfo* methodNode = newNodeInfoDeclaration($1, $2, METHOD, yylineno, offset);
                addNodeToSymbolTable(&symbolTable, methodNode);
                
                addLevelToSymbolTable(&symbolTable);

            } PARAMS_DECL TCloseParenthesis TExtern TSemiColon {
            
            NodeInfo* methodNode = searchGlobalLevelSymbolTable(symbolTable, $2); 
            setParamsNodeInfo(methodNode, $4);
            $$ = newLeaf(&methodNode);
            popLevelSymbolTable(&symbolTable);
            
        }
    ;  


PARAMS_DECL: PARAMS_LIST_DECL {
            $$ = $1;
        }
    | /* LAMBDA */ {
            NodeInfo* emptyNode = newEmptyNodeInfo();
            $$ = newLeaf(&emptyNode);
        }
    ;

PARAMS_LIST_DECL: TType TId TComma PARAMS_LIST_DECL {
            NodeInfo* alreadyDeclared = searchLocalLevelSymbolTable(symbolTable, $2);
                if (alreadyDeclared != NULL) {
                    printf("\033[1;31mLine: %d Error:\033[0m const identifier %s already declared\n",yylineno, $3);
                    exit(1);
                }

            offset++;
            NodeInfo* paramNode = newNodeInfoParameterDecl($1, $2, PARAM, yylineno, offset);
            $$ = newAst(paramNode, $4, newEmptyAst());
        }
    | TType TId {
            NodeInfo* alreadyDeclared = searchLocalLevelSymbolTable(symbolTable, $2);
                if (alreadyDeclared != NULL) {
                    printf("\033[1;31mLine: %d Error:\033[0m const identifier %s already declared\n",yylineno, $3);
                    exit(1);
                }
            offset++;
            NodeInfo* paramNode = newNodeInfoParameterDecl($1, $2, PARAM, yylineno, offset);
            $$ = newLeaf(&paramNode);
        }
    ;

BLOCK: TOpenCurlyBracket VAR_DECL_BLOCK STATEMENT_BLOCK TCloseCurlyBracket {
            // Add new level to symbol table.
            addLevelToSymbolTable(&symbolTable);

            NodeInfo* blockNode = newNodeInfo(NONETYPE, BLOCK, yylineno);
            $$ = newAst(blockNode, $2, $3);

            popLevelSymbolTable(&symbolTable);
        }
    | TOpenCurlyBracket STATEMENT_BLOCK TCloseCurlyBracket {
            addLevelToSymbolTable(&symbolTable);

            NodeInfo* blockNode = newNodeInfo(NONETYPE, BLOCK, yylineno);
            $$ = newAst(blockNode, $2, $3);   

            popLevelSymbolTable(&symbolTable);
        }
    ;

STATEMENT_BLOCK: STATEMENT STATEMENT_BLOCK {
            NodeInfo* stmtBlockNode = newNodeInfo(NONETYPE, STMT_BLOCK, yylineno);
            $$ = newAst(stmtBlockNode, $1, $2);
        }
    | /* LAMBDA */ {
            NodeInfo* emptyNode = newEmptyNodeInfo();
            $$ = newLeaf(&emptyNode);
        }
    ;

STATEMENT: ASSIGNMENT TSemiColon {
            $$ = $1;
        }
    | METHOD_CALL TSemiColon {
            $$ = $1;
        }
    | IF_STATEMENT {
            $$ = $1;
        }
    | WHILE_STATEMENT {
            $$ = $1;
        }
    | RETURN_STATEMENT {
            $$ = $1;
        }
    | BLOCK {
            $$ = $1;
        }
    | TSemiColon {
            NodeInfo* emptyNode = newEmptyNodeInfo();
            $$ = newLeaf(&emptyNode);
        }
    ;

ASSIGNMENT: TId TAssign EXPR {
            NodeInfo* var = searchGlobalLevelSymbolTable(symbolTable, $1);
            if (var == NULL) {
                printf("\033[1;31mLine: %d Error:\033[0m variable %s not declared\n", yylineno,$1);
                exit(1);
            }
            NodeInfo* assignNode = newNodeInfo(NONETYPE, ASSIGN, yylineno);
            $$ = newAst(assignNode, newLeaf(&var), $3);
        }
    ;

METHOD_CALL: TId TOpenParenthesis PARAMS_CALL TCloseParenthesis {
            NodeInfo* method = searchGlobalLevelSymbolTable(symbolTable, $1);
            if (method == NULL) {
                printf("\033[1;31mLine: %d Error:\033[0m method %s not declared\n", yylineno,$1);
                exit(1);
            }
            
            $$ = newAst(methodNode, newLeaf(&search(symbolTable, $1)), $3);
        }
    ;

PARAMS_CALL: PARAMS_LIST_CALL {
            $$ = $1;
        }
    | /* LAMBDA */ {
            NodeInfo* emptyNode = newEmptyNodeInfo();
            $$ = newLeaf(&emptyNode);
        }
    ;

PARAMS_LIST_CALL: EXPR TComma PARAMS_LIST_CALL {
            NodeInfo* paramNode = newNodeInfo(NONETYPE, PARAM, yylineno);
            $$ = newAst(paramNode, $1, $3);
        }
    | EXPR {
            NodeInfo* paramNode = newNodeInfo(NONETYPE, PARAM, yylineno);   // TODO: REMEMBER TO ASK IF YOU HAVE RS. 
            $$ = newAst(paramNode, $1, newEmptyAst());
        }
    ;

IF_STATEMENT: TIf TOpenParenthesis EXPR TCloseParenthesis TThen BLOCK {
            NodeInfo* ifNode = newNodeInfo(NONETYPE, IF, yylineno);
            $$ = newAst(ifNode, $3, $5);
        }
    | TIf TOpenParenthesis EXPR TCloseParenthesis TThen BLOCK TElse BLOCK {
            NodeInfo* ifElseNode = newNodeInfo(NONETYPE, IF_ELSE, yylineno);
           
            NodeInfo* blocksNode = newNodeInfo(NONETYPE, IF_BLOCKS, yylineno);
            TAst* ifBlock = newAst(blocksNode, $5, $7);

            $$ = newAst(ifElseNode, $3, ifBlock);
        }
    ;

WHILE_STATEMENT: TWhile TOpenParenthesis EXPR TCloseParenthesis BLOCK {
            NodeInfo* whileNode = newNodeInfo(NONETYPE, WHILE, yylineno);
            $$ = newAst(whileNode, $3, $5);
        }
    ;

RETURN_STATEMENT: TReturn EXPR TSemiColon {
            NodeInfo* returnNode = newNodeInfo(NONETYPE, RETURN, yylineno);
            $$ = newAst(returnNode, $2, newEmptyAst());
        }   
    | TReturn TSemiColon {
            NodeInfo* emptyNode = newEmptyNodeInfo();
            $$ = newLeaf(&emptyNode);
        }
    ;

EXPR: EXPR TAdd EXPR {
            NodeInfo* addNode = newNodeInfo(INTEGER, ADD, yylineno);     // BINARY OP
            $$ = newAst(addNode, $1, $3);
        }
    | EXPR TSub EXPR {
            NodeInfo* subNode = newNodeInfo(INTEGER, SUB, yylineno);     // BINARY OP
            $$ = newAst(subNode, $1, $3);
        }
    | EXPR TMul EXPR {
            NodeInfo* mulNode = newNodeInfo(INTEGER, MUL, yylineno);     // BINARY OP
            $$ = newAst(mulNode, $1, $3);
        }
    | EXPR TDiv EXPR {
            NodeInfo* divNode = newNodeInfo(INTEGER, DIV, yylineno);     // BINARY OP
            $$ = newAst(divNode, $1, $3);
        }
    | EXPR TMod EXPR {
            NodeInfo* modNode = newNodeInfo(INTEGER, MOD, yylineno);     // BINARY OP
            $$ = newAst(modNode, $1, $3);
        }
    | EXPR TGreaterThan EXPR {
            NodeInfo* greaterThanNode = newNodeInfo(BOOLEAN, GREATER_THAN, yylineno);     // BINARY OP
            $$ = newAst(greaterThanNode, $1, $3);
        }
    | EXPR TLessThan EXPR {
            NodeInfo* lessThanNode = newNodeInfo(BOOLEAN, LESS_THAN, yylineno);     // BINARY OP
            $$ = newAst(lessThanNode, $1, $3);
        }
    | EXPR TEquals EXPR {
            NodeInfo* equalsNode = newNodeInfo(BOOLEAN, EQUALS, yylineno);     // BINARY OP
            $$ = newAst(equalsNode, $1, $3);
        }
    | EXPR TAnd EXPR {
            NodeInfo* andNode = newNodeInfo(BOOLEAN, AND, yylineno);             // BINARY OP
            $$ = newAst(andNode, $1, $3);
        }
    | EXPR TOr EXPR {
            NodeInfo* orNode = newNodeInfo(BOOLEAN, OR, yylineno);             // BINARY OP
            $$ = newAst(orNode, $1, $3);
        }
    | TSub EXPR %prec TNegative {
            NodeInfo* negativeNode = newNodeInfo(INTEGER, NEGATIVE, yylineno); // UNARY OP
            $$ = newAst(negativeNode, $2, newEmptyAst());
        }
    | TNot EXPR {
            NodeInfo* notNode = newNodeInfo(BOOLEAN, NOT, yylineno);           // UNARY OP
            $$ = newAst(notNode, $2, newEmptyAst());
        }
    | METHOD_CALL {
            $$ = $1;
        }
    | LITERAL {
            $$ = $1;
        }
    | TId {
            NodeInfo* var = searchGlobalLevelSymbolTable(symbolTable, $1);
            if (var == NULL) {
                printf("\033[1;31mLine: %d Error:\033[0m variable %s not declared\n", yylineno,$1);
                exit(1);
            }
            $$ = newLeaf(&var);
        }
    | TOpenParenthesis EXPR TCloseParenthesis {
            $$ = $2;
        }
    ;

LITERAL: TIntegerLiteral {
            $$ = newLeaf(newNodeInfoLiteral($1, INTEGER, CONST_VALUE, yylineno));         // Node without value and ID.
        }
    | TBooleanLiteral {
            $$ = newLeaf(newNodeInfoLiteral((void)*$1, BOOLEAN, CONST_VALUE, yylineno));  // Node without value and ID.
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
