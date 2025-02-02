#include <stdlib.h> 
#include <stdio.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <netdb.h> 
#include <arpa/inet.h> 

void main() 
{ 
    FILE *fp; 
    struct sockaddr_in servaddr; 
    int client, s; 
    char name[1000], fname[1000], rcvg[1000];  
       
    if ((client = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
        printf("socket creation error\n"); 
        exit(1); 
    } 
    printf("Socket created...\n"); 
    
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(2002); 
    
    if (connect(client, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){ 
        printf("connection error\n"); 
        close(client); 
        exit(1); 
    } 
    printf("Connected...\n"); 
    
    printf("Enter the existing file name: "); 
    scanf("%s", name); 
    printf("Enter the new file name: "); 
    scanf("%s", fname); 
     
    if ((fp = fopen(fname, "w")) == NULL) {
        printf("Error: Unable to open file for writing...\n");
        close(client);
        exit(0);
    }

    send(client, name, sizeof(name), 0); 
    
    while (1){   
        
        if ((s = recv(client, rcvg, sizeof(rcvg) - 1, 0)) <= 0){
            if(s == 0)
                printf("connection closed\n");
            else 
                printf("Error: File not received\n");
            fclose(fp);
            close(client);
            break; 
        } 
        
        rcvg[s] = '\0'; 
        
        if (strcmp(rcvg, "error") == 0){ 
            printf("File is not available..\n"); 
            fclose(fp);
            close(client);
            break; 
        } 
        else if (strcmp(rcvg, "completed") == 0){ 
            printf("File transfer completed...\n"); 
            fclose(fp); 
            close(client); 
            break; 
        } 
        else{
            fwrite(rcvg, sizeof(char), s, fp);  
        }
    }
}
