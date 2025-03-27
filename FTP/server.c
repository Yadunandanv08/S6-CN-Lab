#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>

void main(){
    int n, desc, temp;
    char buffer[100], name[100];
    struct sockaddr_in server, client;
    FILE *f1;
    
    desc = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = 3003;

    n = bind(desc, (struct sockaddr*)&server, sizeof(server));
    n = listen(desc, 5);
    
    int length = sizeof(client);
    temp = accept(desc, (struct sockaddr*)&client, &length);

    read(temp, &name, 100);
    f1 = fopen(name, "r");
    while(fgets(buffer, 100, f1)!=NULL){
        write(temp, buffer, 100);
    }
    close(temp);

}