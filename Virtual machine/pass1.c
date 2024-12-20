#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(int argc, char *argv[]){

	int locctr, straddr = 0x00, prglen = 0x00;
	char label[10], opcode[10], operand[10], mnemonic[10], code[10];
	FILE *fp1 = fopen(argv[1], "r");
	FILE *fp2 = fopen("optab.txt", "r");
	FILE *fp3 = fopen("intermediate.txt", "w");
	FILE *fp4 = fopen("symtab.txt", "w");
	FILE *fp5 = fopen("length.txt", "w");
	
	fscanf(fp1, "%s%s%s", label, opcode, operand);	

	if(!fp1){
		printf("Error in opening %s!", argv[1]);
	}

	if(strcmp(opcode , "START") == 0){
		straddr = strtol(operand, NULL, 16);
		locctr = straddr;
		
	}else{
		locctr = 0x00;
	}

	fprintf(fp3, "%X\t%s\t%s\t%s\n", locctr, label, opcode, operand);
	fscanf(fp1, "%s%s%s", label, opcode, operand);
	
	while(strcmp(opcode , "END") != 0){
	
		fprintf(fp3, "%04X\t%s\t%s\t%s\n", locctr, label, opcode, operand);
		
		if(strcmp(label, "**") != 0)
			fprintf(fp4, "%s\t%X\n", label, locctr );

		
		
		while(!feof(fp2)){
			fscanf(fp2, "%s%s", mnemonic, code);
			if(strcmp(opcode, mnemonic) == 0){
				locctr += 3;
				prglen += 3;
				break;				
			}			
		}
		rewind(fp2);
		
		if(strcmp(opcode, "WORD") == 0){

			locctr += 3;
		
		}else if(strcmp(opcode, "RESW") == 0){
		
			locctr += (3*atoi(operand));
			
		}else if(strcmp(opcode, "RESB") == 0){

			locctr += atoi(operand);
			
		}else if(strcmp(opcode, "BYTE") == 0){

			locctr += (strlen(operand)-3);
			
		}
		
		fscanf(fp1, "%s%s%s", label, opcode, operand);
	}
	
	fprintf(fp3, "%X\t%s\t%s\t%s\n", locctr, label, opcode, operand);
	fprintf(fp5, "%X\n", prglen);
	
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
	fclose(fp5);

}
