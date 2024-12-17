#include <stdio.h>

struct process{
	int PrNo;
	int at, bt, wt, tat, rt, prio;
};

int smallestProcessIndex(struct process *p, int ct, int limit){
	int i, hpi = -1, high_prio = 9999;
	for(i=0;i<limit;i++){
		if(p[i].rt != 0 && p[i].at <=ct){
			if(p[i].prio < high_prio){
				high_prio = p[i].prio;
				hpi = i;
			}
		}
	}
	return hpi;
}

void main(){

	int limit, i, j, ct = 0, hpi;
	float avg_wt = 0, avg_tat = 0;
	printf("\nEnter the number of processes : ");
	scanf("%d", &limit);
	
	struct process p[limit];
	
	printf("\nEnter the Arrival time, Burt time and priority\n");
	for(i=0;i<limit;i++){
		scanf("%d %d %d",&p[i].at, &p[i].bt, &p[i].prio);
		p[i].PrNo = i;
		p[i].rt = p[i].bt;
	}
	
	printf("\nPrNo \t AT \t BT \t WT \t TAT \t RT \t prio");
	
	do{
		hpi = smallestProcessIndex(p, ct, limit);
		if(hpi == -1){
			break;
		}
			
		ct += p[hpi].rt;
		p[hpi].rt = 0;
		p[hpi].tat = ct - p[hpi].at;
		p[hpi].wt = p[hpi].tat - p[hpi].bt;
		
		printf("\n%d \t %d \t %d \t %d \t %d \t %d \t %d", p[hpi].PrNo, p[hpi].at, p[hpi].bt, p[hpi].wt, p[hpi].tat, p[hpi].rt,  p[hpi].prio);
		
		avg_wt += p[hpi].wt;
		avg_tat += p[hpi].tat;
	}while(1);
	
	
	printf("\nAverage waiting time : %f", avg_wt / limit);
	printf("\nAverage turn around time : %f \n", avg_tat / limit);
	
}
