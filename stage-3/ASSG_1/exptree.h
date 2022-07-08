#define int_type 0
#define bool_type 1

typedef struct symbol{
	char *var_name;
	int binding;
	struct symbol *next;
}symbol;

typedef struct tnode{
	int val;
	int type; // variable - type// const 0 // var 1
	symbol *var_name;
	int node_type;// node -type leaf 0 || + 1 || - 2 || * 3 || / 4 || assign 5 || write 6 || read 7 || stmtconnector  8 || 
	struct tnode *left,*right;
}tnode;

tnode * makeLeafNode(int type,int n,char *var);

tnode * makeTreeNode(int node_type,tnode *l,tnode *r);

int AST_Eval(FILE *,tnode *);

void codegen(tnode *);

int yyerror(char const *);
