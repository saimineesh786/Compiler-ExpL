typedef struct tnode{
	int val;
	char *op;
	struct tnode *left,*right;
}tnode;

tnode * makeLeafNode(int n);

tnode * makeOperatorNode(char c,tnode *l,tnode *r);

int evaluate(tnode *);
