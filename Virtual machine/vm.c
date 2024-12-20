#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Memory
#define MEMORY_SIZE 1000000 //1MB
unsigned char memory[MEMORY_SIZE];

//Registers
int A, X, L, PC, SW;


//To store a record readed from source file
char record[100];

void strslice( char *dest, char *src, int idx){
	int i, j;
	for( i=idx, j=0; src[i]!='\0' && src[i] != '^'; i++, j++ ){
		dest[j] = src[i];
	}
	dest[j] = '\0';
}

//To print the content of memory, used for debugging
void printMem(){
	char  temp[10];
	strslice(temp, record, 2); // use for getting limit if need for the below loop
	for(int i = 0x2000; i < 0x2020; i++){
		printf("%X\t: %02X\n" ,i, memory[i]);
	}
}


//To fetch from memory
int fetch(int address, int len){
	unsigned int value = 0x00;
	
	for(int i = 0, j = address; i < len; i ++, j++){
		value = value * 0x100;
		value += memory[j];
	}

	return value;
}

//For executing the loaded prgm
void execute(){
	
	char temp[10];
	int prglen, opcode, opaddr;
	unsigned int var = 0;
	FILE *fp = fopen("length.txt", "r");
	
	fscanf(fp, "%s", temp);
	prglen = strtol(temp, NULL, 16);
	
	for(int i=0x00; i<prglen; i+=0x03){
		opcode = fetch(PC, 1);
		PC++;
		switch(opcode){
			case 0x00: //LDA
				opaddr = fetch(PC, 2);
				PC += 2;
				A = fetch(opaddr, 3);
				break;
				
			case 0xC: //STA
				opaddr = fetch(PC, 2);	
				PC += 2;
				opaddr += 2;
				for(int i=0; i < 3; i++){
					memory[opaddr--] = A % 0x10;
					A /= 0x10;
				}
				
				printf("\n");
				break;
				
			case 0x50: //LDCH
				opaddr = fetch(PC, 2);
				PC += 2;
				A = fetch(opaddr, 1);
				break;
				
			case 0x54: //STCH
				opaddr = fetch(PC, 2);
				PC += 2;
				memory[opaddr] = A;
				break;
				
			case 0x18: //ADD
				opaddr = fetch(PC, 2);
				PC += 2;
				for(int i=0; i < 3; i++){
					var *= 0x100;
					var += memory[opaddr++];
				}
				A += var;
				break;
			
			case 0x1C: //SUB
				opaddr = fetch(PC, 2);
				PC += 2;
				for(int i=0; i < 3; i++){
					var *= 0x100;
					var += memory[opaddr++];
				}
				A -= var;
				break;
				
			case 0x20: //MUL
				opaddr = fetch(PC, 2);
				PC += 2;
				for(int i=0; i < 3; i++){
					var *= 0x100;
					var += memory[opaddr++];
				}
				A *= var;
				break;
				
			case 0x24: //DIV
				opaddr = fetch(PC, 2);
				PC += 2;
				for(int i=0; i < 3; i++){
					var *= 0x100;
					var += memory[opaddr++];
				}
				A /= var;
				break;
		}
		var = 0x00;
	}
	
	//printMem();
	fclose(fp);
}


//Absolute Loader
void loader(FILE *objcode){

	int address, i;
	unsigned int j;
	char straddr[10], temp[10];
	fscanf(objcode, "%s", record);
	
	while(record[0] != 'E'){	
		
		strslice(straddr, record, 2);
		address = strtol(straddr, NULL, 16);
		strslice(temp, record, 9);
		
		i=12; 
		while(record[i] != '\0'){
			if(record[i] != '^'){
				sprintf(temp, "%c%c", record[i], record[i+1]);
				j = strtol(temp, NULL, 16);
				memory[address] = j;
				address++;
				i += 2;
			}else{
				i++;
			}
		}
		fscanf(objcode, "%s", record);
	}
	
	//printMem();
	strslice(temp, record, 2);
	PC = strtol(temp, NULL, 16);//Loading the address of first executable instruction in End rec
}

void memRead(){
	unsigned int loc;
	printf("Enter the Memory location:  ");
	scanf("%X", &loc);
	for(int i=0;i <3; i++){
		printf("%X : %02X\n", loc, memory[loc]);
		loc++;
	}
}

void memWrite(){
	unsigned int loc, value;
	printf("Enter the Memory location and Value:  ");
	scanf("%X %X", &loc, &value);
	memory[loc] = value;
}


void main(){

	char straddr[10];
	int choice;
	
	FILE *objcode = fopen("objcode.sic", "r");
	
	if(!objcode){
		printf("Error in opening objcode.sic\n");
		exit(0);
	}
	
	fscanf(objcode, "%s", record);
	
	loader(objcode);

	
		printf("\nMAIN MENU: \n1 for memory read \n2 for memory write \n3 TO execute \n4 to exit virtual machine!\n\n");
	
	do{
		printf("\nEnter you choice : ");
		scanf("%d", &choice);
		
		switch(choice){
			case 1:
				memRead();
				break;
			case 2:
				memWrite();
				break;
			case 3:
				execute();
				break;
			case 4: 
				exit(0);
				break;
			default:
				printf("Invalid choice!");
				printf("\nMAIN MENU: \n1 for memory read \n2 for memory write \n3 TO execute \n4 to exit virtual machine!\n\n");
				break;
		}
	}while(choice != 4);
	
	fclose(objcode);
}


