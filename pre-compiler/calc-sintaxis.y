%{

#include <stdlib.h>
#include <stdio.h>

%}
 
%token INT
%token ID
%token TMENOS
%token TEQUALS
%token TRETURN
%token TCONST

%type expr
%type VALOR
    
%left '+' TMENOS 
%left '*'
 
%%
 
prog: decl sent { printf("No hay errores \n"); } 
    ;

decl: type asign decl 
    | /* lambda */
    ;

type: TCONST INT
    | INT
    ;

sent: asign sent 
    | ret sent
    | asign
    | ret
    | /* lambda */
    ;

asign: ID TEQUALS expr ';'
    ;

ret: TRETURN ID ';' 
    | TRETURN expr ';'
    ; 


expr: VALOR     

    | ID          

    | expr '+' expr    
    
    | expr '*' expr

    | expr TMENOS expr  

    | '(' expr ')'      
    ;


VALOR : INT              
       ;

%%


