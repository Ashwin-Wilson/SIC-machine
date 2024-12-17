#include <stdio.h>

void main(){

	int n, m, i, j,k, flag;
	
	printf("Enter the number of process and resources:  ");
	scanf("%d %d", &n, &m);
	
	int max[n][m], alloc[n][m], need[n][m], avail[m], work[m], finish[n], safesq[n];
	
	printf("Enter the max matrix\n");
	for(i=0;i<n;i++){
		finish[i] = 0;
		for(j=0;j<m;j++){
			scanf("%d", &max[i][j] );
		}
	}
	
	printf("Enter the allocation matrix\n");
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			scanf("%d", &alloc[i][j] );
		}
	}
	
	printf("Enter the avail matrix\n");
	for(i=0;i<m;i++){
		scanf("%d", &avail[i]);
		work[i] = avail[i];
	}
	
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			need[i][j] = max[i][j] - alloc[i][j];
		}
	}
	int idx=0;
	
	for(int l=0;l<n;l++){
		for(i=0; (i<n);i++){
			if(finish[i] == 0){
				flag = 0;
				for(j=0;j<m;j++){
					if(need[i][j] > work[j]){
						flag = 1;
						break;
					}
				}
				if(flag == 0){
					for(k=0;k<m;k++){
						work[k] += alloc[i][k];
					}
					finish[i] = 1;
					safesq[idx++] = i;
				}
			}
		}
		
	}
	
	printf("safe sequence : \n");
	for(int l=0;l<n;l++){
		printf("%d\t", safesq[l]);
	}
					
	
}
