int k=-1;
tnode * makeLeafNode(int type,int n,char *var_name){
	tnode *tn=(tnode *)malloc(sizeof(tnode));
	tn->type=type;
	if(type==0){
		tn->val=n;
	}
	else if(type==1){
		tn->var_name=(char *)malloc(sizeof(char));
		*(tn->var_name)=var_name[0];
	}
	tn->node_type=0;
	tn->left=tn->right=NULL;
	return tn;
}

tnode * makeConnectorNode(int node_type,tnode *l,tnode *r){
	tnode *tn=(tnode *)malloc(sizeof(tnode));
	tn->node_type=node_type;
	if((node_type==1)||(node_type==2)||(node_type==3)||(node_type==4)||(node_type==5)||(node_type==8)){
		tn->left=l;
		tn->right=r;
	}
	else if((node_type==6)||(node_type==7)||(node_type==9)){
		tn->left=l;
		tn->right=NULL;
	}
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

void swap(int *a,int *b){
	int t=*a;
	*a=*b;
	*b=t;
}
int AST_Eval(FILE *fp,tnode *tn){
	printf("%d\n",tn->node_type);
	if(tn->node_type==0){
		int p=getreg();
		if(tn->type==0){
			fprintf(fp,"MOV R%d,%d\n",p,tn->val);
		}
		else if(tn->type==1){
			fprintf(fp,"MOV R%d,[%d]\n",p,4096+*(tn->var_name)-'a');
		}
		return p;
	}
	else if(tn->node_type==1){
		int p=AST_Eval(fp,tn->left),q=AST_Eval(fp,tn->right);
		if(p>q){
			swap(&p,&q);
		}
		fprintf(fp,"ADD R%d,R%d\n",p,q);
		freereg();
		return p;
	}
	else if(tn->node_type==2){
		int p=AST_Eval(fp,tn->left),q=AST_Eval(fp,tn->right);
		if(p>q){
			swap(&p,&q);
		}
		fprintf(fp,"SUB R%d,R%d\n",p,q);
		freereg();
		return p;
	}
	else if(tn->node_type==3){
		int p=AST_Eval(fp,tn->left),q=AST_Eval(fp,tn->right);
		if(p>q){
			swap(&p,&q);
		}
		fprintf(fp,"MUL R%d,R%d\n",p,q);
		freereg();
		return p;
	}
	else if(tn->node_type==4){
		int p=AST_Eval(fp,tn->left),q=AST_Eval(fp,tn->right);
		if(p>q){
			swap(&p,&q);
		}
		fprintf(fp,"DIV R%d,R%d\n",p,q);
		freereg();
		return p;
	}
	else if(tn->node_type==5){
		int q=AST_Eval(fp,tn->right);
		fprintf(fp,"MOV [%d],R%d\n",4096+*((tn->left)->var_name)-'a',q);
		freereg();
	}
	else if(tn->node_type==6){
		int p=getreg();
		int q=AST_Eval(fp,tn->left);
		fprintf(fp,"MOV R%d,5\n",p);
		fprintf(fp,"PUSH R%d\n",p);
		fprintf(fp,"MOV R%d,-2\n",p);
		fprintf(fp,"PUSH R%d\n",p);
		fprintf(fp,"MOV R%d,R%d\n",p,q);
		fprintf(fp,"PUSH R%d\n",p);
		fprintf(fp,"PUSH R%d\n",p);
		fprintf(fp,"PUSH R%d\n",p);
		fprintf(fp,"INT 7\n");
		fprintf(fp,"POP R%d\n",p);
		fprintf(fp,"POP R%d\n",p);
		fprintf(fp,"POP R%d\n",p);
		fprintf(fp,"POP R%d\n",p);
		fprintf(fp,"POP R%d\n",p);
		freereg();
		freereg();
	}
	else if(tn->node_type==7){
		int p=getreg();
		fprintf(fp,"MOV R%d,7\n",p);
		fprintf(fp,"PUSH R%d\n",p);
		fprintf(fp,"MOV R%d,-1\n",p);
		fprintf(fp,"PUSH R%d\n",p);
		fprintf(fp,"MOV R%d,%d\n",p,4096+*((tn->left)->var_name)-'a');
		fprintf(fp,"PUSH R%d\n",p);
		fprintf(fp,"PUSH R%d\n",p);
		fprintf(fp,"PUSH R%d\n",p);
		fprintf(fp,"INT 6\n");
		fprintf(fp,"POP R%d\n",p);
		fprintf(fp,"POP R%d\n",p);
		fprintf(fp,"POP R%d\n",p);
		fprintf(fp,"POP R%d\n",p);
		fprintf(fp,"POP R%d\n",p);
		freereg();
	}
	else if(tn->node_type==8){
		AST_Eval(fp,tn->left);
		AST_Eval(fp,tn->right);
	}
	else if((tn->node_type==9)||(tn->node_type==10)){
		if(tn->node_type==9){
			AST_Eval(fp,tn->left);
		}
		int p=getreg();
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
	}
	
}

void codegen(tnode *tn){
	FILE *fp=fopen("ex1.xsm","w");
	fprintf(fp,"%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",0,2056,0,0,0,0,0,0);
	fprintf(fp,"MOV SP,4121\n");
	AST_Eval(fp,tn);
}
