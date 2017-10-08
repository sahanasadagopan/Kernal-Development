#include <stdio.h>
#include <string.h>
void main(){
	char c[50];
	FILE *fp =fopen("file","wb+");
	while(fgets(c,sizeof(c),stdin)){
	fprintf(fp, "%s\n",c );
	
	}
	fclose(fp);
	
}