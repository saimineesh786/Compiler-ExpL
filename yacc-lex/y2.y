/* YACC Auxiliary declarations*/

/* YACC Declarations*/

%union
{
	char *character;
};

%token CHARACTER

%type <character> CHARACTER '+'
%left '+'
%left '*'
%%

start 	: expr '\n' {printf("%s\n",$<character>1);exit(1);}
	;
expr 	: expr '+' expr {printf("%chi\n",$2->character);$<character>$=(char *)malloc(sizeof(char)*100);strcpy($<character>$,"+ ");strcat($<character>$,$<character>1);strcat($<character>$,$<character>3);}
     	| expr '*' expr {$<character>$=(char *)malloc(sizeof(char)*100);strcpy($<character>$,"* ");strcat($<character>$,$<character>1);strcat($<character>$,$<character>3);}
     	| '(' expr ')' {$<character>$=$<character>2;}
     	| CHARACTER {$<character>$=$<character>1;}
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
