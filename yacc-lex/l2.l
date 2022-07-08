%{
  #include "y.tab.h"
  #include <stdlib.h>
  #include <stdio.h>
%}

character [a-z|A-Z]+
%%

{character} {
	yylval.character = (char *)malloc(sizeof(char)*100);
	strcpy(yylval.character,yytext);
	strcat(yylval.character," ");
	return CHARACTER;
  }

(.|\n)	{return *yytext;}
%%

int yywrap(){
	return 1;
}
