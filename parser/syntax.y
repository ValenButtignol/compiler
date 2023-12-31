%{

#include <stdlib.h>
#include <stdio.h>

#include "../include/dataStructures/ast.h"
#include "../include/dataStructures/nodeInfo.h"
#include "../include/dataStructures/symbolTable.h"
#include "../include/dataStructures/threeAddressCodeList.h"
#include "../include/utils/enums.h"
#include "../include/utils/utils.h"

extern int yylineno;
extern int yytypeCorrect;

SymbolTable* symbolTable;
TAst* globalAst;
ErrorNode* errors;
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
%token<string> TDef
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
%type<ast> OPENBLOCK
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
    errors = NULL;
    offset = 0;
    initializeSymbolTable(&symbolTable);
} 

%%

   
PROGRAM: TProgram TOpenCurlyBracket VAR_DECL_BLOCK METHOD_DECL_BLOCK TCloseCurlyBracket {

            NodeInfo* programNode = newNodeInfoSimple(PROGRAM, yylineno);       
            $$ = newAst(programNode, $3, $4);
            globalAst = $$;
            popLevelSymbolTable(&symbolTable);          
        }
    | TProgram TOpenCurlyBracket METHOD_DECL_BLOCK TCloseCurlyBracket {
            NodeInfo* programNode = newNodeInfoSimple(PROGRAM, yylineno);
            $$ = newAst(programNode, NULL, $3);
            globalAst = $$;
            popLevelSymbolTable(&symbolTable);
        }
    ;

VAR_DECL_BLOCK: VAR_DECL VAR_DECL_BLOCK {

            NodeInfo* varDeclBlockNode = newNodeInfoSimple(VAR_DECL_BLOCK, yylineno);
            $$ = newAst(varDeclBlockNode, $1, $2);      
        }
    | VAR_DECL {
            $$ = $1;
        }
    ;

VAR_DECL: TType TId TAssign EXPR TSemiColon {
            NodeInfo* alreadyDeclared = searchLocalLevelSymbolTable(symbolTable, $2);       // Check if the id is already declared in the current level.
            if (alreadyDeclared != NULL) {   
                addVariableIDDeclaredError(&errors, yylineno, $2);
            }

            offset++;
            NodeInfo* varNode = newNodeInfoDeclaration($2, *$1, VAR, yylineno, offset);      
            addNodeToSymbolTable(&symbolTable, varNode);
            TAst* declaredVariable = newLeaf(&varNode);
            
            NodeInfo* varDecl = newNodeInfoType(varNode->type, VAR_DECL, yylineno);

            $$ = newAst(varDecl, declaredVariable, $4);

        }
    ;

METHOD_DECL_BLOCK: METHOD_DECL METHOD_DECL_BLOCK {
            NodeInfo* methodDeclBlock = newNodeInfoSimple(METHOD_DECL_BLOCK, yylineno);
            $$ = newAst(methodDeclBlock, $1, $2);
        }
    | METHOD_DECL {
            $$ = $1;
        }
    ;

METHOD_DECL: TDef TType TId TOpenParenthesis {

                NodeInfo* alreadyDeclared = searchLocalLevelSymbolTable(symbolTable, $3);
                if (alreadyDeclared != NULL) {   
                    addProcedureIDDeclaredError(&errors, yylineno, $3);
                }
                offset = 0;
                NodeInfo* methodNode = newNodeInfoDeclaration($3, *$2, METHOD_DECL, yylineno, offset);    
                addNodeToSymbolTable(&symbolTable, methodNode);                                     
                
                currentMethodName = malloc(strlen($3) + 1);                                             
                currentMethodName = $3;                                                                
                
                addLevelToSymbolTable(&symbolTable);

            } METHOD_ENDING {
                $$ = $6;
            }

    | TDef TVoid TId TOpenParenthesis {
                
                NodeInfo* alreadyDeclared = searchLocalLevelSymbolTable(symbolTable, $3);
                if (alreadyDeclared != NULL) {   
                    addProcedureIDDeclaredError(&errors, yylineno, $3);
                }

                offset = 0;
                NodeInfo* methodNode = newNodeInfoDeclaration($3, *$2, METHOD_DECL, yylineno, offset);
                addNodeToSymbolTable(&symbolTable, methodNode);                
                currentMethodName = malloc(strlen($3) + 1);                                             
                currentMethodName = $3;             

                addLevelToSymbolTable(&symbolTable);

            } METHOD_ENDING {
                $$ = $6;
            }
    ;  

METHOD_ENDING: PARAMS_DECL TCloseParenthesis BLOCK {                                                      // The block itself creates and closes its own level
                NodeInfo* methodNode = searchGlobalLevelSymbolTable(symbolTable, currentMethodName);     
                setParamsToNodeInfo(&methodNode, $1);
                setNewOffset(&methodNode, offset);        
                $$ = newAst(methodNode, $1, $3);                                                          // After the data is linked, and the block is created, adn return the method node.
                popLevelSymbolTable(&symbolTable);                                                        // Pop the level created for params.
                free(currentMethodName);
            }
    | PARAMS_DECL TCloseParenthesis TExtern TSemiColon {
                NodeInfo* methodNode = searchGlobalLevelSymbolTable(symbolTable, currentMethodName); 
                setParamsToNodeInfo(&methodNode, $1);
                setNewOffset(&methodNode, offset);
                setNewTag(&methodNode, EXTERN_METHOD_DECL);
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
                addParameterIDDeclaredError(&errors, yylineno, $2);
            }

            offset++;
            NodeInfo* paramNode = newNodeInfoDeclaration($2, *$1, PARAM, yylineno, offset);
            addNodeToSymbolTable(&symbolTable, paramNode);
            $$ = newAst(paramNode, $4, NULL);
        }
    | TType TId {
            NodeInfo* alreadyDeclared = searchLocalLevelSymbolTable(symbolTable, $2);
            if (alreadyDeclared != NULL) {   
                addParameterIDDeclaredError(&errors, yylineno, $2);
            }
            offset++;
            NodeInfo* paramNode = newNodeInfoDeclaration($2, *$1, PARAM, yylineno, offset);
            addNodeToSymbolTable(&symbolTable, paramNode);
            $$ = newLeaf(&paramNode);
        }
    ;

            
BLOCK: TOpenCurlyBracket { addLevelToSymbolTable(&symbolTable); } OPENBLOCK {
            $$ = $3;
        }
    ;

OPENBLOCK: VAR_DECL_BLOCK STATEMENT_BLOCK TCloseCurlyBracket {

            NodeInfo* blockNode = newNodeInfoSimple(BLOCK, yylineno);
            $$ = newAst(blockNode, $1, $2);

            popLevelSymbolTable(&symbolTable);
        }
    | STATEMENT_BLOCK TCloseCurlyBracket {

            NodeInfo* blockNode = newNodeInfoSimple(BLOCK, yylineno);
            $$ = newAst(blockNode, NULL, $1);   

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
                addVariableIDNotDeclaredError(&errors, yylineno, $1);
            }else{
                NodeInfo* assignNode = newNodeInfoType(var->type, ASSIGNMENT, yylineno);
                $$ = newAst(assignNode, newLeaf(&var), $3);
            }
        }
    ;

METHOD_CALL: TId TOpenParenthesis PARAMS_CALL TCloseParenthesis {
            NodeInfo* method = searchGlobalLevelSymbolTable(symbolTable, $1);
            if (method == NULL) {
                addProcedureIDNotDeclaredError(&errors, yylineno, $1);
            }else{
                NodeInfo* callNode = newNodeInfoType(method->type, METHOD_CALL, yylineno);
                setParamsToNodeInfo(&callNode, $3);                                                           
                $$ = newAst(callNode, $3, newLeaf(&method));
            }
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
            NodeInfo* paramNode = newNodeInfoType($1->data->type, PARAM, yylineno);
            $$ = newAst(paramNode, $3, $1);
        }
    | EXPR {
            NodeInfo* paramNode = newNodeInfoType($1->data->type, PARAM, yylineno);
            $$ = newAst(paramNode, NULL, $1);
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
            NodeInfo* method = searchGlobalLevelSymbolTable(symbolTable, currentMethodName);
            NodeInfo* returnNode = newNodeInfoType(method->type, RETURN, yylineno);
            $$ = newAst(returnNode, $2, NULL);
        }   
    | TReturn TSemiColon {
            NodeInfo* emptyNode = newNodeInfoType(VOID, RETURN, yylineno);
            $$ = newLeaf(&emptyNode);

        }
    ;

EXPR: EXPR TAdd EXPR {
            NodeInfo* addNode = newNodeInfoType(INTEGER, ADD, yylineno);
            $$ = newAst(addNode, $1, $3);
        }
    | EXPR TSub EXPR {
            NodeInfo* subNode = newNodeInfoType(INTEGER, SUB, yylineno);
            $$ = newAst(subNode, $1, $3);
        }
    | EXPR TMul EXPR {
            NodeInfo* mulNode = newNodeInfoType(INTEGER, MUL, yylineno);
            $$ = newAst(mulNode, $1, $3);
        }
    | EXPR TDiv EXPR {
            NodeInfo* divNode = newNodeInfoType(INTEGER, DIV, yylineno);
            $$ = newAst(divNode, $1, $3);
        }
    | EXPR TMod EXPR {
            NodeInfo* modNode = newNodeInfoType(INTEGER, MOD, yylineno);
            $$ = newAst(modNode, $1, $3);
        }
    | EXPR TGreaterThan EXPR {
            NodeInfo* greaterThanNode = newNodeInfoType(BOOLEAN, GREATER_THAN, yylineno);
            $$ = newAst(greaterThanNode, $1, $3);
        }
    | EXPR TLessThan EXPR {
            NodeInfo* lessThanNode = newNodeInfoType(BOOLEAN, LESS_THAN, yylineno);
            $$ = newAst(lessThanNode, $1, $3);
        }
    | EXPR TEquals EXPR {
            NodeInfo* equalsNode = newNodeInfoType(BOOLEAN, EQUALS, yylineno);
            $$ = newAst(equalsNode, $1, $3);
        }
    | EXPR TAnd EXPR {
            NodeInfo* andNode = newNodeInfoType(BOOLEAN, AND, yylineno);
            $$ = newAst(andNode, $1, $3);
        }
    | EXPR TOr EXPR {
            NodeInfo* orNode = newNodeInfoType(BOOLEAN, OR, yylineno);
            $$ = newAst(orNode, $1, $3);
        }
    | TSub EXPR %prec TNegative {
            NodeInfo* negativeNode = newNodeInfoType(INTEGER, NEGATIVE, yylineno);
            $$ = newAst(negativeNode, $2, NULL);
        }
    | TNot EXPR {
            NodeInfo* notNode = newNodeInfoType(BOOLEAN, NOT, yylineno);          
            $$ = newAst(notNode, $2, NULL);
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
                addVariableIDNotDeclaredError(&errors, yylineno, $1);
            }else{
                $$ = newLeaf(&var);
            }
        }
    | TOpenParenthesis EXPR TCloseParenthesis {
            $$ = $2;
        }
    ;

LITERAL: TIntegerLiteral {
            NodeInfo* literalNode = newNodeInfoLiteral($1, INTEGER, CONST_VALUE, yylineno);
            $$ = newLeaf(&literalNode);       
        }
    | TBooleanLiteral {
            NodeInfo* literalNode = newNodeInfoLiteral($1, BOOLEAN, CONST_VALUE, yylineno);
            $$ = newLeaf(&literalNode);
        }
    ;

%%

TAst* getGlobalAst() {
    return globalAst;
}

SymbolTable* getSymbolTable() {
    return symbolTable;
}

ErrorNode* getErrors() {
    return errors;
}