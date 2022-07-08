/* YACC Auxiliary declarations*/

/* YACC Declarations*/

%union
{
	char character;
	int integer;

};

%token OP
%token NUMBER

%type <character> OP
%type <integer> NUMBER

%%

expr : expr OP expr '\n' { printf("%c %d %d\n",$<character>2,$<integer>1,$<integer>3);exit(1); }
     | NUMBER        { $<integer>$=$<integer>1; }
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
