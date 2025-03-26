#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>


void main(){
    int client;
    struct sockaddr_in server;
    char buffer[100];
    int length = sizeof(server);

    client = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    server.sin_family = AF_INET;
    server.sin_port = htons(2002);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    while(1){
        printf("server: ");
        fgets(buffer, 100, stdin);
        sendto(client, buffer, strlen(buffer), 0, (struct sockaddr*)&server, sizeof(server));
        recvfrom(client, buffer, sizeof(buffer)-1, 0, (struct sockaddr*)&server, &length);
        printf("client: %s", buffer);
    }
    close(client);
}