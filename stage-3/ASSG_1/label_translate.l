%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "label.c"
	FILE *fp;
	int target_addr;
	int lines=0,pass;
%}

%%
(.)*L[0-9]+[\n]	{if(pass==2){print_target_addr(fp,yytext);fprintf(fp,"\n");}else{lines++;}}
L[0-9]+:[\n]	{if(pass==1){label_entry(yytext,lines);}}
(.)*[\n]		{if(pass==2){fprintf(fp,"%s",yytext);}else{lines++;}}

%%

int yywrap(void){
	return 1;
}

int main(){
	yyin=fopen("ex1.xsm","r");
	pass=1;
	yylex();
	print();
	fp=fopen("ex1_final.xsm","w");
	yyin=fopen("ex1.xsm","r");
	pass=2;
	yylex();
	return 0;
}
