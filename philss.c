#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct s_fork
{
    pthread_mutex_t used;
}       t_fork;

typedef struct s_philo{
    struct s_data *data;
    int id;
    pthread_mutex_t forks;
    t_fork *l_fork;
    t_fork *r_fork;
}   t_philo;

typedef struct s_data
{
    size_t  time_to_die;
    size_t  time_to_eat;
    size_t  time_to_sleep;
    size_t  start_time;
}   t_data;

size_t	get_timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000000 + time.tv_usec);
}

void	ft_usleep(useconds_t time)
{
	size_t	t;

	t = get_timestamp();
	while (get_timestamp() - t < time)
		usleep(1);
}


void has_taken_a_fork(t_philo *philo)
{
    if (philo->id  % 2 == 0)
    {
        pthread_mutex_lock(&(philo->l_fork->used));
        printf("%zu %d has taken l fork\n", (get_timestamp() - philo->data->start_time) / 1000,philo->id);
        pthread_mutex_lock(&(philo->r_fork->used));
        printf("%zu %d has taken r fork\n",(get_timestamp() - philo->data->start_time) / 1000, philo->id);
    }
    else
    {
        pthread_mutex_lock(&(philo->r_fork->used));
        printf("%zu %d has taken r fork\n", (get_timestamp() - philo->data->start_time) / 1000,philo->id);
        pthread_mutex_lock(&(philo->l_fork->used));
        printf("%zu %d has taken l fork\n", (get_timestamp() - philo->data->start_time) / 1000,philo->id);
    }
}

void    release_fork(t_philo *philo)
{
    pthread_mutex_unlock(&(philo->l_fork->used));
    pthread_mutex_unlock(&(philo->r_fork->used));
}

void is_eating(t_philo *philo)
{
    printf("%zu %d is eating\n",(get_timestamp() - philo->data->start_time) / 1000, philo->id);
    ft_usleep(philo->data->time_to_eat);
}

void is_sleeping(t_philo *philo)
{
    printf("%zu %d is sleeping\n",(get_timestamp() - philo->data->start_time) / 1000, philo->id);
    ft_usleep(philo->data->time_to_sleep);
}

void is_thinking(t_philo *philo)
{
    printf("%zu %d is thinking\n", (get_timestamp() - philo->data->start_time)/ 1000, philo->id);
}
void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    while (1) {

        //ft_usleep(philo->time_to_think);
        has_taken_a_fork(philo);
        is_eating(philo);
        release_fork(philo);
        is_sleeping(philo);
        is_thinking(philo);

       //ft_usleep(philo->time_to_think);
    }

    return NULL;
}

int main(int argc, char *argv[]) {



    if (argc != 2)
    {
        printf("Uso: %s <num_philo>\n", argv[0]);
        return 1;
    }

    int num_philo = atoi(argv[1]);
    if (num_philo <= 0)
    {
        printf("Inserisci un numero valido di philo.\n");
        return 1;
    }

    pthread_t thread_id[num_philo];
    t_philo philo[num_philo];
    t_fork forks[num_philo];
    t_data data;

    data.time_to_die = 3000000;   // 3 seconds
    data.time_to_eat = 1000000; // 1 seconds
    data.time_to_sleep = 1000000; // 1 seconds
    data.start_time = get_timestamp();

    // Inizializzazione delle forks
    for (int i = 0; i < num_philo; i++)
    {
        pthread_mutex_init(&(forks[i].used), NULL);
    }


    // Creazione dei philo
    for (int i = 0; i < num_philo; i++)
    {
        philo[i].data = &data;
        philo[i].id = i + 1;
        philo[i].l_fork = &forks[i];
        philo[i].r_fork = &forks[(i + 1) % num_philo];
        pthread_create(&thread_id[i], NULL, routine, &philo[i]);
    }

    // Attendi la terminazione dei philo
    for (int i = 0; i < num_philo; i++)
    {
        pthread_join(thread_id[i], NULL);
    }

    // Distruggi i mutex delle forks
    for (int i = 0; i < num_philo; i++)
    {
        pthread_mutex_destroy(&(forks[i].used));
    }

    return 0;
}
