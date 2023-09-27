#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int meals = 0;
//pthread_mutex_t mutex;

void*	routine()
{
     //   pthread_mutex_lock(&mutex);
    for (int i = 0; i < 10000000; i++)
    {
      //  pthread_mutex_lock(&mutex);
        meals++;
       // pthread_mutex_unlock(&mutex);
    }
       // pthread_mutex_unlock(&mutex);
}



int main()
{
	pthread_t th[4];
	int i;
  //  pthread_mutex_init(&mutex, NULL);

	for (i = 0; i < 4; i++)
	{
		if (pthread_create(th + i, NULL, &routine, NULL ))
		{
			perror("failed creting a thread");
			return 1;
		}
		printf("thread %d created\n", i);
    }
	for (i = 0; i < 4; i++)
    {
     if (pthread_join(th[i] , NULL))
		return 2;
		printf("thread %d destroyed\n", i);
    }
    //pthread_mutex_destroy(&mutex);
    printf("numbers of meals: %d\n", meals);
}
