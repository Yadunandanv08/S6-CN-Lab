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
    printf("hi");

    n = recv(temp, buffer, 100, 0);
    printf("\nclient: %s\n", buffer);
    int number = atoi(buffer);

    int flag = 0;
    for(int i=2;i<number/2;i++){
        if(number%i == 0){
            n = send(temp, "not prime", 100, 0);
            flag = 1;
            break;
        }    
    }
    if(flag == 0){
        n = send(temp, "prime", 100, 0);
    }
    close(temp);
    
}



