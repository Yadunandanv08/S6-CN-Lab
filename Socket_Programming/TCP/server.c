#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>

void main(){
    char buffer[100];
    int n, desc, temp;
    socklen_t length;
    struct sockaddr_in server, client;

    desc = socket(AF_INET, SOCK_STREAM, 0);
    if (desc == -1)
        printf("error creating socket\n");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = 3003;
    n = bind(desc, (struct sockaddr*)&server, sizeof(server));
    if(n == -1)
        printf("binding error\n");
    
    n = listen(desc, 5);
    if(n == -1)
        printf("listening error\n");
    
    length = sizeof(client);
    temp = accept(desc, (struct sockaddr*)&client, &length);
    if(temp == -1)
        printf("error in temporary socket creation\n");

    n = recv(temp, buffer, 100, 0);
    if(n == -1)
        printf("recieving error\n");
    
    printf("Message from client: %s\n", buffer);
    close(temp);

}