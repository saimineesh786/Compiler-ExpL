tnode * createConnectorNode(int nodeType,tnode *stmts,tnode *stmt){
	tnode *tn=(tnode *)malloc(sizeof(tnode));
	tn->nodeType=nodeType;
	tn->left=stmts,tn->right=stmt;
	return tn;
}

tnode * createIONode(int nodeType,tnode *Location){
	tnode *tn=(tnode *)malloc(sizeof(tnode));
	if(expr->type!=int_type){
		yyerror("TYPE MISMATCH 1 ERROR\n");
		exit(1);
	}
	tn->nodeType=nodeType;
	tn->left=Location,tn->right=NULL;
	return tn;
}

tnode * createAssignmentNode(int nodeType,tnode *id.tnode *expr){
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
