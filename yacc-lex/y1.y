/* YACC Auxiliary declarations*/

/* YACC Declarations*/

%union
{
	char *character;
};

%token CHARACTER

%type <character> CHARACTER
%left '+'
%left '*'
%%

start	: expr '\n' {printf("\n");exit(1);}
	;
expr	: expr '+' expr {printf("+ ");}
     	| expr '*' expr {printf("* ");}
     	| '(' expr ')' 
     	| CHARACTER {printf("%s ",$<character>1);}
     	;

%%


int yyerror()
{
	printf("Error");
}


/* Auxiliary functions */
int main(){
	yyparse();
	return 1;
}
