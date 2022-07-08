#define MAX_LABELS 1000
int a[MAX_LABELS];
int pos=0;

int extract_number(char *label){
	char *number=(char *)malloc(sizeof(char)*15);
	int j=0,i=0;
	while(label[j]!='\0'){
		if((label[j]>='0')&&(label[j]<='9')){
			number[i]=label[j];
			i++;
		}
		j++;
	}
	number[i]='\0';
	return atoi(number);;
}
void label_entry(char *label,int lines){
	int lab_num=extract_number(label);
	a[lab_num]=2056+((lines-8)*2);
}

void print(){
	for(int i=0;i<10;i++){
		printf("%d %d\n",i,a[i]);
	}
}
void print_target_addr(FILE *fp,char *label){
	char *number=(char *)malloc(sizeof(char)*15);
	char *h=(char *)malloc(sizeof(char)*30);
	int j=0,i=0;
	while(label[j]!='L'){
		h[i++]=label[j];
		j++;
	}
	h[i]='\0';
	i=0;
	j++;
	while(label[j]!='\0'){
		number[i++]=label[j];
		j++;
	}
	number[i]='\0';
	fprintf(fp,"%s%d",h,a[atoi(number)]);
}
