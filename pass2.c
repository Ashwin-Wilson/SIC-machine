#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int tlen = 0x00;
char trec[100];

void updateTxtRecLen(){
	
	int nibble = tlen % 0x10;	
	if (nibble < 10) 
    		trec[10] = '0' + nibble; 
	else 
	    trec[10] = 'A' + (nibble - 10); 
	
	tlen /= 0x10;
	
	nibble = tlen % 0x10;
		
	if (nibble < 10) 
    		trec[9] = '0' + nibble; 
	else 
	    trec[9] = 'A' + (nibble - 10); 
	
	
	tlen = 0x00;
}

void main(){
	
	int straddr;
	char locctr[10], label[10], opcode[10], operand[10], mnemonic[10], code[10], prglen[10], symbol[10], saddr[10];
	
	FILE *fp1 = fopen("intermediate.txt", "r");
	FILE *fp2 = fopen("symtab.txt", "r");
	FILE *fp3 = fopen("optab.txt", "r");
	FILE *fp4 = fopen("objcode.sic", "w");
	FILE *fp5 = fopen("length.txt", "r");
	FILE *fp6 = fopen("listfile.txt", "w");
	
	fscanf(fp5, "%s", prglen);
	
	fscanf(fp1, "%s%s%s%s", locctr, label, opcode, operand);
	fprintf(fp6, "%s\t%s\t%s\t%s", locctr, label, opcode, operand);
	
	if(strcmp(opcode, "START") == 0){
		fprintf(fp4, "H^%s^00%s^0000%s\n", label, operand, prglen);
		straddr = strtol(locctr, NULL, 16);
	}
	
	fscanf(fp1, "%s%s%s%s", locctr, label, opcode, operand);
	sprintf(trec, "T^00%s^##", locctr);
	
	while(strcmp(opcode, "END") != 0 ){
		 while(!feof(fp3)){
		 	fscanf(fp3, "%s%s", mnemonic, code);
		 	if(strcmp(mnemonic, opcode) == 0){
				sprintf(trec + strlen(trec), "^%s", code);
				fprintf(fp6, "\n%s\t%s\t%s\t%s\t%s", locctr, label, opcode, operand, code);
				tlen += 0x03;
		 		break;
		 	}
		 }
		 rewind(fp3);
		  
		 while(!feof(fp2)){
		 	fscanf(fp2, "%s%s", symbol, saddr);
		 	if(strcmp(symbol, operand) == 0){
		 		sprintf(trec + strlen(trec), "%s", saddr);
		 		fprintf(fp6, "%s", saddr);
		 		break;
		 	}
		 	
		 }
		 rewind(fp2);
		 
		 if(strcmp(opcode, "WORD") == 0){
		 	updateTxtRecLen();
		 	if (strcmp (trec , "") != 0)
			 	fprintf(fp4, "%s\n", trec);
		 	sprintf(trec, "T^00%s^03^%06X", locctr, atoi(operand));
		 	fprintf(fp4, "%s\n", trec);
		 	strcpy(trec, "");
			fprintf(fp6, "\n%s\t%s\t%s\t%s\t%06X", locctr, label, opcode, operand,  atoi(operand));	
				
		 }
		 
		 else if(strcmp(opcode, "BYTE") == 0){
		 	updateTxtRecLen();
		 	if (strcmp (trec , "") != 0)
			 	fprintf(fp4, "%s\n", trec);	
		 	int i = 2;
			sprintf(trec, "T^00%s^%02lX^", locctr, (strlen(operand) - 3));
			fprintf(fp6, "\n%s\t%s\t%s\t%s\t", locctr, label, opcode, operand);
			while(operand[i+1] != '\0'){
				sprintf(trec + strlen(trec), "%X", operand[i]);
				fprintf(fp6, "%X", operand[i]);
				i++;
			}
			fprintf(fp4, "%s\n", trec);
			strcpy(trec, "");
		 }
		 fscanf(fp1, "%s%s%s%s", locctr, label, opcode, operand);	
	}
	
	updateTxtRecLen();

	if (strcmp (trec , "") != 0)
		fprintf(fp4, "%s\n", trec);
	fprintf(fp4, "E^%06X\n", straddr);
		
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
	fclose(fp5);
	fclose(fp6);
}