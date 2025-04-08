#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

int ack(){
    return rand()%100<70;
}

void main(){
    int n, ws, wt, i=1, count=1;

    srand(time(NULL));

    printf("Enter Number of packets:");
    scanf("%d", &n);
    printf("enter window size:");
    scanf("%d", &ws);
    printf("Enter waiting time:");
    scanf("%d", &wt);

    int ackarr[n+1];

    while(i<=n){
        if((ws+i-1)>n)
            ws = n+1-i;
        printf("Sending packets %d to %d..\n", i, i+ws-1);
        for(int j=i;j<ws+i;j++){
            if(ack()){
                sleep(1);
                printf("Ack recieved for %d\n", j);
                ackarr[j]=1;
            }
            else{
                sleep(wt);
                printf("Ack not recieved for %d\n", j);
                ackarr[j]=-1;
            }
        }
        for(int j=i;j<ws+i;j++){
            if(ackarr[j]==-1){
                printf("Resending packets from %d\n", count);
                break;
            }
            else count++;
        }
        i=count;
    }
}