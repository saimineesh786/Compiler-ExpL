tnode * createConnectorNode(int nodeType,tnode *stmts,tnode *stmt){
	tnode *tn=(tnode *)malloc(sizeof(tnode));
	tn->nodeType=nodeType;
	tn->left=stmts,tn->right=stmt;
	return tn;
}

tnode * createIONode(int nodeType,tnode *Location){
	tnode *tn=(tnode *)malloc(sizeof(tnode));
	if(Location->type!=int_type){
		yyerror("TYPE MISMATCH 1 ERROR\n");
		exit(1);
	}
	tn->nodeType=nodeType;
	tn->left=Location,tn->right=NULL;
	return tn;
}

tnode * createAssignmentNode(int nodeType,tnode *id,tnode *expr){
	tnode *tn=(tnode *)malloc(sizeof(tnode));
	if(expr->type!=int_type){
		yyerror("TYPE MISMATCH 1 ERROR\n");
		exit(1);
	}
	tn->nodeType=nodeType;
	tn->left=id,tn->right=expr;
	return tn;
}

tnode * createIfElseNode(int nodeType,tnode *expr,tnode *ifStmts,tnode *elseStmts){
	tnode *tn=(tnode *)malloc(sizeof(tnode));
	if(expr->type!=bool_type){
		yyerror("TYPE MISMATCH 2 ERROR\n");
		exit(1);
	}
	tn->nodeType=nodeType;
	tnode *stmts=(tnode *)malloc(sizeof(tnode));
	stmts->left=ifStmts,stmts->right=elseStmts;
	tn->left=expr,tn->right=stmts;
	return tn;
}

tnode * createIfNode(int nodeType,tnode *expr,tnode *stmts){
	tnode *tn=(tnode *)malloc(sizeof(tnode));
	if(expr->type!=bool_type){
		yyerror("TYPE MISMATCH 2 ERROR\n");
		exit(1);
	}
	tn->nodeType=nodeType;
	tn->left=expr,tn->right=stmts;
	return tn;
}

tnode * createWhileNode(int nodeType,tnode *expr,tnode *stmts){
	tnode *tn=(tnode *)malloc(sizeof(tnode));
	if(expr->type!=bool_type){
		yyerror("TYPE MISMATCH 2 ERROR\n");
		exit(1);
	}
	tn->nodeType=nodeType;
	tn->left=expr,tn->right=stmts;
	return tn;
}

tnode * createArithmeticNode(int nodeType,tnode *expr1,tnode *expr2){
	tnode *tn=(tnode *)malloc(sizeof(tnode));
	if(expr1->type!=int_type || expr1->type!=expr2->type){
		yyerror("TYPE MISMATCH 1 ERROR\n");
		exit(1);
	}
	tn->type=int_type,tn->nodeType=nodeType;
	tn->left=expr1,tn->right=expr2;
	return tn;
}

tnode * createLogicalNode(int nodeType,tnode *expr1,tnode *expr2){
	tnode *tn=(tnode *)malloc(sizeof(tnode));
	if(expr1->type!=int_type || expr1->type!=expr2->type){
		yyerror("TYPE MISMATCH 1 ERROR\n");
		exit(1);
	}
	tn->type=bool_type,tn->nodeType=nodeType;
	tn->left=expr1,tn->right=expr2;
	return tn;
}

tnode * createLeafNode(int val,int type,char *varName,int nodeType){
	tnode *tn=(tnode *)malloc(sizeof(tnode));
	tn->val=val,tn->type=type,tn->varName=varName,tn->left=tn->right=NULL;
	return tn;
}

int reg=-1;
int label=-1;

int getLabel(){
	return ++label;
}

int getReg(){
	return ++reg;
}

void freeReg(){
	if(reg==-1)
		return;
	--reg;
}

void swap(int *a,int *b){
	int t=*a;
	*a=*b;
	*b=t;
}

int constantHandler(tnode *root){
	int r1=getReg();
	fprintf(yyin,"MOV R%d,%d\n",r1,root->val);
	return r1;
}

int variableHandler(tnode *root){
	int r1=getReg();
	fprintf(yyin,"MOV R%d,[%d]\n",r1,4096+*(root->varName) - 'a');
	return r1;
}

int arithmeticOperatorHandler(tnode *root,int r1,int r2){
	if(r1>r2){
		swap(&r1,&r2);
	}
	int nodeType=root->nodeType;
	switch(nodeType){
		case 2:	fprintf(yyin,"ADD R%d,%d\n",r1,r2);	break;	
		case 3:	fprintf(yyin,"SUB R%d,%d\n",r1,r2);	break;	 
		case 4:	fprintf(yyin,"MUL R%d,%d\n",r1,r2);	break;	
		case 5:	fprintf(yyin,"DIV R%d,%d\n",r1,r2);	break;	
	}
	freeReg();
	return r1;
}

int logicalOperatorHandler(tnode *root,int r1,int r2){
	if(r1>r2){
		swap(&r1,&r2);
	}
	int nodeType=root->nodeType;
	switch(nodeType){
		case 6:	fprintf(yyin,"LT R%d,%d\n",r1,r2);	break;	
		case 7:	fprintf(yyin,"GT R%d,%d\n",r1,r2);	break;	 
		case 8:	fprintf(yyin,"LE R%d,%d\n",r1,r2);	break;	
		case 9:	fprintf(yyin,"GE R%d,%d\n",r1,r2);	break;	
		case 10:	fprintf(yyin,"EQ R%d,%d\n",r1,r2);	break;	
		case 11:	fprintf(yyin,"NE R%d,%d\n",r1,r2);	break;	
	}
	freeReg();
	return r1;
}

void assignHandler(tnode *root,int r1){
	fprintf(yyin,"MOV [%d],R%d\n",4096+*(root->varName)-'a',r1);
	freeReg();
}

void readHandler(tnode *root){
	int r1=getReg();
	fprintf(yyin,"MOV R%d,7\n",r1);
	fprintf(yyin,"PUSH R%d\n",r1);
	fprintf(yyin,"MOV R%d,-1\n",r1);
	fprintf(yyin,"PUSH R%d\n",r1);
	fprintf(yyin,"MOV R%d,%d\n",r1,4096+*(root->varName));
	fprintf(yyin,"PUSH R%d\n",r1);
	fprintf(yyin,"PUSH R%d\n",r1);
	fprintf(yyin,"PUSH R%d\n",r1);
	fprintf(yyin,"INT 6\n");
	fprintf(yyin,"POP R%d\n",r1);
	fprintf(yyin,"POP R%d\n",r1);
	fprintf(yyin,"POP R%d\n",r1);
	fprintf(yyin,"POP R%d\n",r1);
	fprintf(yyin,"POP R%d\n",r1);
	freeReg();
}

void writeHandler(tnode *root,int r1){
	int r2=getReg();
	fprintf(yyin,"MOV R%d,5\n",r2);
	fprintf(yyin,"PUSH R%d\n",r2);
	fprintf(yyin,"MOV R%d,-2\n",r2);
	fprintf(yyin,"PUSH R%d\n",r2);
	fprintf(yyin,"MOV R%d,R%d\n",r2,r1);
	fprintf(yyin,"PUSH R%d\n",r2);
	fprintf(yyin,"PUSH R%d\n",r2);
	fprintf(yyin,"PUSH R%d\n",r2);
	fprintf(yyin,"INT 7\n");
	fprintf(yyin,"POP R%d\n",r2);
	fprintf(yyin,"POP R%d\n",r2);
	fprintf(yyin,"POP R%d\n",r2);
	fprintf(yyin,"POP R%d\n",r2);
	fprintf(yyin,"POP R%d\n",r2);
	freeReg();
	freeReg();
}

void ifHandler(tnode *root,int r1){
	int l=getLabel();
	fprintf(yyin,"JZ R%d,L%d\n",r1,l);
	codeGeneration(root->right);
	fprintf(yyin,"L%d:\n",l);
	freeReg();
}

void ifElseHandler(tnode *root,int r1){
	int l1=getLabel(),l2=getLabel();
	fprintf(yyin,"JZ R%d,L%d\n",r1,l1);
	codeGeneration(root->left->left);
	fprintf(yyin,"JMP L%d\n",l2);
	fprintf(yyin,"L%d:\n",l1);
	codeGeneration(root->left->right);
	fprintf(yyin,"L%d:\n",l2);
	freeReg();
}

void whileHandler(tnode *root,int r1){
	int l1=getLabel(),l2=getLabel();
	fprintf(yyin,"L%d:\n",l1);
	fprintf(yyin,"JZ R%d,L%d",r1,l2);
	codeGeneration(root->right);
	fprintf(yyin,"JMP L%d\n",l1);
	fprintf(yyin,"L%d:\n",l2);
	freeReg();
}

int codeGeneration(tnode *root){
	
	if(root->nodeType==0){
		return constantHandler(root);
	}
	else if(root->nodeType==1){
		return variableHandler(root);
	}
	else if(root->nodeType>=2 && root->nodeType<=5){
		int r1=codeGeneration(root->left);
		int r2=codeGeneration(root->right);
		return arithmeticOperatorHandler(root,r1,r2);
	}
	else if(root->nodeType>=6 && root->nodeType<=11){
		int r1=codeGeneration(root->left);
		int r2=codeGeneration(root->right);
		return logicalOperatorHandler(root,r1,r2);
	}
	else if(root->nodeType==12){
		int r1=codeGeneration(root->right);
		assignHandler(root,r1);
	}
	else if(root->nodeType==13){
		readHandler(root);
	}
	else if(root->nodeType==14){
		int r1=codeGeneration(root->left);
		writeHandler(root,r1);
	}
	else if(root->nodeType==15){
		int r1=codeGeneration(root->left);
		ifHandler(root,r1);
	}
	else if(root->nodeType==16){
		int r1=codeGeneration(root->left);
		ifElseHandler(root,r1);
	}	
	else if(root->nodeType==17){	
		int r1=codeGeneration(root->left);
		whileHandler(root,r1);
	}
	else if(root->nodeType==18){
		codeGeneration(root->left);
		codeGeneration(root->right);
	}
	
}
