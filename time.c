
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

size_t	get_useconds(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000000 + time.tv_usec);
}

void	ft_usleep(useconds_t time)
{
	size_t	t;

	t = get_useconds();
	while (get_useconds() - t < time)
		usleep(1);
}

int main()
{
	size_t start_time = get_useconds();

    // Define the durations for eating, sleeping, and thinking in microseconds
    size_t time_to_eat = 2000000;   // 2 seconds
    size_t time_to_sleep = 3000000; // 3 seconds
    size_t time_to_think = 1000000; // 1 second

    // Simulate a philosopher eating
    printf("Time: %zu microseconds, Philosopher is eating...\n", get_useconds() - start_time);
    ft_usleep(time_to_eat);

    // Simulate a philosopher sleeping
    printf("Time: %zu microseconds, Philosopher is sleeping...\n", get_useconds() - start_time);
    ft_usleep(time_to_sleep);

    // Simulate a philosopher thinking
    printf("Time: %zu microseconds, Philosopher is thinking...\n", get_useconds() - start_time);
    ft_usleep(time_to_think);

    size_t end_time = get_useconds();
    size_t total_time = end_time - start_time;

    printf("Total time elapsed: %zu microseconds\n", total_time);
}

