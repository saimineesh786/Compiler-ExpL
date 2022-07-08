%{
  #include "y.tab.h"
  #include<stdlib.h>
  #include<stdio.h>
%}

number  [0-9]+
operator ['+'|'-'|'*'|'/'|'%']
newline \n
%%

{number} {
	yylval =(YYSTYPE)atoi(yytext);
	return NUMBER;
  }

{operator}	{
	yylval =(YYSTYPE)*yytext;
	return OP;
  }
[\n] {return *yytext;}
%%

int yywrap(){
	return 1;
}
