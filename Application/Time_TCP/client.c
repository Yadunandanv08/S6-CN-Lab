#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<time.h>

void main(){
    int desc, n;
    char buffer[100];
    struct sockaddr_in client;
    socklen_t length;

    desc = socket(AF_INET, SOCK_STREAM, 0);

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_ANY;
    client.sin_port = 3003;

    n = connect(desc, (struct sockaddr*)&client, sizeof(client));

    while(1){
        printf("Ask server for time: ");
        fgets(buffer, 100, stdin);
        n = send(desc, buffer, 100, 0);
        n = recv(desc, buffer, 100, 0);
        printf("Time: %s\n", buffer);
    }
    close(desc);
}