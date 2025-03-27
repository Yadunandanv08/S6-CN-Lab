#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>

void main(){
    int n, desc;
    char buffer[100], name[100];
    struct sockaddr_in server;
    FILE *f1;
    
    desc = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = 3003;
    
    if (connect(desc, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("Connect failed");
        exit(1);
    }
    

    printf("enter filename: ");
    scanf("%s", name);
    write(desc, name, 100);
    f1 = fopen(name, "r");
    while((n=read(desc, buffer, 100))!=0){
        printf("%s", buffer);
    }

    close(desc);

}