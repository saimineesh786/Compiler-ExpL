%{
	#include<stdio.h>
	#include<stdlib.h>
%}
%token letter number
%%
start 	: letter variable '\n' {return ;}
	;
variable : letter variable
	| number variable
	| epsilon
	;
epsilon : ;
%%

void yyerror(){
	printf("Parsing Error\n");
}

yylex(){
	char c=getchar();
	if(isalpha(c))
		return letter;
	else if(isdigit(c))
		return number;
	return c;
}

int main(){
	if(yyparse())
		printf("Invalid Variable\n");
	else
		printf("Valid Variable\n");
	return 1;
}
