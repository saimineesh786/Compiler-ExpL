%{
	#include <stdio.h>
	int cntdec=0,cntfloat=0;
%}
integer [0-9]+|-[1-9][0-9]*
floating {integer}.[0-9]+
%%
{integer} {cntdec++;}
{floating} {cntfloat++;}
<<EOF>> {printf("%d %d\n",cntdec,cntfloat);return 0;}
%%

int yywrap(){
	return 1;
}

int main(){
	yylex();
	return 0;
}
