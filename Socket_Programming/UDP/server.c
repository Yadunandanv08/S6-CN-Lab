#include <stdio.h> 
#include <stdlib.h>  
#include <string.h> 
#include <unistd.h> 
#include <sys/socket.h> 
#include <netinet/in.h>
#include <arpa/inet.h> 
 
void main() { 
    int server; 
    char servMsg[2000], cliMsg[2000]; 
    struct sockaddr_in server, client; 
    int client_struct_length = sizeof(client); 
     
    if ((server = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) { 
        printf("socket creation error\n"); 
        exit(1); 
    } 
    printf("Socket created\n"); 
    server.sin_family = AF_INET; 
    server.sin_port = htons(2002); 
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    
    if (bind(server, (struct sockaddr*)&server, sizeof(server)) < 0) { 
        printf("binding error\n"); 
        exit(1); 
    } 
    printf("Binding done\n"); 
    printf("Listening...\n"); 
    
    if (recvfrom(server, cliMsg, sizeof(cliMsg), 0, (struct sockaddr*)&client, 
    &client_struct_length) < 0) { 
        printf("receiving error\n"); 
        exit(1); 
    } 
    printf("Msg from client: %s\n", cliMsg); 
    strcpy(servMsg, cliMsg); 
    if(sendto(server, servMsg, strlen(servMsg), 0, 
        (struct sockaddr*)&client, client_struct_length) < 0) { 
        printf("sending error\n"); 
        exit(1); 
    } 
    close(server);  
}