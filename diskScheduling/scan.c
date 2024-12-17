#include<stdio.h>
#include<stdlib.h>

int D[25],l,u,n;
void scan();
void sort();
int indexof(int);

int main(){
    printf("ENTER THE LOWER AND UPPER LIMIT OF DISK : ");
    scanf("%d%d",&l,&u);
    printf("ENTER THE SIZE OF DISK QUEUE : ");
    scanf("%d",&n);
    printf("ENTER  THE DISK QUEUE : ");
    for(int i =1;i <= n ;i++)
        scanf("%d",&D[i]);
    scan();
}

void scan(){

    int head,h_idx,sequence[20],s_idx=0,hm=0;
    printf("ENTER THE HEAD POINTER : ");
    scanf("%d",&head);
    D[0] = head;
    n++;
    sort();
    h_idx = indexof(head);
    for(int i = h_idx; i<n ;i++)    
        sequence[s_idx++] =D[i] ;
    sequence[s_idx++]= u;
    for(int i = h_idx-1;i>=0;i--)
        sequence[s_idx++] = D[i];
    printf("\nSEEK SEQUENCE IN SCAN :");
    for(int i=0;i<s_idx;i++){

        if(i<s_idx-1){
            hm+=abs(sequence[i+1]-sequence[i]);
            printf("%d -> ",sequence[i]);
        }else
            printf("%d ",sequence[i]);
            
    }
    printf("\nTOTAL HEAD MOVEMENTS: %d ",hm);
}

void sort(){
    for(int i =0;i< n -1;i++)
        for(int j =0; j< n-i-1;j++)
            if(D[j]>D[j+1]){
                int temp = D[j];
                D[j]=D[j + 1];
                D[j + 1] =temp;
            }
}
int indexof(int head){
    for(int i =0;i<n;i++)
        if(D[i]== head)
            return i;
}

