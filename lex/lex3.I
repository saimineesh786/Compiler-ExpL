%{
	#include <stdio.h>
%}

word3 [A-Z](.)(.)
%%
{word3} {printf("%s",yytext);}
<<EOF>> {printf("Parsing Over\n");return 0;}

[\t\n]+
.+
%%

int yywrap(){
	return 1;
}

int main(){
	FILE *fp=fopen("input_file.l","r");
	yyin=fp;
	yylex();
	return 0;
}
