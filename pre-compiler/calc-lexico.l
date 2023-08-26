%{

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "calc-sintaxis.tab.h"

%}

%option noyywrap
%option yylineno

letra [a-zA-Z]      
digito [0-9]   


%%

{digito}                     { 
                                printf("%d",atoi(yytext)); 
                                return INT;}

"int"                     { 
                                printf("%s ",yytext); 
                                return INT;}

"const"					 { 
                                printf("%s ",yytext); 
                                return TCONST;}									

"return"                     { 
                                printf("%s ",yytext); 
                                return TRETURN;}

{letra}({letra}|{digito})*    { 
                                printf("%s ",yytext);
                                return ID;}

"-"                       {  printf("%s ",yytext);
                                  return TMENOS;}    

"="						 { printf("%s ",yytext);
									return TEQUALS;}

[+*()]                   {  printf("%s ",yytext);
                                  return *yytext;}

[;]						 {  printf("%s\n",yytext);
                                  return *yytext;}
.|\n                          ; /* ignore all the rest */

%%

void yyerror(){
	printf("%s%d\n","-> ERROR Sintactico en la linea: ",yylineno);
}

int main(int argc,char *argv[]){
	++argv,--argc;
	if (argc > 0)
		yyin = fopen(argv[0],"r");
	else
		yyin = stdin;

	yyparse();

}
