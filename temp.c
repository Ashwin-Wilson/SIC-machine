#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char mem[100000];

void tohex(unsigned char high, char low, int loc){
	
	int temp;
	if(high < 'A'){
		temp = strtol(&high, NULL, 16);
		sprintf(mem + loc, "%02X", high);
		printf("high : %02X\n", mem[loc]);
	} 	
}

void main(){


	char temp[100];
	char add = 'A';
	int loc = 0xA;
	char high = '9', low = 'B';
	sprintf(mem, "askdjfniouewnxkjvhipuarhiwfijnwiucniwue");
	int len;
	len = 2;
	int offset = len;
	strncpy(temp, mem+offset, 3);
	printf("%s\n",temp);
	//tohex(high, low, loc);
	
}
