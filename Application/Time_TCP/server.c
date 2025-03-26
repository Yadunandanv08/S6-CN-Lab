#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<time.h>    

void main(){
    int desc, temp, n;
    char buffer[100];
    struct sockaddr_in server, client;
    socklen_t length;
    time_t t;
    struct tm *tm_info;
    time(&t);

    desc = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = 3003;

    n = bind(desc, (struct sockaddr*)&server, sizeof(server));

    n = listen(desc, 5);

    length = sizeof(client);
    temp = accept(desc, (struct sockaddr*)&client, &length);

    while(1){
        n = recv(temp, buffer, 100, 0);
        tm_info = localtime(&t);
        strftime(buffer, 100, "%y-%m-%d %H:%M:%S", tm_info);
        n = send(temp, buffer, 100, 0);
    }

    close(temp);
}