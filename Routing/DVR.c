#include<stdio.h>
#include<unistd.h>

void initialize(int nodes, int next[100][100]){
    for(int i=0;i<nodes;i++)
        for(int j=0;j<nodes;j++)
            next[i][j]=j;
}

void route(int nodes, int cost[100][100], int next[100][100]){
    int updated;
    do{
        updated=0;
        for(int i=0;i<nodes;i++)
            for(int j=0;j<nodes;j++)
                for(int k=0;k<nodes;k++)
                    if(cost[i][j]>cost[i][k]+cost[k][j]){
                        cost[i][j] = cost[i][k]+cost[k][j];
                        next[i][j] = k;
                        updated=1;
                    }
    }while(updated);
}

void main(){

    int cost[100][100], next[100][100], nodes;

    printf("Enter number of nodes: ");
    scanf("%d", &nodes);

    printf("Enter Cost Matrix:\n");
    for(int i=0;i<nodes;i++){
        printf("\n");
        for(int j=0;j<nodes;j++)
            scanf("%d", &cost[i][j]);
    }
        
    initialize(nodes, next);
    route(nodes, cost, next);

    for(int i=0;i<nodes;i++){
        printf("Routing table of node %d\n", i);
        printf("Curr\tDist\tNext\n");
        printf("=============================================\n");
        for(int j=0;j<nodes;j++)
            printf("%d\t\t%d\t\t%d\n", j, cost[i][j], next[i][j]);
    }
}