#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>


void main(){
    char buffer[100];
    int n, desc, temp;
    socklen_t length;
    struct sockaddr_in server, client;

    desc = socket(AF_INET, SOCK_STREAM, 0);

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_ANY;
    client.sin_port = 3003;

    length = sizeof(server);

    n= connect(desc, (struct sockaddr*)&client, sizeof(client));

    while(1){
        printf("client: ");
        fgets(buffer, 100, stdin);
        n = send(desc, buffer, 100, 0);
        n = recv(desc, buffer, 100, 0);
        printf("\nserver: %s\n", buffer);
    }

    close(temp);
    
}

