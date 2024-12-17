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

//To print the content of memory
void printMem(){
	char  temp[10];
	strslice(temp, record, 2); // use for getting limit if need for the below loop
	for(int i = 0x2000; i < 0x2017; i++){
		printf("%X\t: %X\n" ,i, memory[i]);
	}
}


//To fetch from memory
int fetch(int address, int len){
	unsigned int value = 0x00;
	
	for(int i = 0, j = address; i < len; i ++, j++){
		value = value * 0x100;
		value += memory[j];
	}
	//printf("Temp :  %04X\naddress :  %x\n", value, address);

	return value;
}

//For executing the loaded prgm
void execute(){

	//address = 0x200E;
	
	char temp[10];
	int tlen, opcode, opaddr;
	FILE *fp = fopen("length.txt", "r");
	
	fscanf(fp, "%s", temp);
	tlen = strtol(temp, NULL, 16);
	
	for(int i=0x00; i<0x0C/*tlen*/; i+=0x03){
		opcode = fetch(PC, 1);
		printf("Opcode :  %X\n", opcode);
		PC++;
		switch(opcode){
			case 0x00: //LDA
				opaddr = fetch(PC, 2);
				PC += 2;
				A = fetch(opaddr, 3);
				printf("A : %X\n", A);
				break;
				
			case 0xC: //STA
				opaddr = fetch(PC, 2);
				PC += 2;
				printf("%X\n", opaddr);
				opaddr += 2;
				for(int i=0; i < 2; i++){
					memory[opaddr--] = A % 0x10;
					A /= 0x10;
				}
				break;
				
			case 0x50: //LDCH
				opaddr = fetch(PC, 2);
				PC += 2;
				A = fetch(opaddr, 1);
				printf("A : %X\n", A);
				break;
				
			case 0x54: //STCH
				opaddr = fetch(PC, 2);
				PC += 2;
				printf("%X\n", opaddr);
				memory[opaddr] = A;
				break;
				
		}
	}
	
	printMem();
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
				//printf("%X\t:%X \t %c\t%c\n",address, memory[address], record[i], record[i+1]);
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
	PC = strtol(temp, NULL, 16);
	execute(); //passing the address of first executable instruction in End rec
}


void main(){
	memory[2018] = '1';
	char straddr[10];
	FILE *objcode = fopen("objcode.sic", "r");
	
	if(!objcode){
		printf("Error in opening objcode.sic\n");
		exit(0);
	}
	
	fscanf(objcode, "%s", record);
	
	loader(objcode);
	
	
	
	fclose(objcode);

}
