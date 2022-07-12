int reg=-1;

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
	fprintf(yyin,"PUSH R%d\n",p);
	fprintf(yyin,"MOV R%d,-1\n",p);
	fprintf(yyin,"PUSH R%d\n",p);
	fprintf(yyin,"MOV R%d,%d\n",p,4096+*(root->varName));
	fprintf(yyin,"PUSH R%d\n",p);
	fprintf(yyin,"PUSH R%d\n",p);
	fprintf(yyin,"PUSH R%d\n",p);
	fprintf(yyin,"INT 6\n");
	fprintf(yyin,"POP R%d\n",p);
	fprintf(yyin,"POP R%d\n",p);
	fprintf(yyin,"POP R%d\n",p);
	fprintf(yyin,"POP R%d\n",p);
	fprintf(yyin,"POP R%d\n",p);
	freereg();
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
	freereg();
	freereg();
}

void ifHandler
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
		ifHandler(root);
	}
	else if(root->nodeType==16){
		ifElseHandler(root);
	}	
	else if(root->nodeType==17){	
		whileHandler(root);
	}
	else if(root->nodeType==18){
		codeGeneration(root->left);
		codeGeneration(root->right);
	}
	
}
