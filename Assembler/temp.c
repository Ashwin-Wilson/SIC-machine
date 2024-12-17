#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char trec[100];
void main(){
	char  ch[] = "*100000";
//	strcat(trec, "T^");
//	strcat(trec, ch);
	sprintf(trec, "T^%s", ch);
	printf("%s", trec);
	int i=0;
	
	while (i<5){
		sprintf(trec + strlen(trec), "^nothing^%s", ch);
		printf("\n%s", trec);
		i++;
	}
	printf("\n%s", trec);
	
	strcpy(ch, ch+1);
	printf("\n%d", atoi(ch));
	
	FILE *fp1  = fopen("symtab.txt", "r");
	
	char sym[10], saddr[100];
	fscanf(fp1, "%s%s", sym, saddr);
	printf("\n%s\t%s", sym, saddr);

	fscanf(fp1, "%s%s", sym, saddr);
	printf("\n%s\t%s", sym, saddr);
	
	fseek(fp1, -1, SEEK_SET);
	fscanf(fp1, "%s%s", sym, saddr);
	printf("\n%s\t%s", sym, saddr);
	
	char trec[100];
	//char saddr[100];
	
	sprintf(saddr, "*14");
	int locctr = 2012;
	sprintf(trec, "T^000000^##^20####");
	printf("\n%s", trec);
	int len =  atoi(strcpy(saddr, saddr+1)) + strlen(trec);
	sprintf(trec + len,"%d", locctr );
	printf("\n%s", trec);
	
	strcpy(saddr + );
	
}














