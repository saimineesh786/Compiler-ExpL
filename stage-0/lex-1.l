%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "y.tab.h"
	#include "exptree.h"
	int number;
%}

%%
[0-9]+	{number=atoi(yytext); yylval.no=makeLeafNode(number);return NUM;}
"+"	{return PLUS;}
"-"	{return MINUS;}
"*"	{return MUL;}
"/"	{return DIV;}
[ \t]	{}
[()]	{return *yytext;}
[\n]	{return END;}
.	{yyerror("unknown character");exit(1);}
%%

int yywrap(void){
	return 1;
}
	 
