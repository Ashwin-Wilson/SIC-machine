#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void strslice(char* dest, char *src, int idx){
	int i, j;
	for(j=0, i=idx; (src[i] != '^') && (src[i] != '\0'); i++, j++){
		dest[j] = src[i];
	}
	dest[j] = '\0';
}

void binconvert(char *bin, char *bitmask){

	//printf("\n%ld", strlen(bitmask));
	strcpy(bin, "");
	for(int i=0;i<strlen(bitmask);i++){
		switch(bitmask[i]){
			case '0':
				strcat(bin, "0000");
				break;
			case '1': 
				strcat(bin, "0001");
				break;
			case '2': 
				strcat(bin, "0010");
				break;
			case '3': 
				strcat(bin, "0011");
				break;
			case '4': 
				strcat(bin, "0100");
				break;
			case '5': 
				strcat(bin, "0101");
				break;
			case '6': 
				strcat(bin, "0110");
				break;
			case '7': 
				strcat(bin, "0111");
				break;
			case '8': 
				strcat(bin, "1000");
				break;
			case '9': 
				strcat(bin, "1001");
				break;
			case 'A': 
				strcat(bin, "1010");
				break;
			case 'B': 
				strcat(bin, "1011");
				break;
			case 'C': 
				strcat(bin, "1100");
				break;
			case 'D': 
				strcat(bin, "1101");
				break;
			case 'E': 
				strcat(bin, "1110");
				break;
			case 'F': 
				strcat(bin, "1111");
				break;
			default:
				printf("\nInvalid symbol");
				//exit(0);
		}
	}
}

void main(){
	
	int straddr = 0, raddr;
	char line[100], start[10], bitmask[10], bin[10], pname[100], objcode[10];
	
	FILE *fp = fopen("objcode.txt", "r");
	
	printf("Enter starting address :  ");
	scanf("%X", &raddr);
	
	fscanf(fp, "%s", line);
	
	if(line[0] == 'H'){
		
		strslice(pname, line, 2);
		printf("prg name :  %s\n\n", pname);
		fscanf(fp, "%s", line);
		
		while(line[0] != 'E'){
		
			if(line[0] == 'T'){
				strslice(start, line, 2);
				straddr = strtol(start,NULL,16);
				straddr += raddr;
				strslice(bitmask, line, 12);
				binconvert(bin, bitmask);
				
				for(int i=16, j=0; (bin[j] != '\0') && (i<strlen(line)); i += 7, j++){
					strslice(objcode, line, i);
					if(bin[j] == '1'){
						printf("%X\t%c%c", straddr, objcode[0], objcode[1]);
						strslice(objcode, objcode, 2);
						printf("%lX\n", strtol(objcode,NULL,16) + raddr);
						
					}else{
						printf("%X\t%s\n", straddr, objcode);
					}
					straddr += 3;
				}
			}
			fscanf(fp, "%s", line);
		}
		
	}else{
		printf("\nInvalid record format!\n");
		exit(0);
	}
	
	fclose(fp);
}
