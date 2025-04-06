#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>

void main(){
    int sock, n, seqsize, wsize;
    int seq[100];
    struct sockaddr_in server;
    socklen_t length;

    printf("Enter array size: ");
    scanf("%d", &seqsize);
    printf("Enter packet sequence:\n");
    for(int i=0;i<seqsize; i++)
        scanf("%d", &seq[i]);
    wsize = 5;
    int win[wsize], ack[wsize];
    int wstart=0, wend=wsize;

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = 3000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    length = sizeof(server);


    while(1){
        if(wend>seqsize)
            wend = seqsize;

        for(int i=wstart, j=0;i<wend && j<wsize;i++, j++)
            win[j]=seq[i];

        n = sendto(sock, win, sizeof(win), 0, (struct sockaddr*)&server, length);
        printf("Window sent to server\n");
        
        printf("window:\n");
        for(int i=0;i<5;i++)
            printf("%d\t", win[i]);

        n = recvfrom(sock, ack, sizeof(ack), 0, (struct sockaddr*)&server, &length);

        for(int i=0;i<5;i++){
            if(ack[i]!=-1)
                printf("\nAcknowledgement for packet %d recieved from server!\n", win[i]);
            else 
                break;
        }

        int count=0;
        for(int i=0;i<wsize;i++){
            if(ack[i]==-1)
                break;
            count++;
        }

        wstart+=count;
        wend+=count;
        
        if (wstart >= seqsize)
            break;

    }
    close(sock);
}