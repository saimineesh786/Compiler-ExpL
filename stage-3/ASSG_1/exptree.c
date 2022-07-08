#define MAX_SYMBOLS 100
#include <string.h>
int k=-1,lb=-1;
int pos=0;
symbol *symbol_head=NULL;
tnode * makeLeafNode(int type,int n,char *var_name){
	tnode *tn=(tnode *)malloc(sizeof(tnode));
	tn->type=type;
	if(var_name==NULL){
		tn->val=n;
		tn->var_name=NULL;
	}
	else{
		int flag=0;
		symbol *sym=symbol_head,*prev=NULL;
		while(sym!=NULL){
			if(strcmp(sym->var_name,var_name)==0){
				flag=1;
				break;
			}
			prev=sym;
			sym=sym->next;
		}
		if(!flag){
			sym=(symbol *)malloc(sizeof(symbol));
			sym->var_name=(char *)malloc(sizeof(char)*50);
			strcpy(sym->var_name,var_name);
			sym->binding=4096+pos;
			sym->next=NULL;
			pos++;
			if(prev==NULL){
				symbol_head=sym;
			}
			else{
				prev->next=sym;
			}
		}
		tn->var_name=sym;
	}
	tn->node_type=0;
	tn->left=tn->right=NULL;
	return tn;
}

void print(tnode *tn){
	if(tn==NULL){
		printf("%d\n",tn->node_type);
		return ;
	}
	print(tn->left);
	print(tn->right);
	printf("%d\n",tn->node_type);
}
tnode * makeConnectorNode(int node_type,tnode *l,tnode *r){
	tnode *tn=(tnode *)malloc(sizeof(tnode));
	tn->node_type=node_type;
	tn->type=-1;
	if((node_type==1)||(node_type==2)||(node_type==3)||(node_type==4)||(node_type==5)){
		if((l->type!=int_type) || (r->type!=int_type)){
			yyerror("Type Mismatch 1");
			exit(1);
		}
		else if(node_type!=5){
			tn->type=int_type;
		}
	}
	else if((node_type==6)||(node_type==7)){
		if(l->type!=int_type){
			yyerror("Type Mismatch 2");
			exit(1);
		}
	}
	else if((node_type==11)||(node_type==12)||(node_type==13)||(node_type==14)||(node_type==15)||(node_type==16)){
		if((l->type!=int_type) || (r->type!=int_type)){
			yyerror("Type Mismatch 3");
			exit(1);
		}
		tn->type=bool_type;
	}
	else if((node_type==18)||(node_type==19)||(node_type==20)){
		if((l->type!=bool_type)){
			yyerror("Type Mismatch 4");
			exit(1);
		}
	}
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

int getLabel(){
	lb++;
	return lb;
}
void swap(int *a,int *b){
	int t=*a;
	*a=*b;
	*b=t;
}

int find(symbol *symb){
	return symb->binding;
}

int AST_Eval(FILE *fp,tnode *tn){
	printf("%d\n",tn->node_type);
	if(tn->node_type==0){
		int p=getreg();
		if(tn->var_name==NULL){
			fprintf(fp,"MOV R%d,%d\n",p,tn->val);
		}
		else{
			fprintf(fp,"MOV R%d,[%d]\n",p,find(tn->var_name));
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
		fprintf(fp,"MOV [%d],R%d\n",find((tn->left)->var_name),q);
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
		fprintf(fp,"MOV R%d,%d\n",p,find((tn->left)->var_name));
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
	else if((tn->node_type>=11)&&(tn->node_type<=16)){
		int p=AST_Eval(fp,tn->left),q=AST_Eval(fp,tn->right);
		if(p>q){
			swap(&p,&q);
		}
		switch(tn->node_type){
			case 11 : fprintf(fp,"LT R%d,R%d\n",p,q);break;
			case 12 : fprintf(fp,"GT R%d,R%d\n",p,q);break;
			case 13 : fprintf(fp,"LE R%d,R%d\n",p,q);break;
			case 14 : fprintf(fp,"GE R%d,R%d\n",p,q);break;
			case 16 : fprintf(fp,"EQ R%d,R%d\n",p,q);break;
			case 15 : fprintf(fp,"NE R%d,R%d\n",p,q);break;
		}
		freereg();
		return p;
	}
	else if(tn->node_type==18){
		int p=AST_Eval(fp,tn->left);
		int z=getLabel(),m=getLabel();
		fprintf(fp,"JZ R%d,L%d\n",p,z);
		AST_Eval(fp,tn->right->left);
		fprintf(fp,"JMP L%d\n",m);
		fprintf(fp,"L%d:\n",z);
		AST_Eval(fp,tn->right->right);
		fprintf(fp,"L%d:\n",m);
		freereg();
	}
	else if(tn->node_type==19){
		int p=AST_Eval(fp,tn->left);
		int z=getLabel();
		fprintf(fp,"JZ R%d,L%d\n",p,z);
		AST_Eval(fp,tn->right);
		fprintf(fp,"L%d:\n",z);
		freereg();
	}
	else if(tn->node_type==20){
		int q=getLabel();
		fprintf(fp,"L%d:\n",q);
		AST_Eval(fp,tn->right);
		int p=AST_Eval(fp,tn->left);
		fprintf(fp,"JNZ R%d,L%d\n",p,q);
		freereg();
	}
}

void codegen(tnode *tn){
	FILE *fp=fopen("ex1.xsm","w");
	fprintf(fp,"%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",0,2056,0,0,0,0,0,0);
	fprintf(fp,"MOV SP,%d\n",4095+pos);
	AST_Eval(fp,tn);
	fclose(fp);
}
