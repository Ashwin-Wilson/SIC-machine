#include <stdio.h>

struct process{
	int PrNo;
	int prio, bt, wt, tat;
};

void main(){
	
	int limit, i, j, ct = 0;
	float avg_wt = 0, avg_tat = 0;
	printf("\nEnter the number of processes : ");
	scanf("%d", &limit);
	
	struct process p[limit];
	
	printf("\nEnter the Priority and  Burt time\n");
	for(i=0;i<limit;i++){
		scanf("%d %d", &p[i].prio, &p[i].bt);
		p[i].PrNo = i;
	}
	
	struct process temp;
	
	for(i=limit-1;i>0;i--){
		for(j=0;j<i;j++){
			if(p[j].prio > p[j+1].prio){
				temp = p[j];
				p[j] = p[j+1];
				p[j+1] = temp;
			}
		}
	}
	
	
	printf("\nPrNo \t BT \t WT \t TAT");
	for(i=0;i<limit;i++){
		p[i].wt = ct;
		ct += p[i].bt;
		p[i].tat = p[i].bt + p[i].wt;
		printf("\n%d \t %d \t %d \t %d", p[i].PrNo, p[i].bt, p[i].wt, p[i].tat);
		
		avg_wt += p[i].wt;
		avg_tat += p[i].tat;
		
	}
	
	printf("\nAverage waiting time : %f", avg_wt / limit);
	printf("\nAverage turn around time : %f \n", avg_tat / limit);
	
}
