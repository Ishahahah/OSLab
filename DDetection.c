#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESS 100
#define MAX_RESOURCE 100

int available[MAX_RESOURCE];
int allocation[MAX_PROCESS][MAX_RESOURCE];
int request[MAX_PROCESS][MAX_RESOURCE];
int marked[MAX_PROCESS];
int safe_sequence[MAX_PROCESS];
int n, m;

int main()
{
    // Input data
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    printf("Enter the available resources: ");
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &available[i]);
    }

    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the request matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &request[i][j]);
        }
    }

    //Show the matrices
    printf("Available resources: \n");
    for (int i = 0; i < m; i++)
    {
        printf("%d\t", available[i]);
    }

    printf("\nAllocation matrix: \n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%d\t", allocation[i][j]);
        }
        printf("\n");
    }

    printf("Request matrix: \n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%d\t", request[i][j]);
        }
        printf("\n");
    }

    // Check for deadlock
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        marked[i] = 0;
    }

    int flag = 1;
    while (flag)
    {
        flag = 0;
        for (int i = 0; i < n; i++)
        {
            printf("Process %d is going on --\n",i);
            if (!marked[i])  //check process is not marked
            {
                int j;
                for (j = 0; j < m; j++)
                {
                    if (request[i][j] > available[j])
                    {
                        break;
                    }
                }

                if (j == m)
                {
                    marked[i] = 1;
                    flag = 1;
                    safe_sequence[count++] = i;
                    for (j = 0; j < m; j++)
                    {
                        available[j] += allocation[i][j];
                        printf("%d\t\n",available[j]);
                    }
                }
            }
        }
    }

    if (count == n)
    {
        printf("System is in safe state.\nNo deadlock is in the system. \n");
        printf("Safe sequence: ");
        for (int i = 0; i < n; i++)
        {
            printf("%d ", safe_sequence[i]);
        }
        printf("\n");
        return 0;
    }
    else
    {
        printf("System is in deadlock state.\n");
        return 1;
    }
}



/*Enter the number of processes: 5
Enter the number of resources: 3
Enter the available resources: 0 0 0
Enter the allocation matrix:
0 1 0
2 0 0
3 0 3
2 1 1
0 0 2
Enter the request matrix:
0 0 0
2 0 2
0 0 0
1 0 0
0 0 2
Available resources: 
0       0       0
Allocation matrix:
0       1       0
2       0       0
3       0       3
2       1       1
0       0       2
Request matrix:
0       0       0
2       0       2
0       0       0
1       0       0
0       0       2
Process 0 is going on --
0
1
0
Process 1 is going on --
Process 2 is going on --
3
1
3
Process 3 is going on --
5
2
4
Process 4 is going on --
5
2
6
Process 0 is going on --
Process 1 is going on --
7
2
6
Process 2 is going on --
Process 3 is going on --
Process 4 is going on --
Process 0 is going on --
Process 1 is going on --
Process 2 is going on --
Process 3 is going on --
Process 4 is going on --
System is in safe state.
No deadlock is in the system.
Safe sequence: 0 2 3 4 1*/