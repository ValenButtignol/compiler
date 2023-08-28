%{

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "syntax.tab.h"

%}

%option noyywrap
%option yylineno

letter [a-zA-Z]      
digit [0-9]


%%

"boolean" {  
        printf("TType: %s\n",yytext);
        return TType;
    }

"int" {  
        printf("TType: %s\n",yytext);
        return TType;
    }

"const" {  
        printf("TConst: %s\n",yytext);
        return TConst;
    }

";" {  
        printf("TSemiColon: %s\n",yytext);
        return TSemiColon;
    }

"return" {  
        printf("TReturn: %s\n",yytext);
        return TReturn;
    }

"=" {  
        printf("TAssign: %s\n",yytext);
        return TAssign;
    }

"+" {  
        printf("TPlus: %s\n",yytext);
        return TPlus;
    }

"-" {  
        printf("TMinus: %s\n",yytext);
        return TMinus;
    }    

"*" {  
        printf("TMultiply: %s\n",yytext);
        return TMultiply;
    }

"/" {  
        printf("TDivide: %s\n",yytext);
        return TDivide;
    }

"(" {  
        printf("TOpenParenthesis: %s\n",yytext);
        return TOpenParenthesis;
    }

")" {  
        printf("TCloseParenthesis: %s\n",yytext);
        return TCloseParenthesis;
    }

{digit}+ { 
        printf("TInteger: %d\n",atoi(yytext)); 
        return TInteger;
    }

"true" { 
        printf("TBool: %s\n",yytext); 
        return TBool;
    }

"false" { 
        printf("TBool: %s\n",yytext); 
        return TBool;
    }

{letter}({letter}|{digit})* { 
        printf("TId: %s\n",yytext);
        return TId;
    }

.|\n ; /* ignore all the rest */

%%

void yyerror(){
	printf("%s%d\n","-> Syntax ERROR at: ",yylineno);
}

int main(int argc,char *argv[]){
	++argv,--argc;
	if (argc > 0)
		yyin = fopen(argv[0],"r");
	else
		yyin = stdin;

	yyparse();

}