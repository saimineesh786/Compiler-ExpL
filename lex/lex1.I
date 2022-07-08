%{
	#include <stdio.h>
	int lines=0,words=0,chars=0;
%}

newline "\n"
word  [^" "|^"\n"]*
%%
{newline} {lines++;}
{word} {words++;chars+=yyleng;}


%%

int yywrap(){
	printf("lines:%d\nwords:%d\nchars%d\n",lines,words,chars);
	return 1;
}

int main(){
	yyin=stdin;
	yylex();
	return 0;
}
