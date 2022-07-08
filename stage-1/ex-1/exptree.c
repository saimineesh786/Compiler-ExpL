int k=-1;
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

int getreg(){
	k++;
	return k;
}

void freereg(){
	if(k==-1)
		return;
	k--;
}

int AST_Eval(FILE *fp,tnode *tn){
	if(tn->op==NULL){
		int p=getreg();
		fprintf(fp,"MOV R%d,%d\n",p,tn->val);
		return p;
	}
	int l=AST_Eval(fp,tn->left),r=AST_Eval(fp,tn->right);
	if(l>r){
		int t=l;
		l=r;
		r=l;
	}
	switch(*(tn->op)){
		case '+' : fprintf(fp,"ADD R%d,R%d\n",l,r);freereg();
		break;
		case '-' : fprintf(fp,"SUB R%d,R%d\n",l,r);freereg();
		break;
		case '*' : fprintf(fp,"MUL R%d,R%d\n",l,r);freereg();
		break;
		case '/' : fprintf(fp,"DIV R%d,R%d\n",l,r);freereg();
		break;
	}
	return l;
}

void codegen(tnode *tn){
	FILE *fp=fopen("ex1.xsm","w");
	fprintf(fp,"%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",0,2056,0,0,0,0,0,0);
	int r=AST_Eval(fp,tn);
	fprintf(fp,"MOV SP,4095\n");
	fprintf(fp,"PUSH R%d\n",r);
	freereg();
	int p=getreg();
	fprintf(fp,"MOV R%d,5\n",p);
	fprintf(fp,"PUSH R%d\n",p);
	fprintf(fp,"MOV R%d,-2\n",p);
	fprintf(fp,"PUSH R%d\n",p);
	fprintf(fp,"MOV R%d,[4096]\n",p);
	fprintf(fp,"PUSH R%d\n",p);
	fprintf(fp,"PUSH R%d\n",p);
	fprintf(fp,"PUSH R%d\n",p);
	fprintf(fp,"INT 7\n");
	fprintf(fp,"POP R%d\n",p);
	fprintf(fp,"POP R%d\n",p);
	fprintf(fp,"POP R%d\n",p);
	fprintf(fp,"POP R%d\n",p);
	fprintf(fp,"POP R%d\n",p);
	
	fprintf(fp,"MOV R%d,10\n",p);
	fprintf(fp,"PUSH R%d\n",p);
	fprintf(fp,"PUSH R%d\n",p);
	fprintf(fp,"PUSH R%d\n",p);
	fprintf(fp,"PUSH R%d\n",p);
	fprintf(fp,"PUSH R%d\n",p);
	fprintf(fp,"INT 10\n");
	fprintf(fp,"POP R%d\n",p);
	fprintf(fp,"POP R%d\n",p);
	fprintf(fp,"POP R%d\n",p);
	fprintf(fp,"POP R%d\n",p);
	fprintf(fp,"POP R%d\n",p);
	freereg();
	freereg();
}
