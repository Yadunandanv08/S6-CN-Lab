#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

int ack(){
    return rand()%100<70;
}

void main(){
    int n, wt, i=1;

    printf("Enter number of packets:");
    scanf("%d", &n);
    printf("Enter waiting time:");
    scanf("%d", &wt);

    srand(time(NULL));

    while(i<=n){
        printf("Sending packet....\n");
        sleep(1);
        if(ack()){
            printf("Acknowledgement recieved for packet %d\n", i);
            i++;
        }
        else{
            sleep(wt);
            printf("Acknowledgement not recieved for packet %d\n", i);
            printf("Resending..\n");
        }
    }
    printf("Finished!\n");

}