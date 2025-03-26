#include<stdio.h>

void main(){
    int distance[10][10], n;
    printf("\nEnter number of routers: ");
    scanf("%d", &n);
    printf("\nEnter distance matrix: ");
    for(int i=0;i<n;i++)
        for(int j = 0;j<n;j++)
            scanf("%d", &distance[i][j]);

    int count;
    do{
        count = 0;
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                for(int k=0;k<n;k++)
                    if(distance[i][j]>distance[i][k]+distance[k][j]){
                        distance[i][j]=distance[i][k]+distance[k][j];
                        count = 1;
                    }
    }while(count!=0);
    for(int i = 0;i < n;i++){
        printf("\t%c",i+65);
    }
    for(int i = 0; i < n;i++){
        printf("\n%c\t",i+65);
        for(int j = 0; j < n;j++){
            printf("%d\t",distance[i][j]);
        }
    }

}