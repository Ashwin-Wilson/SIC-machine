#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct symtab{
	char symbol[10], saddr[10];
}st[20];

int slen = 0;

int findsym(char key[]){

	for(int i=0;i<slen;i++){
		if(strcmp(key, st[i].symbol) == 0){
			return i;
		}
	}
	return -1;
}



void main(){
	FILE *fp1 = fopen("input.txt", "r");
	FILE *fp2 = fopen("optab.txt", "r");
	FILE *fp3 = fopen("listfile.txt", "w");
	FILE *fp4 = fopen("symtab.txt", "w+");
	FILE *fp5 = fopen("objcode.txt", "w");
	
	int locctr, straddr = 0, tlen = 0;
	char trec[100], hrec[100], label[10], opcode[10], operand[10], mnemonic[10], code[10];
	
	fscanf(fp1, "%s%s%s", label, opcode, operand);	

	if(strcmp(opcode , "START") == 0){
		sprintf(hrec , "H^%s^00%s", label, operand);
		straddr = atoi(operand);
		locctr = straddr;
		
	}else{
		locctr = 0;
	}
	
	sprintf(trec, "T^00%s^##", operand);
	fscanf(fp1, "%s%s%s", label, opcode, operand);	

	while(strcmp(opcode, "END") != 0){
		int i = 0, tlocctr = locctr ; // temp locctr
		if(strcmp(label, "**") != 0){
		
			i = findsym(label);
			if(i != -1){ // if symbol found
				if(st[i].saddr[0] == '*'){ // if symbol address is null
					
					for(int j=(atoi(strcpy(st[i].saddr, st[i].saddr + 1)) + 3), k=0; k<4; k++, j--){ // rewritting the symbol address to objcode.
						trec[j] = (tlocctr % 10) + '0';
						tlocctr /= 10;
					}
					sprintf(st[i].saddr, "%d", locctr);
				}
			}else{ // if symbol not found
				strcpy(st[slen].symbol, label);
				sprintf(st[slen++].saddr, "%d", locctr);
			}
		}
		
		
		while(!feof(fp2)){
			int j = 0;
			fscanf(fp2, "%s%s", mnemonic, code);
	
			if(strcmp(mnemonic, opcode) == 0){
				sprintf(trec + strlen(trec), "^%s", code);
				locctr += 3; // for instruction with opcode
				tlen += 6;
				j = findsym(operand);
				
				if(j != -1){ // symbol found
				
					if(st[j].saddr[0] == '*'){ // symbol address is null
						sprintf(trec + strlen(trec), "####");
					}
				}else{ //symbol not found
					strcpy(st[slen].symbol, operand);
					sprintf(st[slen++].saddr, "*%ld", strlen(trec));
					sprintf(trec + strlen(trec), "####");
				}
			}			
		}
		rewind(fp2);	
		
		if(strcmp(opcode, "RESW") == 0){
			
			locctr += (3 * atoi(operand));
		
		}else if(strcmp(opcode, "RESB") == 0){
		
			locctr += atoi(operand);
		
		}else if(strcmp(opcode, "WORD") == 0){
		
			sprintf(trec + strlen(trec), "^%06X", atoi(operand));
			locctr += 3;
			tlen += 6;
		
		}else if(strcmp(opcode, "BYTE") == 0){
			
			sprintf(trec + strlen(trec), "^");
			for(int k=2; operand[k+1] != '\0';k++){
				sprintf(trec + strlen(trec), "%X", operand[k]);
				tlen++;
			}
			locctr += (strlen(operand) - 3);
		
		}
		
		fscanf(fp1, "%s%s%s", label, opcode, operand);	
	}
	
	tlen /= 2;
	tlen++;
	trec[10] = (tlen % 10) + '0';
	tlen /= 10;
	trec[9] = (tlen % 10) + '0';
	
	sprintf(hrec + strlen(hrec), "^%d", (locctr - straddr));
	fprintf(fp5, "%s\n%s\nE^%06d\n", hrec, trec, straddr);
	
	
	for(int k=0; k<slen;k++){
		printf("\n%s\t%s", st[k].symbol, st[k].saddr);
	}
	
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
	fclose(fp5);
}
