typedef struct tnode{
	int val;
	char *op;
	struct tnode *left,*right;
}tnode;

tnode * makeLeafNode(int n);

tnode * makeOperatorNode(char c,tnode *l,tnode *r);

int AST_Eval(FILE *,tnode *);

void codegen(tnode *);

int yyerror(char const *);
