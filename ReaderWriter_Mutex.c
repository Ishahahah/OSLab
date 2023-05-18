#include <stdio.h>
#include <stdbool.h>
struct semaphore
{
    int mutex;
    int rcount;
    int rwait;
    bool wrt;
};
void addR(struct semaphore *s)
{
    if (s->mutex == 0 && s->rcount == 0)
    {
        printf("\nSorry, File open in Write mode.\nNew Reader added to queue.\n");
        s->rwait++;
    }
    else
    {
        printf("\nReader Process added.\n");
        s->rcount++;
        s->mutex--;
    }
    return;
}
void addW(struct semaphore *s)
{
    if (s->mutex == 1)
    {
        s->mutex--;
        s->wrt = 1;
        printf("\nWriter Process added.\n");
    }
    else if (s->wrt)
        printf("\nSorry, Writer already operational.\n");
    else
        printf("\nSorry, File open in Read mode.\n");
    return;
}
void remR(struct semaphore *s)
{
    if (s->rcount == 0)
        printf("\nNo readers to remove.\n");
    else
    {
        printf("\nReader Removed.\n");
        s->rcount--;
        s->mutex++;
    }
    return;
}
void remW(struct semaphore *s)
{
    if (s->wrt == 0)
        printf("\nNo Writer to Remove");
    else
    {
        printf("\nWriter Removed\n");
        s->mutex++;
        s->wrt = 0;
        if (s->rwait != 0)
        {
            s->mutex -= s->rwait;
            s->rcount = s->rwait;
            s->rwait = 0;
            printf("%d waiting Readers Added.", s->rcount);
        }
    }
}
int main()
{
    struct semaphore S1 = {1, 0, 0};
    printf("\nName : Prajwal Korade\n");
    while (1)
    {
        printf("Options :-\n1.Add Reader.\n2.Add Writer.\n3.Remove Reader.\n4.Remove Writer.\n5.Exit.\n\n\tChoice : ");
        int ch;
        scanf("%d",&ch);
        switch(ch)
        {
                case 1:
                    addR(&S1);
                    break;
                case 2:
                    addW(&S1);
                    break;
                case 3:
                    remR(&S1);
                    break;
                case 4:
                    remW(&S1);
                    break;
                case 5:
                    getch();
                    return 0;
                default:
                    printf("\nInvalid Entry!");
                    continue;
        }
        printf("\nCurrently->\n\tMutex\t\t:\t%d\n\tActive Readers\t:\t%d\n\tWaiting Readers\t:\t%d\n\tWriter Active\t:\t%s\n\n",S1.mutex, S1.rcount, S1.rwait, 
        (S1.mutex==0 && S1.rcount==0)? "YES" : "NO");
    }
}
