%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "exptree.h"
	#include "exptree.c"
	int yylex(void);
	extern FILE * yyin;
%}

%union{
	struct tnode *no;
}
%type <no> expr NUM program END
%token NUM PLUS MINUS MUL DIV END
%left PLUS MINUS
%left MUL DIV

%%
program	: expr END {$$=$2;codegen($1);printf("\n");exit(1);}
		;
expr		: PLUS expr expr {$$ = makeOperatorNode('+',$2,$3);}
		| MINUS expr expr {$$ = makeOperatorNode('-',$2,$3);}
		| MUL expr expr {$$ = makeOperatorNode('*',$2,$3);}
		| DIV expr expr {$$ = makeOperatorNode('/',$2,$3);}
		| '(' expr ')' {$$=$2;}
		| NUM {$$=$1;}
		; 
%%

int yyerror(char const *s){
	printf("yyerror : %s\n",s);
	return 0;
}

int main(void){
	FILE *fp=fopen("inp_file.expl","r");
	yyin=fp;
	yyparse();
	return 0;
}
