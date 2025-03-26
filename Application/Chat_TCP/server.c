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

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = 3003;

    n= bind(desc, (struct sockaddr*)&server, sizeof(server));

    n =listen(desc, 5);

    length = sizeof(client);

    temp = accept(desc, (struct sockaddr*)&client, &length);

    while(1){
        n = recv(temp, buffer, 100, 0);
        printf("\nclient: %s\n", buffer);
        printf("server: ");
        fgets(buffer, 100, stdin);
        n = send(temp, buffer, 100, 0);
    }

    close(temp);
    
}



