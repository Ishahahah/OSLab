#include <stdio.h>

#define MAX_RESOURCES 5
#define MAX_PROCESSES 5

int available[MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];

void print_status(int num_resources, int num_processes)
{
    printf("Available resources:\n");
    for (int i = 0; i < num_resources; i++)
    {
        printf("%d ", available[i]);
    }
    printf("\n");

    printf("Allocation matrix:\n");
    for (int i = 0; i < num_processes; i++)
    {
        for (int j = 0; j < num_resources; j++)
        {
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    int num_resources, num_processes;

    // Initialize available resources
    printf("Enter the number of resources: ");
    scanf("%d", &num_resources);
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    printf("Enter the number of available resources:\n");
    for (int i = 0; i < num_resources; i++)
    {
        scanf("%d", &available[i]);
    }

    // Initialize maximum demand for each process
    printf("Enter the maximum demand for each process:\n");
    for (int i = 0; i < num_processes; i++)
    {
        printf("For process %d:\n", i);
        for (int j = 0; j < num_resources; j++)
        {
            scanf("%d", &maximum[i][j]);
        }
    }

    // Initialize allocation matrix
    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < num_processes; i++)
    {
        printf("For process %d:\n", i);
        for (int j = 0; j < num_resources; j++)
        {
            scanf("%d", &allocation[i][j]);

        }
    }
    printf("Need matrix:\n");
    for (int i = 0; i < num_processes; i++)
    {
        for (int j = 0; j < num_resources; j++)
        {
            need[i][j] = maximum[i][j] - allocation[i][j];
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
    // Check for safe state
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0};
    int safe_sequence[MAX_PROCESSES];
    int count = 0;

    print_status(num_resources, num_processes);

    while (count < num_processes)
    {
        int found = 0;
        for (int i = 0; i < num_processes; i++)
        {
            if (!finish[i])
            {
                int j;
                for (j = 0; j < num_resources; j++)
                {
                    if (need[i][j] > available[j])
                    {
                        break;
                    }
                }
                if (j == num_resources)
                {
                    for (int k = 0; k < num_resources; k++)
                    {
                        available[k] += allocation[i][k];
                        allocation[i][k] = 0;
                        need[i][k] = 0;
                    }
                    safe_sequence[count++] = i;
                    finish[i] = 1;
                    found = 1;

                    printf("Process %d finished.\n", i);
                    print_status(num_resources, num_processes);
                }
            }
        }
        if (!found)
        {
            printf("System is in unsafe state.\n");
            break;
        }
    }

    if (count == num_processes)
    {
        printf("System is in safe state.\n");
        printf("Safe sequence: ");
        for (int i = 0; i < num_processes; i++)
        {
            printf("%d ", safe_sequence[i]);
        }
        printf("\n");
    }

    return 0;
}
