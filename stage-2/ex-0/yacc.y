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
%type <no> expr NUM ID READ WRITE program slist stmt inpStmt outStmt assgStmt
%token NUM PLUS MINUS MUL DIV BEGINER END READ WRITE ASSIGN ID
%left PLUS MINUS
%left MUL DIV

%%
program	: BEGINER slist END ';' {$$=makeConnectorNode(9,$2,NULL);codegen($$);exit(1);}
		| BEGINER END ';' {$$=makeConnectorNode(10,NULL,NULL);codegen(NULL);exit(1);}
		;
		
slist		: slist stmt {$$=makeConnectorNode(8,$1,$2);}
		| stmt {$$=$1;}
		;
		
stmt		: inpStmt {$$=$1;}
		| outStmt {$$=$1;}
		| assgStmt {$$=$1;}
		;
		
inpStmt	: READ '(' ID ')' ';' {$$ = makeConnectorNode(7,$3,NULL);}
		;
	
outStmt	: WRITE '(' expr ')' ';' {$$ = makeConnectorNode(6,$3,NULL);}
		;
		
assgStmt	: ID ASSIGN expr ';' {$$ = makeConnectorNode(5,$1,$3);}
		;
		 
expr		: expr PLUS expr {$$ = makeConnectorNode(1,$1,$3);}
		| expr MINUS expr {$$ = makeConnectorNode(2,$1,$3);}
		| expr MUL expr {$$ = makeConnectorNode(3,$1,$3);}
		| expr DIV expr {$$ = makeConnectorNode(4,$1,$3);}
		| '(' expr ')' {$$=$2;}
		| NUM {$$=$1;}
		| ID  {$$=$1;}
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
