%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "y.tab.h"
	#include "declarations.h"
	int number;
	char *symbol;
%}

%%
[0-9]+	{
	number=atoi(yytext);
	yylval.no=createLeafNode(number,int_type,NULL,0);
	return NUM;
	}
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
"if"	{return IF;}
"then"	{return THEN;}
"else"	{return ELSE;}
"endif" {return ENDIF;}
"while" {return WHILE;}
"do"	{return DO;}
"endwhile" {return ENDWHILE;}
[a-z]	{
	symbol=(char *)malloc(sizeof(char));
	*symbol=*yytext;
	yylval.no=createLeafNode(0,int_type,symbol,1);
	return ID;
	}
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
