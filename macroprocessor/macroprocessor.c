#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(){

	char label[10], opcode[10], operand[10], name[10];

	FILE *input = fopen("input.txt", "r");
	FILE *output = fopen("output.txt", "w");
	FILE *namtab = fopen("namtab.txt", "w+");
	FILE *argtab = fopen("argtab.txt", "w+");
	FILE *deftab = fopen("deftab.txt", "w+");
	
	fscanf(input, "%s%s%s", label, opcode, operand);
	
	while(strcmp(opcode, "END") != 0){

		if(strcmp(opcode, "MACRO") == 0){	

			fprintf(namtab, "%s\n", label);
			rewind(namtab);
			fprintf(deftab, "%s\t%s\n", label, operand);
			int i=1;

			fscanf(input, "%s%s%s", label, opcode, operand);
			
			while(strcmp(opcode, "MEND") != 0){
				
				fprintf(deftab, "%s\t?%d\n", opcode, i++);
				fscanf(input, "%s%s%s", label, opcode, operand);
			}
			fprintf(deftab, "%s\n", opcode);
			
		}else{
			fscanf(namtab, "%s", name);
			if(strcmp(opcode, name) == 0){
				fprintf(output, "#\t%s\t%s\n", opcode, operand);
				rewind(deftab);
				
				for(int i=0; operand[i] != '\0'; i++){
					if(operand[i] != ','){
						fprintf(argtab, "%c", operand[i]);
					}else{
						fprintf(argtab, "\n");
					}
				}
				
				rewind(argtab);
				
				fscanf(deftab, "%s%s", opcode, operand);
				fscanf(deftab, "%s%s", opcode, operand);
				while(strcmp(opcode, "MEND") != 0){
					fscanf(argtab, "%s", operand);
					fprintf(output, "**\t%s\t%s\n",opcode, operand);
					fscanf(deftab, "%s%s", opcode, operand);
				}
			}else{
				fprintf(output, "%s\t%s\t%s\n", label, opcode, operand);
			}
		}
		
		fscanf(input, "%s%s%s", label, opcode, operand);
	}
	fprintf(output, "**\t%s\t**\n", opcode);
	
	fclose(input);
	fclose(output);
	fclose(namtab);
	fclose(argtab);
	fclose(deftab);
}
