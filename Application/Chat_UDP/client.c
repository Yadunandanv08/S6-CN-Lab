#include <stdio.h> 
#include <stdlib.h>  
#include <string.h> 
#include <unistd.h> 
#include <sys/socket.h> 
#include <netinet/in.h>
#include <arpa/inet.h> 
 
void main(){
    int servr;
    char buffer[200];
    struct sockaddr_in client;
    int length = sizeof(client);

    servr = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr("127.0.0.1");
    client.sin_port = htons(2002);

    bind(servr, (struct sockaddr*)&client, sizeof(client));

    while(1){ 
        recvfrom(servr, buffer, sizeof(buffer)-1, 0, (struct sockaddr*)&client, &length);
        printf("client: %s", buffer); 
        printf("client: ");
        fgets(buffer, 100, stdin);
        sendto(servr, buffer, strlen(buffer), 0, (struct sockaddr*)&client, sizeof(client));
    }
    close(servr);
}
