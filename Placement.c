#include<stdio.h>
#include<stdlib.h>

void firstFit(int block[], int m, int process[], int n, int allocation[])
{

    for(int i = 0; i < n; i++)
    {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++)  
    {
        for (int j = 0; j < m; j++)  
        {
            if (block[j] >= process[i])
            {
                
                allocation[i] = j;

                block[j] -= process[i];

                break; 
            }
        }
    }
}

void nextFit(int block[], int m, int process[], int n, int allocation[])
{
    int j=0;
    int t=m-1;

    for(int i = 0; i < n; i++)
    {
        allocation[i] = -1;
    }

    for(int i = 0; i < n; i++){

        while (j < m){
            if(block[j] >= process[i]){
                 
                allocation[i] = j;
                 
                block[j] -= process[i];
                 

                t = (j - 1) % m;
                break;
            }
            if (t == j){
                // sets a new end point
                t = (j - 1) % m;
                // breaks the loop after going through all memory block
                break;
            }
            j = (j + 1) % m;
        }
    }
}

void bestFit(int block[], int m, int process[], int n, int allocation[])
{
    for(int i = 0; i < n; i++)
    {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        int bestIndex = -1;
        for (int j = 0; j < m; j++)
        {
            if (block[j] >= process[i])
            {
                if (bestIndex == -1)
                    bestIndex = j;
                else if (block[bestIndex] > block[j])
                    bestIndex = j;
            }
        }
 
        if (bestIndex != -1)
        {
            allocation[i] = bestIndex;
            block[bestIndex] -= process[i];
        }
    }
}

void worstFit(int block[], int m, int process[], int n, int allocation[])
{

    for(int i = 0; i < n; i++)
    {
        allocation[i] = -1;
    }

    for (int i=0; i<n; i++)
    {
        int worstIndex = -1;
        for (int j=0; j<m; j++)
        {
            if (block[j] >= process[i])
            {
                if (worstIndex == -1)
                    worstIndex = j;
                else if (block[worstIndex] < block[j])
                    worstIndex = j;
            }
        }
 
        if (worstIndex != -1)
        {

            allocation[i] = worstIndex;

            block[worstIndex] -= process[i];
        }
    }
}    

int main()
{
    int m; //number of blocks in the memory
    int n; //number of processes in the input queue 

    printf("Enter number of blocks in memory :");
    scanf("%d", &m);

    printf("Enter number of processes in memory :");
    scanf("%d", &n);

    int block[m];
    int process[n];

    printf("Enter size of %d blocks : ", m);

    for(int i=0; i<m; i++){
        scanf("%d", &block[i]);
    }

    printf("Enter size of %d processes : ", n);

    for(int i=0; i<n; i++){
        scanf("%d", &process[i]);
    }

    int allocation[n];

    int x;

    printf("Enter number (firstfit = 1, nextfit = 2, bestfit = 3, worstfit =4 ): ");
    scanf("%d", &x);
    
    switch(x){
        case 1:
            firstFit(block, m, process, n, allocation);
            break;

        case 2:
            nextFit(block, m, process, n, allocation);
            break;

        case 3:
            bestFit(block, m, process, n, allocation);       
            break;

        case 4:
            worstFit(block, m, process, n, allocation);  
            break;
        
        case 5:
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid choice, please try again.\n");
            break;
    }

    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < n; i++)
    {
        printf(" %i\t\t\t", i+1);
        printf("%i\t\t\t\t", process[i]);
        if (allocation[i] != -1)
            printf("%i", allocation[i] + 1);
        else
            printf("Not Allocated");
        printf("\n");
    }

    printf("\nAfter placing processes remaining memory in blocks :\n");

    for(int i=0; i<m; i++){
        printf("%d\t", block[i]);
    }

    return 0 ;
}
