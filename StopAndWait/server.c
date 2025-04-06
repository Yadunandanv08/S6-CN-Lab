#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>

typedef struct packet{
    int type;
    int sn;
    char data[100];
    int ack;
}Packet;

void main(){
    int sock, n;
    char buffer[100];
    struct sockaddr_in server, client;
    socklen_t length;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    
    server.sin_family = AF_INET;
    server.sin_port = 3000;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    n = bind(sock, (struct sockaddr*)&server, sizeof(server));

    length = sizeof(client);

    int fnum = 0;
    Packet packsnd;
    Packet packrecv;
    
    while(1){
        n = recvfrom(sock, &packrecv, sizeof(packrecv), 0, (struct sockaddr*)&client, &length);
        if(n>0 && packrecv.type == 1 && packrecv.sn == fnum){
            printf("Packet recieved from client: %s\n", packrecv.data);
            packsnd.ack = 0;
            packsnd.sn = fnum;
            packsnd.type = 0;
            sendto(sock, &packsnd, sizeof(packsnd), 0,(struct sockaddr*)&client, length);
            printf("Acknowledgement sent!\n");
        }
        else{
            printf("Packet not recieved\n");
        }
        fnum++;
    }
    close(sock);
}