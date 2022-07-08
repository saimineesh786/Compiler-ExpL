tnode * makeLeafNode(int n){
	tnode *tn=(tnode *)malloc(sizeof(tnode));
	tn->op=NULL;
	tn->val=n;
	tn->left=tn->right=NULL;
	return tn;
}

tnode * makeOperatorNode(char c,tnode *l,tnode *r){
	tnode *tn=(tnode *)malloc(sizeof(tnode));
	tn->op=(char *)malloc(sizeof(char));
	*(tn->op)=c;
	tn->left=l;
	tn->right=r;
	return tn;
}

int evaluate(tnode *tn){
	if(tn->op==NULL){
		return tn->val;
	}
	int ltree_val=evaluate(tn->left),rtree_val=evaluate(tn->right);
	switch(*(tn->op)){
		case '+' : return ltree_val + rtree_val;
		case '-' : return ltree_val - rtree_val;
		case '*' : return ltree_val * rtree_val;
		case '/' : return ltree_val / rtree_val; 
	}
}
