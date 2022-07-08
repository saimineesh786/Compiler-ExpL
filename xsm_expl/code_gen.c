#include <stdio.h>
#include <stdlib.h>

int main(){
	FILE *fp=fopen("target_file.xsm","w");
	fprintf(fp, " %d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",0,2056,0,0,0,0,0,0);
	fprintf(fp, "BRKP\n");
	fprintf(fp, "MOV R0, 3\n");
	fprintf(fp, "MOV R1, 2\n");
	fprintf(fp, "ADD R0, R1\n");
	fprintf(fp, "[4096]=R0\n");
	fprintf(fp, "[4096]=R0\n");
	fprintf(fp, "RET\n");
	return 0;
}
