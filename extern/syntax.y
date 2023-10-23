%{

#include <stdlib.h>
#include <stdio.h>

#include "../include/dataStructures/ast.h"
#include "../include/dataStructures/nodeInfo.h"
#include "../include/dataStructures/symbolTable.h"
#include "../include/dataStructures/threeAddressCodeList.h"
#include "../include/utils/enums.h"

extern int yylineno;
extern int yytypeCorrect;

SymbolTable* symbolTable;
TAst* globalAst;
int offset;
char* currentMethodName;
%}

 
%union {
    struct TAst* ast;
    enum TType* type;
    char* string;
    void* literal;
    enum TTag* tag;
    enum TOperator* operator;
}

%token<string> TProgram
%token<string> TOpenCurlyBracket
%token<string> TCloseCurlyBracket
%token<string> TOpenParenthesis
%token<string> TCloseParenthesis
%token<string> TSemiColon
%token<string> TComma
%token<type> TType
%token<type> TVoid
%token<string> TIf
%token<string> TThen
%token<string> TElse
%token<string> TWhile
%token<string> TReturn
%token<string> TExtern
%token<string> TAssign
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
%token<literal> TBooleanLiteral
%token<literal> TIntegerLiteral
%token<string> TId

%type<ast> PROGRAM
%type<ast> VAR_DECL_BLOCK
%type<ast> VAR_DECL
%type<ast> METHOD_DECL_BLOCK
%type<ast> METHOD_DECL
%type<ast> METHOD_ENDING
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


%left TAnd TOr          // Lower precedence operators
%nonassoc TEquals TGreaterThan TLessThan
%left TAdd TSub
%left TMul TDiv TMod
%left TNot TNegative    // Greater precedence operators


%initial-action {
    offset = 0;
    initializeSymbolTable(&symbolTable); // TODO: Initialize symbol table with block 0.
} 

%%

PROGRAM: TProgram TOpenCurlyBracket VAR_DECL_BLOCK METHOD_DECL_BLOCK TCloseCurlyBracket {
            NodeInfo* programNode = newNodeInfoSimple(PROGRAM, yylineno);       
            $$ = newAst(programNode, $3, $4);
            globalAst = $$;
            popLevelSymbolTable(&symbolTable);          // This pop is not really necesary.
        }
    | TProgram TOpenCurlyBracket VAR_DECL_BLOCK TCloseCurlyBracket {
            NodeInfo* programNode = newNodeInfoSimple(PROGRAM, yylineno);
            $$ = newAst(programNode, $3, newEmptyAst());
            globalAst = $$;
            popLevelSymbolTable(&symbolTable);
        }
    | TProgram TOpenCurlyBracket METHOD_DECL_BLOCK TCloseCurlyBracket {
            NodeInfo* programNode = newNodeInfoSimple(PROGRAM, yylineno);
            $$ = newAst(programNode, newEmptyAst(), $3);
            globalAst = $$;

            popLevelSymbolTable(&symbolTable);
        }
    ;

VAR_DECL_BLOCK: VAR_DECL_BLOCK VAR_DECL {
            NodeInfo* varDeclBlockNode = newNodeInfoSimple(VAR_DECL_BLOCK, yylineno);
            $$ = newAst(varDeclBlockNode, $2, $1);      // LS is VAR_DECL and RS others VAR_DECL_BLOCK.
        }
    | VAR_DECL {
            $$ = $1;
        }
    ;

VAR_DECL: TType TId TAssign EXPR TSemiColon {
            NodeInfo* alreadyDeclared = searchLocalLevelSymbolTable(symbolTable, $2);       // Check if the identificator is already declared in the current level.
            if (alreadyDeclared != NULL) {                                                  // TODO: save the error in a list.
                printf("\033[1;31mLine: %d Error:\033[0m const identifier %s already declared\n",yylineno, $2);
                exit(1);
            }

            offset++;
            NodeInfo* varNode = newNodeInfoDeclaration($2, *$1, VAR, yylineno, offset);      // Create VAR node.
            addNodeToSymbolTable(&symbolTable, varNode);
            TAst* declaredVariable = newLeaf(&varNode);

            NodeInfo* varDecl = newNodeInfoSimple(VAR_DECL, yylineno);                  // Create a VAR_DECL node to evaluate VAR after with the EXPR.

            $$ = newAst(varDecl, declaredVariable, $4);
        }
    ;

METHOD_DECL_BLOCK: METHOD_DECL_BLOCK METHOD_DECL {
            NodeInfo* methodDeclBlock = newNodeInfoSimple(METHOD_DECL_BLOCK, yylineno);
            $$ = newAst(methodDeclBlock, $2, $1);
        }
    | METHOD_DECL {
            $$ = $1;
        }
    ;

METHOD_DECL: TType TId TOpenParenthesis {
                NodeInfo* alreadyDeclared = searchLocalLevelSymbolTable(symbolTable, $2);       // Check if the identificator is already declared in the current level.
                if (alreadyDeclared != NULL) {                                                  // TODO: save the error in a list.
                    printf("\033[1;31mLine: %d Error:\033[0m const identifier %s already declared\n",yylineno, $2);
                    exit(1);
                }

                offset++;
                NodeInfo* methodNode = newNodeInfoDeclaration($2, *$1, METHOD_DECL, yylineno, offset);    
                addNodeToSymbolTable(&symbolTable, methodNode);                                     // Add the method to the symbol table.
                
                currentMethodName = malloc(strlen($2) + 1);                                             
                currentMethodName = $2;                                                                 // Save the current method name.
                
                addLevelToSymbolTable(&symbolTable);                                                // We include a new level for the params of the method.

            } METHOD_ENDING {
                $$ = $5;
            }

    | TVoid TId TOpenParenthesis {
                NodeInfo* alreadyDeclared = searchLocalLevelSymbolTable(symbolTable, currentMethodName);
                if (alreadyDeclared != NULL) {
                    printf("\033[1;31mLine: %d Error:\033[0m const identifier %s already declared\n",yylineno, $2);
                    exit(1);
                }

                offset++;
                NodeInfo* methodNode = newNodeInfoDeclaration($2, *$1, METHOD_DECL, yylineno, offset);
                addNodeToSymbolTable(&symbolTable, methodNode);
                
                currentMethodName = malloc(strlen($2) + 1);                                             
                currentMethodName = $2;                                                                 // Save the current method name.
                addLevelToSymbolTable(&symbolTable);

            } METHOD_ENDING {
                $$ = $5;
            }
    ;  

METHOD_ENDING: PARAMS_DECL TCloseParenthesis BLOCK {                                                      // The block itself creates and closes its own level
                NodeInfo* methodNode = searchGlobalLevelSymbolTable(symbolTable, currentMethodName);               
                setParamsNodeInfo(&methodNode, $1);                                                       // Link the Method node with the params as a list.
                $$ = newAst(methodNode, $1, $3);                                                          // After the data is linked, and the block is created, we return the method node.
                popLevelSymbolTable(&symbolTable);                                                        // Pop the level created for params.
                free(currentMethodName);
            }
    | PARAMS_DECL TCloseParenthesis TExtern TSemiColon {
                NodeInfo* methodNode = searchGlobalLevelSymbolTable(symbolTable, currentMethodName); 
                setParamsNodeInfo(&methodNode, $1);
                $$ = newLeaf(&methodNode);
                popLevelSymbolTable(&symbolTable);
                free(currentMethodName);
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
                    printf("\033[1;31mLine: %d Error:\033[0m const identifier %s already declared\n",yylineno, $2);
                    exit(1);
                }

            offset++;
            NodeInfo* paramNode = newNodeInfoDeclaration($2, *$1, PARAM, yylineno, offset);    // Don't know if offset is needed.
            $$ = newAst(paramNode, $4, newEmptyAst());
        }
    | TType TId {
            NodeInfo* alreadyDeclared = searchLocalLevelSymbolTable(symbolTable, $2);
                if (alreadyDeclared != NULL) {
                    printf("\033[1;31mLine: %d Error:\033[0m const identifier %s already declared\n",yylineno, $2);
                    exit(1);
                }
            offset++;
            NodeInfo* paramNode = newNodeInfoDeclaration($2, *$1, PARAM, yylineno, offset);
            $$ = newLeaf(&paramNode);
        }
    ;

BLOCK: TOpenCurlyBracket VAR_DECL_BLOCK STATEMENT_BLOCK TCloseCurlyBracket {
            // Add new level to symbol table.
            addLevelToSymbolTable(&symbolTable);

            NodeInfo* blockNode = newNodeInfoSimple(BLOCK, yylineno);
            $$ = newAst(blockNode, $2, $3);

            popLevelSymbolTable(&symbolTable);
        }
    | TOpenCurlyBracket STATEMENT_BLOCK TCloseCurlyBracket {
            addLevelToSymbolTable(&symbolTable);

            NodeInfo* blockNode = newNodeInfoSimple(BLOCK, yylineno);
            $$ = newAst(blockNode, newEmptyAst(), $2);   

            popLevelSymbolTable(&symbolTable);
        }
    ;

STATEMENT_BLOCK: STATEMENT STATEMENT_BLOCK {
            NodeInfo* stmtBlockNode = newNodeInfoSimple(STMT_BLOCK, yylineno);
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
            NodeInfo* assignNode = newNodeInfoSimple(ASSIGNMENT, yylineno);
            $$ = newAst(assignNode, newLeaf(&var), $3);
        }
    ;

METHOD_CALL: TId TOpenParenthesis PARAMS_CALL TCloseParenthesis {
            NodeInfo* method = searchGlobalLevelSymbolTable(symbolTable, $1);
            if (method == NULL) {
                printf("\033[1;31mLine: %d Error:\033[0m method %s not declared\n", yylineno,$1);
                exit(1);
            }
            TAst* methodTree = newLeaf(&method);
            NodeInfo* methodNode = newNodeInfoSimple(METHOD_CALL, yylineno);

            $$ = newAst(methodNode, methodTree, $3);
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
            NodeInfo* paramNode = newNodeInfoSimple(PARAM, yylineno);
            $$ = newAst(paramNode, $1, $3);
        }
    | EXPR {
            NodeInfo* paramNode = newNodeInfoSimple(PARAM, yylineno);   // TODO: REMEMBER TO ASK IF YOU HAVE RS. 
            $$ = newAst(paramNode, $1, newEmptyAst());
        }
    ;

IF_STATEMENT: TIf TOpenParenthesis EXPR TCloseParenthesis TThen BLOCK {
            NodeInfo* ifNode = newNodeInfoSimple(IF, yylineno);
            $$ = newAst(ifNode, $3, $6);
        }
    | TIf TOpenParenthesis EXPR TCloseParenthesis TThen BLOCK TElse BLOCK {
            NodeInfo* ifElseNode = newNodeInfoSimple(IF_ELSE, yylineno);
           
            NodeInfo* blocksNode = newNodeInfoSimple(IF_BLOCKS, yylineno);
            TAst* ifBlock = newAst(blocksNode, $6, $8);

            $$ = newAst(ifElseNode, $3, ifBlock);
        }
    ;

WHILE_STATEMENT: TWhile TOpenParenthesis EXPR TCloseParenthesis BLOCK {
            NodeInfo* whileNode = newNodeInfoSimple(WHILE, yylineno);
            $$ = newAst(whileNode, $3, $5);
        }
    ;

RETURN_STATEMENT: TReturn EXPR TSemiColon {
            NodeInfo* returnNode = newNodeInfoSimple(RETURN, yylineno);
            $$ = newAst(returnNode, $2, newEmptyAst());
        }   
    | TReturn TSemiColon {
            NodeInfo* emptyNode = newEmptyNodeInfo();
            $$ = newLeaf(&emptyNode);
        }
    ;

EXPR: EXPR TAdd EXPR {
            NodeInfo* addNode = newNodeInfoType(INTEGER, ADD, yylineno);     // BINARY OP
            $$ = newAst(addNode, $1, $3);
        }
    | EXPR TSub EXPR {
            NodeInfo* subNode = newNodeInfoType(INTEGER, SUB, yylineno);     // BINARY OP
            $$ = newAst(subNode, $1, $3);
        }
    | EXPR TMul EXPR {
            NodeInfo* mulNode = newNodeInfoType(INTEGER, MUL, yylineno);     // BINARY OP
            $$ = newAst(mulNode, $1, $3);
        }
    | EXPR TDiv EXPR {
            NodeInfo* divNode = newNodeInfoType(INTEGER, DIV, yylineno);     // BINARY OP
            $$ = newAst(divNode, $1, $3);
        }
    | EXPR TMod EXPR {
            NodeInfo* modNode = newNodeInfoType(INTEGER, MOD, yylineno);     // BINARY OP
            $$ = newAst(modNode, $1, $3);
        }
    | EXPR TGreaterThan EXPR {
            NodeInfo* greaterThanNode = newNodeInfoType(BOOLEAN, GREATER_THAN, yylineno);     // BINARY OP
            $$ = newAst(greaterThanNode, $1, $3);
        }
    | EXPR TLessThan EXPR {
            NodeInfo* lessThanNode = newNodeInfoType(BOOLEAN, LESS_THAN, yylineno);     // BINARY OP
            $$ = newAst(lessThanNode, $1, $3);
        }
    | EXPR TEquals EXPR {
            NodeInfo* equalsNode = newNodeInfoType(BOOLEAN, EQUALS, yylineno);     // BINARY OP
            $$ = newAst(equalsNode, $1, $3);
        }
    | EXPR TAnd EXPR {
            NodeInfo* andNode = newNodeInfoType(BOOLEAN, AND, yylineno);             // BINARY OP
            $$ = newAst(andNode, $1, $3);
        }
    | EXPR TOr EXPR {
            NodeInfo* orNode = newNodeInfoType(BOOLEAN, OR, yylineno);             // BINARY OP
            $$ = newAst(orNode, $1, $3);
        }
    | TSub EXPR %prec TNegative {
            NodeInfo* negativeNode = newNodeInfoType(INTEGER, NEGATIVE, yylineno); // UNARY OP
            $$ = newAst(negativeNode, $2, newEmptyAst());
        }
    | TNot EXPR {
            NodeInfo* notNode = newNodeInfoType(BOOLEAN, NOT, yylineno);           // UNARY OP
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
            $$ = newLeaf(newNodeInfoLiteral($1, BOOLEAN, CONST_VALUE, yylineno));  // Node without value and ID.
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
