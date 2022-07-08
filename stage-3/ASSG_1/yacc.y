%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "exptree.h"
	#include "exptree.c"
	int yylex(void);
	extern FILE * yyin;
%}

%union{
	struct tnode *no;
}
%type <no> expr NUM ID READ WRITE program Stmts Stmt ReadStmt WriteStmt AsgStmt IfStmt IfElseStmt WhileStmt WHILE IF ELSE
%token FUN NUM PLUS MINUS MUL DIV READ WRITE ASSIGN ID LT GT LTE GTE NTEQ EQ IF WHILE DO ELSE
%nonassoc LT GT LTE GTE NTEQ EQ
%left PLUS MINUS
%left MUL DIV
%%
program	: FUN '(' ')' '{' Stmts '}' {$$=makeConnectorNode(9,$5,NULL);codegen($$);exit(1);}
		| FUN '(' ')' '{' '}' {$$=makeConnectorNode(10,NULL,NULL);codegen(NULL);exit(1);}
		;
		
Stmts		: Stmts Stmt {$$=makeConnectorNode(8,$1,$2);}
		| Stmt {$$=$1;}
		;
		
Stmt		: AsgStmt {$$=$1;}
		| IfStmt {$$=$1;}
		| IfElseStmt {$$=$1;}
		| WhileStmt {$$=$1;}
		| ReadStmt {$$=$1;}
		| WriteStmt {$$=$1;}
		;
		
ReadStmt	: READ '(' ID ')' ';' {$$ = makeConnectorNode(7,$3,NULL);}
		;
	
WriteStmt	: WRITE '(' expr ')' ';' {$$ = makeConnectorNode(6,$3,NULL);}
		;
		
AsgStmt	: ID ASSIGN expr ';' {$$ = makeConnectorNode(5,$1,$3);}
		;
		 
IfElseStmt	: IF '(' expr ')' '{' Stmts '}' ELSE '{' Stmts '}' {$8 = makeConnectorNode(17,$6,$10);$$=makeConnectorNode(18,$3,$8);}
		;
		
IfStmt		: IF '(' expr ')' '{' Stmts '}' {$$=makeConnectorNode(19,$3,$6);}
		;
		
WhileStmt	: DO '{' Stmts '}' WHILE '(' expr ')' ';' {$$ = makeConnectorNode(20,$7,$3);}
		;
		
expr		: expr PLUS expr {$$ = makeConnectorNode(1,$1,$3);}
		| expr MINUS expr {$$ = makeConnectorNode(2,$1,$3);}
		| expr MUL expr {$$ = makeConnectorNode(3,$1,$3);}
		| expr DIV expr {$$ = makeConnectorNode(4,$1,$3);}
		| '(' expr ')' {$$=$2;}
		| expr LT expr {$$ = makeConnectorNode(11,$1,$3);}
		| expr GT expr {$$ = makeConnectorNode(12,$1,$3);}
		| expr LTE expr {$$ = makeConnectorNode(13,$1,$3);}
		| expr GTE expr {$$ = makeConnectorNode(14,$1,$3);}
		| expr NTEQ expr {$$ = makeConnectorNode(15,$1,$3);}
		| expr EQ expr {$$ = makeConnectorNode(16,$1,$3);}
		| NUM {$$=$1;}
		| ID {$$=$1;}
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
