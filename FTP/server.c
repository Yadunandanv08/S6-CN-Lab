#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>

void main(){
    int server, client, val;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1000];
    FILE *fp;

    if((server = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        printf("socket creation error\n");
        exit(1);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(2002);

    if(bind(server, (struct sockaddr*)&address, sizeof(address)) < 0){
        printf("binding error\n");
        exit(1);
    }

    if(listen(server, 3) < 0){
        printf("listening error\n");
        exit(1);
    }
    printf("listening..\n");

    while(1){
        if((client = accept(server, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0){
            printf("connection failed\n");
            exit(1);
        }

        if((val = read(client, buffer, sizeof(buffer))) < 0){
            send(client, "error", 5, 0);
            close(client);
            continue;
        }

        buffer[val] = '\0';
        
        if((fp = fopen(buffer, "rb")) == NULL)
            send(client, "error", 5, 0);
        else{
            char fbuf[1000];
            int bytes;
            while((bytes = fread(fbuf, 1, sizeof(fbuf), fp)) > 0)
                send(client, fbuf, bytes, 0);
            fclose(fp);
            send(client, "completed", 9, 0);
        }
        close(client);
    }
}
