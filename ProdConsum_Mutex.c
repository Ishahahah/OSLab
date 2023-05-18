#include <stdio.h>
#include <stdlib.h>
int mutex = 1;
int empty = 10, full = 0, x = 0; // added full variable
void producer()
{
    --mutex;
    ++full; // increment full instead of slots
    --empty;
    x++;
    printf("\nProducer produces "
           "item %d",
           x);
    ++mutex;
}
void consumer()
{
    --mutex;
    --full;
    ++empty;
    printf("\nConsumer consumes "
           "item %d",
           x);
    x--;
    ++mutex;
}
int main()
{
    int n, i;
    printf("\nName : Isha Dashetwar \n");
    printf("\n1. Press 1 for Producer"
           "\n2. Press 2 for Consumer"
           "\n3. Press 3 for Exit");
    for (i = 1; i > 0; i++)
    {
        printf("\nEnter your choice:");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            if ((mutex == 1) && (empty != 0))
            {
                producer();
            }
            else
            {
                printf("Buffer is full!");
            }
            break;
        case 2:
            if ((mutex == 1) && (full != 0))
            {
                consumer();
            }
            else
            {
                printf("Buffer is empty!");
            }
            break;
        case 3:
            exit(0);
            break;
        default: // added default case to handle invalid input
            printf("Invalid input!");
            break;
        }
    }
    return 0; // added return statement
}