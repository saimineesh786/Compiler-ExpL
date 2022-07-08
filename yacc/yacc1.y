%{
	#include<stdio.h>
	#include<stdlib.h>
	int levels=0;
%}
%token DIGIT
%left '+'
%left '*'

%%
start 	: ifstmt '\n'	{return ;}
	;
ifstmt	: 'i' 'f' '(' expr ')' '{' ifstmt '}' 'e' 'l' 's' 'e'  '{' ifstmt '}'	{levels++;}
	| 'i' 'f' '(' expr ')' '{' expr '}''e' 'l' 's' 'e' '{' expr '}'	{levels++;}
	| 'i' 'f' '(' expr ')' '{' expr '}'		{levels++;}
	;
expr	: expr '+' expr	
	| expr '*' expr	
	| '(' expr ')'
	| DIGIT	
	;
%%

void yyerror(){
	printf("Parsing Error\n");
}

yylex(){
	char c=getchar();
	if(isdigit(c)){
		return DIGIT;
	}
	return c;
}

int main(){
	if(yyparse()){
		printf("Parsing UnSuccessful\n");
	}	
	else{
		printf("Parsing Successful, number of levels : %d\n",levels);
	}
	return 1;
}
