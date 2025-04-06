#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<time.h>

void main(){
    int sock, n, wsize=5;
    int seq[100];
    struct sockaddr_in server, client;
    socklen_t length;

    int win[wsize], ack[wsize];

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = 3000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    n = bind(sock, (struct sockaddr*)&server, sizeof(server));

    length = sizeof(client);
    srand(time(NULL));

    while(1){
        int drop = rand()%5;
        int count=0;
        n = recvfrom(sock, &win, sizeof(win), 0, (struct sockaddr*)&client, &length);
        printf("Window recieved from client\n");
        printf("Packet %d Dropped!\n", win[drop]);
        win[drop]=-1;
        for(int i=0;i<wsize;i++){
            if(win[i]==-1){
                ack[i]=-1;
                break;
            }
            else{
                ack[i]=1;
                count++;
                printf("packet %d recieved!\n", win[i]);
            }
        }
        n = sendto(sock, &ack, sizeof(ack), 0, (struct sockaddr*)&client, length);
        for(int i=0;i<count;i++)
            printf("Acknowledgement for packet %d sent!\n", win[i]);
    }
    close(sock);
}