#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>

void main(){
    char buffer[100];
    int n, desc;
    struct sockaddr_in client;

    desc = socket(AF_INET, SOCK_STREAM, 0);
    if(desc == -1)
        printf("socket creation error\n");

    client.sin_family =  AF_INET;
    client.sin_addr.s_addr = INADDR_ANY;
    client.sin_port = 3003;

    n = connect(desc, (struct sockaddr*)&client, sizeof(client));
    if(n == -1)
        printf("error in server connection\n");
    
    printf("enter data to be sent: ");
    fgets(buffer, 100, stdin);

    n = send(desc, buffer, 100, 0);
    if(n == -1)
        printf("error in sending");
    
    close(desc);
}