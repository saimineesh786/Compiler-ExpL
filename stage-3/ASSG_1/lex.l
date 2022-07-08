%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
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
"<"	{return LT;}
">"	{return GT;}
"<="	{return LTE;}
">="	{return GTE;}
"!="	{return NTEQ;}
"=="	{return EQ;}
"read"  {return READ;}
"write" {return WRITE;}
"If"	{return IF;}
"else"	{return ELSE;}
"FUN"	{return FUN;}
"while" {return WHILE;}
"do"	{return DO;}
[a-z][a-z0-9]*	{yylval.no=makeLeafNode(0,0,yytext);return ID;}
";"	{return *yytext;}
[ \t]	{}
[(){}]	{return *yytext;}
[\n]	{}
[ ]+	{}
.	{printf("%s\n",yytext);yyerror("unknown character");exit(1);}
%%

int yywrap(void){
	return 1;
}
