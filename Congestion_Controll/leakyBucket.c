#include<stdio.h>
void main(){
    int size, n, input, output, curr;

    printf("\nEnter Bucket Size: ");
    scanf("%d", &size);

    printf("\nEnter Flow Rate: ");
    scanf("%d", &output);

    printf("\nEnter Number of Inputs: ");
    scanf("%d", &n);

    curr=0;
    for(int i=0;i<n;i++){
        printf("\nEnter Incoming packet sizes: ");
        scanf("%d", &input);

        if(input<=(size-curr)){
            curr+=input;
            printf("\nBucket Size is %d / %d\n", curr, size);
        }
        else{
            printf("\ndropped %d packets: ", input-(size-curr));
            printf("\nBucket Size is %d / %d\n", curr, size);
            curr = size;
        }
        curr -= output;
        printf("\n%d packets remaining", curr);
    }
}