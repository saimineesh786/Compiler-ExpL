%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "helper.h"
	#include "helper.c"
	int yylex(void);
%}

%union{
	struct tnode *no;
}
%type <no> Program expr Stmts Stmt ReadStmt WriteStmt AssgStmt IfStmt WhileStmt
%token NUM PLUS MINUS MUL DIV LT GT LTE GTE NTEQ EQ READ WRITE ASSIGN ID IF WHILE DO ELSE ENDIF ENDWHILE
%nonassoc LT GT LTE GTE NTEQ EQ
%left PLUS MINUS
%left MUL DIV
%%
Program	: Stmts {codeGeneration($$);exit(0);}
		;
Stmts		: Stmts Stmt {$$=createConnectorNode(18,$1,$2);}
		| Stmt {$$=$1;}
		;
Stmt		: AssgStmt {$$=$1;}
		| IfStmt {$$=$1;}
		| WhileStmt {$$=$1;}
		| ReadStmt {$$=$1;}
		| WriteStmt {$$=$1;}
		;
ReadStmt	: READ '(' ID ')' ';' {$$ = createIONode(13,$<no>3);}
		;
WriteStmt	: WRITE '(' expr ')' ';' {$$ = createIONode(14,$3);}
		;
AssgStmt	: ID ASSIGN expr ';' {$$ = createAssignmentNode(12,$<no>1,$3);}
		;		 
IfStmt		: IF '(' expr ')' '{' Stmts '}' ELSE '{' Stmts '}' ENDIF ';' {$$ = createIfElseNode(16,$3,$6,$10);}
		| IF '(' expr ')' '{' Stmts '}' ENDIF ';' {$$ = createIfNode(15,$3,$6);}
		;	
WhileStmt	: WHILE '(' expr ')' DO Stmts	ENDWHILE ';' {$$ = createWhileNode(17,$3,$6);}
		;
expr		: expr PLUS expr {$$ = createArithmeticNode(2,$1,$3);}
		| expr MINUS expr {$$ = createArithmeticNode(3,$1,$3);}
		| expr MUL expr {$$ = createArithmeticNode(4,$1,$3);}
		| expr DIV expr {$$ = createArithmeticNode(5,$1,$3);}
		| '(' expr ')' {$$ = $2;}
		| expr LT expr {$$ = createLogicalNode(6,$1,$3);}
		| expr GT expr {$$ = createLogicalNode(7,$1,$3);}
		| expr LTE expr {$$ = createLogicalNode(8,$1,$3);}
		| expr GTE expr {$$ = createLogicalNode(9,$1,$3);}
		| expr EQ expr {$$ = createLogicalNode(10,$1,$3);}
		| expr NTEQ expr {$$ = createLogicalNode(11,$1,$3);}
		| NUM {$$ = $<no>1;}
		| ID {$$ = $<no>1;}
		; 
%%

int yyerror(char const *s){
	printf("yyerror : %s",s);
	return 0;
}

int main(void){
	FILE *fp=fopen("test1.expl","r");
	yyin=fp;
	yyparse();
	return 0;
}
