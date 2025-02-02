#include <string.h> 
#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
 
void main(){ 
    int client; 
    struct sockaddr_in servAddr; 
    char servMsg[2000], cliMsg[2000]; 
    int server_struct_length = sizeof(servAddr);  
        
    if((client = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){ 
        printf("socket creation error\n"); 
        exit(1); 
    } 

    printf("Socket created\n"); 
    servAddr.sin_family = AF_INET; 
    servAddr.sin_port = htons(2002); 
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    printf("Enter message to server: "); 
    fgets(cliMsg, sizeof(cliMsg), stdin); 
    if(sendto(client, cliMsg, strlen(cliMsg), 0, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0){ 
        printf("Unable to send message\n"); 
        exit(1); 
    } 
    if(recvfrom(client, servMsg, sizeof(servMsg), 0, (struct sockaddr*)&servAddr,&server_struct_length) < 0){ 
        printf("receiving error\n"); 
        exit(1); 
    } 
    close(client); 
} 
