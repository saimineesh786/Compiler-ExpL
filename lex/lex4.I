%{
	#include <stdio.h>
	int slc=1,mlc=1;
%}

slc "//"(.)*
mlc "/*"([^"*"]*|"*"[^"/"])*"*/"
%%
{slc} {printf("%d:%s\n",slc,yytext);slc++;}
{mlc} {printf("%d:%s\n",mlc,yytext);mlc++;}
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
