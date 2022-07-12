#define int_type 0
#define bool_type 1
#include <string.h>
int *variables;
FILE * yyin;
typedef struct tnode{
	int val; //  value for constants
	int type; // type of variable
	char *varName; // variable name for variable nodes
	int nodeType;
	/*
		0	-	constant
		1	-	variable
		2	- 	+
		3	-	-
		4	-	*
		5	-	/
		6	-	<
		7	-	>
		8	-	<=
		9	-	>=
		10	-	==
		11	-	!=
		12	-	ASSIGN
		13		READ	
		14	-	WRITE
		15	-	if statement
		16	-	ifElse statement
		17	-	While statement
		18	-	Statement Connector
	*/
	struct tnode *left,*right;
}tnode;

tnode * createLeafNode(int val,int type,char *varName,int nodeType);

tnode * createLogicalNode(int nodeType,tnode *expr1,tnode *expr2);

tnode * createArithmeticNode(int nodeType,tnode *expr1,tnode *expr2);

tnode * createWhileNode(int nodeType,tnode *expr,tnode *stmts);

tnode * createIfNode(int nodeType,tnode *expr,tnode *stmts);

tnode * createIfElseNode(int nodeType,tnode *expr,tnode *ifStmts,tnode *elseStmts);

tnode * createAssignmentNode(int nodeType,tnode *id.tnode *expr);

tnode * createIONode(int nodeType,tnode *Location);

tnode * createConnectorNode(int nodeType,tnode *stmts,tnode *stmt);

int codegen(tnode *);

int yyerror(char const *);
