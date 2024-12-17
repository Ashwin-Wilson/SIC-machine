#include <stdio.h>

struct process{
	int no;
	int bt, wt, tat, rt;
};

void main(){

	int i, j, limit, time_slice, ct = 0, npi, completed = 0, done = 1;
	float avg_wt = 0, avg_tat = 0;

	printf("\nEnter the number of processes : ");
	scanf("%d",&limit);	
	
	struct process pr[limit];
	
	printf("\nEnter the time slice : ");
	scanf("%d",&time_slice);	
	
	for(i=0;i<limit;i++){
		printf("\nEnter the BT of processes %d : ",i);
		scanf("%d", &pr[i].bt);
		pr[i].rt = pr[i].bt;
		pr[i].no = i;
	}
	
	printf("\nPrNo \t BT \t WT \t TAT \t RT");
	
	do{
	
		done = 1;
		
		for(i=0;i<limit;i++){
		
			if(pr[i].rt != 0){

				done = 0;

				if(pr[i].rt > time_slice){
					ct += time_slice;
					pr[i].rt -= time_slice;
				}
				else{
					ct += pr[i].rt;
					pr[i].rt = 0;
					pr[i].tat = ct;
					pr[i].wt = ct - pr[i].bt;
					
					avg_wt += pr[i].wt;
					avg_tat += pr[i].tat;
					
					printf("\n%d \t %d \t %d \t %d \t %d", pr[i].no, pr[i].bt, pr[i].wt, pr[i].tat, pr[i].rt);
				}
			}
		}
		if(done){
			break;
		}
	}while(ct);
	
 	printf("\n Average Waiting time : %f", avg_wt / limit);
 	printf("\n Average Turn Around time : %f", avg_tat / limit);		
}



