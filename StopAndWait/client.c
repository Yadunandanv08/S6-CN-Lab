#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<time.h>

typedef struct packet{
    int type;
    int sn;
    char data[100];
}Packet;

void main(){
    int sock, n;
    char buffer[100];
    struct sockaddr_in server;
    socklen_t length;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    
    server.sin_family = AF_INET;
    server.sin_port = 3000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    length = sizeof(server);

    int fnum = 0, ackrecv = 1;
    Packet packsnd;
    Packet packrecv;
    
    while(1){
        srand(time(NULL));
        int drop = rand()%9;
        if(ackrecv == 1){
            packsnd.sn = fnum;
            packsnd.type = 1;
            sprintf(packsnd.data, "packet %d", fnum);

            sendto(sock, &packsnd, sizeof(packsnd), 0,(struct sockaddr*)&server, length);
            printf("Packet %d sent!\n", fnum);
            n = recvfrom(sock, &packrecv, sizeof(packrecv), 0, (struct sockaddr*)&server, &length);
        }
        if(drop !=0 && fnum%drop == 0){
            printf("Packet dropped!\n");
            ackrecv = 0;
            sleep(1);
        }
        else if(n>0 && packrecv.type == 0 && packrecv.sn == fnum){
            printf("Acknowledgement for packet %d Recieved\n", fnum);
            ackrecv = 1;
            sleep(1);
            fnum++;
        }
        else{
            printf("Acknowledgement for packet %d not Recieved\n", fnum);
            ackrecv = 0;
            sleep(1);
        }
    }
    close(sock);
}