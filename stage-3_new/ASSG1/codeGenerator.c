int reg=-1;
int label=-1,whileLabel1,whileLabel2;

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
	fprintf(outFile,"MOV R%d,%d\n",r1,root->val);
	return r1;
}

int variableHandler(tnode *root){
	int r1=getReg();
	fprintf(outFile,"MOV R%d,[%d]\n",r1,4096+*(root->varName) - 'a');
	return r1;
}

int arithmeticOperatorHandler(tnode *root,int r1,int r2){
	if(r1>r2){
		swap(&r1,&r2);
	}
	int nodeType=root->nodeType;
	switch(nodeType){
		case 2:	fprintf(outFile,"ADD R%d,R%d\n",r1,r2);	break;	
		case 3:	fprintf(outFile,"SUB R%d,R%d\n",r1,r2);	break;	 
		case 4:	fprintf(outFile,"MUL R%d,R%d\n",r1,r2);	break;	
		case 5:	fprintf(outFile,"DIV R%d,R%d\n",r1,r2);	break;	
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
		case 6:	fprintf(outFile,"LT R%d,R%d\n",r1,r2);		break;	
		case 7:	fprintf(outFile,"GT R%d,R%d\n",r1,r2);		break;	 
		case 8:	fprintf(outFile,"LE R%d,R%d\n",r1,r2);		break;	
		case 9:	fprintf(outFile,"GE R%d,R%d\n",r1,r2);		break;	
		case 10:	fprintf(outFile,"EQ R%d,R%d\n",r1,r2);		break;	
		case 11:	fprintf(outFile,"NE R%d,R%d\n",r1,r2);		break;	
	}
	freeReg();
	return r1;
}

void assignHandler(tnode *root,int r1){
	fprintf(outFile,"MOV [%d],R%d\n",4096+*(root->left->varName)-'a',r1);
	freeReg();
}

void readHandler(tnode *root){
	int r1=getReg();
	fprintf(outFile,"MOV R%d,7\n",r1);
	fprintf(outFile,"PUSH R%d\n",r1);
	fprintf(outFile,"MOV R%d,-1\n",r1);
	fprintf(outFile,"PUSH R%d\n",r1);
	fprintf(outFile,"MOV R%d,%d\n",r1,4096+*(root->left->varName)-'a');
	fprintf(outFile,"PUSH R%d\n",r1);
	fprintf(outFile,"PUSH R%d\n",r1);
	fprintf(outFile,"PUSH R%d\n",r1);
	fprintf(outFile,"INT 6\n");
	fprintf(outFile,"POP R%d\n",r1);
	fprintf(outFile,"POP R%d\n",r1);
	fprintf(outFile,"POP R%d\n",r1);
	fprintf(outFile,"POP R%d\n",r1);
	fprintf(outFile,"POP R%d\n",r1);
	freeReg();
}

void writeHandler(tnode *root,int r1){
	int r2=getReg();
	fprintf(outFile,"MOV R%d,5\n",r2);
	fprintf(outFile,"PUSH R%d\n",r2);
	fprintf(outFile,"MOV R%d,-2\n",r2);
	fprintf(outFile,"PUSH R%d\n",r2);
	fprintf(outFile,"MOV R%d,R%d\n",r2,r1);
	fprintf(outFile,"PUSH R%d\n",r2);
	fprintf(outFile,"PUSH R%d\n",r2);
	fprintf(outFile,"PUSH R%d\n",r2);
	fprintf(outFile,"INT 7\n");
	fprintf(outFile,"POP R%d\n",r2);
	fprintf(outFile,"POP R%d\n",r2);
	fprintf(outFile,"POP R%d\n",r2);
	fprintf(outFile,"POP R%d\n",r2);
	fprintf(outFile,"POP R%d\n",r2);
	freeReg();
	freeReg();
}

void ifHandler(tnode *root,int r1){
	int l=getLabel();
	fprintf(outFile,"JZ R%d,L%d\n",r1,l);
	codeGeneration(root->right);
	fprintf(outFile,"L%d:\n",l);
	freeReg();
}

void ifElseHandler(tnode *root,int r1){
	int l1=getLabel(),l2=getLabel();
	fprintf(outFile,"JZ R%d,L%d\n",r1,l1);
	codeGeneration(root->right->left);
	fprintf(outFile,"JMP L%d\n",l2);
	fprintf(outFile,"L%d:\n",l1);
	codeGeneration(root->right->right);
	fprintf(outFile,"L%d:\n",l2);
	freeReg();
}

void whileHandler(tnode *root){
	int l1=getLabel(),l2=getLabel();
	whileLabel1=l1,whileLabel2=l2;
	fprintf(outFile,"L%d:\n",l1);
	int r1=codeGeneration(root->left);
	fprintf(outFile,"JZ R%d,L%d\n",r1,l2);
	codeGeneration(root->right);
	fprintf(outFile,"JMP L%d\n",l1);
	fprintf(outFile,"L%d:\n",l2);
	freeReg();
}

void breakHandler(){
	fprintf(outFile,"JMP L%d\n",whileLabel2);
}

void continueHandler(){
	fprintf(outFile,"JMP L%d\n",whileLabel1);
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
		whileHandler(root);
	}
	else if(root->nodeType==18){
		codeGeneration(root->left);
		codeGeneration(root->right);
	}
	else if(root->nodeType==19){
		codeGeneration(root->left);
		codeGeneration(root->right);
	}
	else if(root->nodeType==20){
		breakHandler();
	}
	else if(root->nodeType==21){
		continueHandler();
	}
}

void codeGen(tnode *root){
	outFile=fopen("tmp.xsm","w");
	fprintf(outFile,"%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",0,2056,0,0,0,0,0,0);
	fprintf(outFile,"MOV SP,%d\n",4095+26);
	codeGeneration(root);
	fprintf(outFile,"INT 10\n");
}
