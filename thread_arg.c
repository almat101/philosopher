#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int num[10] = {0,1,2,3,4,5,6,7,8,9};

void *routine(void *arg)
{
    int index = *(int *)arg;
    printf("%d\n", num[index]);
    //free(arg);
}




int main()
{
    pthread_t th[10];
    int i;

    for (i = 0; i < 10; i++)
    {
        //int *a = malloc(sizeof(int));
        //*a = i;
        if(pthread_create(&th[i], NULL, &routine, num + i) != 0)
        {
            perror("thread failed to create");
            return 127;
        }
        printf("th + i %p\n", th + i);
        printf("num + i %p\n", num + i);
        
        printf("num is %p, i is  %d\n", num, i);
    }
    for (i = 0; i < 10; i++)
    {
        if(pthread_join(th[i], NULL) != 0)
        {
            perror("thread faileed to join");
            return 127;
        }
    }
}
