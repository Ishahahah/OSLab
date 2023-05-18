#include <stdio.h>
#include <math.h>

int main() {

    int block_size;

    printf("Enter size of memory block in KB: ");
    scanf("%d", &block_size);

    int request_size;

    printf("Enter number of requests: ");
    scanf("%d", &request_size);

    int memory_request[request_size];

    int n = log2(ceil(block_size/1.0))/log2(2);

    int blocks[n];

    int min_memory = block_size; //Minimum memory request cannot be more than block_size

    printf("Enter memory requests:\n");

    for (int i = 0; i < request_size; i++) {
        int request;
        scanf("%d", &request);
        memory_request[i]=request;
        if (request < min_memory) {
            min_memory = request;
        }
    }

    // printf("Minimum memory request: %d\n", min_memory);

    int m=(log(min_memory)/log(2))+1;

    // printf("%d\n", n);
    // printf("%d\n", m);

    int visited[n-m+1];

    blocks[0]=pow(2, m);
    visited[0]=0;
    blocks[1]=pow(2, m);
    visited[1]=0;

    printf("Before Allocation:\n");
    printf("%d\t", blocks[0]);
    printf("%d\t", blocks[1]);

    for(int i=2; i<n-m+1; i++)
    {
        blocks[i]=blocks[i-1]*2;
        visited[i]=0;
        printf("%d\t", blocks[i]);
    }

    printf("\n\n");

    int i=0;
    int j=0;

    for(int i=0; i<request_size; i++)
    {
        for (int j=0; j<n-m+1; j++)
        {
            if(visited[j]==0 && blocks[j]>=memory_request[i])
            {
                blocks[j]-=memory_request[i];
                printf("%d memory request is allocated in %d block\n", memory_request[i], j+1);
                memory_request[i]=0;
                visited[j]=1;
                break;
            }
        }
    }

    int remain_memory=0;

    printf("\n");
    printf("After Allocation:\n");
    for(int i=0; i<n-m+1; i++)
        {
            remain_memory+=blocks[i];
            printf("%d\t", blocks[i]);
        }

    for(int i=0; i<request_size; i++){
        if(memory_request[i]!=0)
        {
            printf("\nMemory can not be allocated for %d request", memory_request[i]);
        }
    }
        
    printf("\nRemaining memory is %d", remain_memory);    
    return 0;
}
