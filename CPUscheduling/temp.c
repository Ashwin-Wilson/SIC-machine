#include <stdio.h>

struct process{
	int no, at, bt, rt, wt, tat;
};

void main(){
	
	int limit, i, j, temp, ct = 0, done, time_slice;
	float  avg_wt=0, avg_tat=0;
	
	printf("Enter the no of processes :  ");	
	scanf("%d", &limit);
	
	struct process p[limit];
	
	printf("Enter the BT of each process: \n");	
	for(i=0;i<limit;i++){
		p[i].no = i;
		scanf("%d", &p[i].bt);
		p[i].rt = p[i].bt;
	}
	
	printf("Enter the time slice :  ");	
	scanf("%d", &time_slice);
	
	
	do{
		done = 0;
		for(i=0;i<limit;i++){
			if(p[i].rt != 0){
				done = 1;
				if(p[i].rt > time_slice){
					ct += time_slice;
					p[i].rt -= time_slice;
				}else{
					ct += p[i].rt;
					p[i].rt = 0;
					p[i].tat = ct;
					p[i].wt = p[i].tat - p[i].bt;
					printf("%d\t%d\t%d\t%d\t%d\n", p[i].no, p[i].bt, p[i].rt, p[i].wt, p[i].tat);
					
					avg_wt += p[i].wt;
					avg_tat += p[i].tat;
				}
			}
		}	
	}while(done);
	
	
	printf("avg wt :  %f\n", avg_wt / limit);
	printf("avg tat :  %f\n", avg_tat / limit);
	
}
