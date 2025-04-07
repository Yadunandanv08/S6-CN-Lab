#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void main(){
    int seq[100], window[5], ack[5], size, wstart=0, wend=5, pointer=0, count;
    printf("\nEnter sequence size:");
    scanf("%d", &size);
    srand(time(NULL));

    printf("\nEnter sequence:");
    for(int i=0;i<size;i++)
        scanf("%d", &seq[i]);

    
    while(wstart<size || pointer>0){
        for(int i = pointer;i<5;i++)
            window[i]=-1;

        int drop = rand()%6;
        for(int i=wstart, j=pointer;i<wend && j<5;i++, j++)
            window[j]=seq[i];
        
        printf("\nwindow sent to server:");
        for(int i=0;i<5 && window[i]!=-1;i++)
            printf("%d\t", window[i]);

        count=0;
        for(int i=0;i<5;i++){
            if(window[i]!=-1){
                if(i==drop){
                    ack[i]=-1;
                    printf("\npacket %d dropped!", window[i]);
                }
                else{
                    ack[i]=1;
                    printf("\nPacket %d recieved, acknowledgement sent", window[i]);
                    count++;
                }
            }
            else
                ack[i]=-1;
        }
        
        pointer=0;
        for(int i=0;i<5;i++){
            if(ack[i]==-1 && window[i]!=-1){
                window[pointer]=window[i];
                pointer++;
            }
        }
        wstart+=count;
        wend = wstart+5;
        if(wend>size)
            wend = size;
    }
}