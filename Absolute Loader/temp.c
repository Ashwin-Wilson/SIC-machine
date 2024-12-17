#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(){

	int straddr, i, j;
	char start[10], line[100], pname[10], name[10];
	FILE *fp = fopen("objcode.txt", "r");
	
	fscanf(fp, "%s", line);
	for(i=2, j=0; line[i] != '^'; i++, j++){
		pname[j] = line[i];
	}
	pname[j] = '\0';
	 
	printf("\nEnter the program name :  ");
	scanf("%s", name);
	 
	if(strcmp(name, pname) == 0){
	 	fscanf(fp, "%s", line);
	 	for(i=2, j=0; i<8; i++, j++){
			start[j] = line[i];
		}
		straddr = atoi(start);
		while(line[0] == 'T'){
			i = 12;
			while(line[i] != '\0'){
				if(line[i] != '^'){
					printf("%d\t%c%c\n", straddr, line[i], line[i+1]);
					i = i+ 2;
					straddr++;
				}else{
					i++;
				}
			}
			fscanf(fp, "%s", line);
		}
		if(line[0] == 'E'){
			fclose(fp);
			exit(0);
		}
	}else{
		printf("\nInvalid program name!");
	}
}
