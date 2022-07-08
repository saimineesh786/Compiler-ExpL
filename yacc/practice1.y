%{
	#include<stdio.h>
	#include<stdlib.h>
%}
%token DIGIT
%left '+'
%left '*'

%%
start 	: expr '\n'	{printf("Successful Parsing\n");exit(1);}
	;
expr	: expr '+' expr	{printf("+ ");}
	| expr '*' expr	{printf("* ");}
	| '(' expr ')'
	| DIGIT	{printf("%d ",$1);}
	;
%%

void yyerror(){
	printf("Parsing Error\n");
}

yylex(){
	int c=getchar();
	if(isdigit(c)){
		yylval=c-'0';
		return DIGIT;
	}
	return c;
}

int main(){
	yyparse();
	return 1;
}
