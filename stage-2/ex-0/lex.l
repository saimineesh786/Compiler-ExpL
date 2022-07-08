%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "y.tab.h"
	#include "exptree.h"
	int number;
%}

%%
[0-9]+	{number=atoi(yytext); yylval.no=makeLeafNode(0,number,NULL);return NUM;}
"+"	{return PLUS;}
"-"	{return MINUS;}
"*" 	{return MUL;}
"/"	{return DIV;}
"="	{return ASSIGN;}
"begin" {return BEGINER;}
"end"	{return END;}
"read"  {return READ;}
"write" {return WRITE;}
[a-z]	{yylval.no=makeLeafNode(1,0,yytext);return ID;}
";"	{return *yytext;}
[ \t]	{}
[()]	{return *yytext;}
[\n]	{}
.	{yyerror("unknown character");exit(1);}
%%

int yywrap(void){
	return 1;
}
