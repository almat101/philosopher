/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatta <amatta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 17:10:55 by amatta            #+#    #+#             */
/*   Updated: 2023/09/29 17:25:04 by amatta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// u_int64_t	get_timestamp(void)
// {
// 	struct timeval	tv;

// 	gettimeofday(&tv, NULL);
// 	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
// }

// void	ft_usleep(u_int64_t time)
// {
// 	u_int64_t	start;

// 	start = get_timestamp();
// 	while ((get_timestamp() - start) < time)
// 		usleep(time / 10);
// }


size_t  get_timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + (time.tv_usec / 1000));
}

void    ft_usleep(useconds_t time)
{
	size_t	t;

	t = get_timestamp();
	while (get_timestamp() - t < time)
		usleep(1);
}


void    has_taken_a_fork(t_philo *philo)
{
    if (philo->id  % 2 == 0)
    {
        pthread_mutex_lock(&(philo->l_fork->used));
        printf("%zu %d has taken a fork\n", (get_timestamp() - philo->data->start_time) ,philo->id);
        pthread_mutex_lock(&(philo->r_fork->used));
        printf("%zu %d has taken a fork\n",(get_timestamp() - philo->data->start_time) , philo->id);
    }
    else
    {
        pthread_mutex_lock(&(philo->r_fork->used));
        printf("%zu %d has taken a fork\n", (get_timestamp() - philo->data->start_time) ,philo->id);
        pthread_mutex_lock(&(philo->l_fork->used));
        printf("%zu %d has taken a fork\n", (get_timestamp() - philo->data->start_time) ,philo->id);
    }
}

void    release_fork(t_philo *philo)
{
    pthread_mutex_unlock(&(philo->l_fork->used));
    pthread_mutex_unlock(&(philo->r_fork->used));
}

void    is_eating(t_philo *philo)
{
    pthread_mutex_lock(&(philo->data->print));
    printf("%zu %d is eating\n",(get_timestamp() - philo->data->start_time) , philo->id);
    //pthread_mutex_lock(&philo->last_meal_mtx);
    philo->last_meal = get_timestamp();
    pthread_mutex_unlock(&(philo->data->print));
    if (philo->data->must_eat)
    {
        philo->num_of_eat++;
       // printf("merdaaaaaaaaaa non deve mangiare\n");
    }
   // printf("%d philo num, %d num of eat %d must_eat\n ",philo->id,  philo->num_of_eat, philo->data->must_eat);
    if (philo->num_of_eat >= philo->data->must_eat && philo->data->must_eat != -1) //  != e un check importante senno usciva subito
    {
        philo->data->finished_eat++;
       // printf("data finished eat  %d  >= data  must_eat %d\n", philo->data->finished_eat ,philo->data->must_eat);
        if (philo->data->finished_eat >= philo->data->num_philo)
        {
            printf("reached must eat times! that is %d", philo->data->must_eat);

            exit(1);
        }
    }
    //pthread_mutex_unlock(&philo->last_meal_mtx);
    ft_usleep(philo->data->time_to_eat);
}

void    is_sleeping(t_philo *philo)
{
    pthread_mutex_lock(&(philo->data->print));
    printf("%zu %d is sleeping\n",(get_timestamp() - philo->data->start_time) , philo->id);
    pthread_mutex_unlock(&(philo->data->print));
    ft_usleep(philo->data->time_to_sleep);
}

void    is_thinking(t_philo *philo)
{
    pthread_mutex_lock(&(philo->data->print));
    printf("%zu %d is thinking\n", (get_timestamp() - philo->data->start_time), philo->id);
    pthread_mutex_unlock(&(philo->data->print));
}

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    while (1) // dead != 1 aggiungere riga 92 e toglierlo da la
    {
        has_taken_a_fork(philo);
        is_eating(philo);
        release_fork(philo);
        is_sleeping(philo);
        is_thinking(philo);
    }
    return NULL;
}

void    *monitor_thread_is_dead (void *arg)
{
    t_philo *philo = (t_philo *)arg;
    int i;

    while (1)
    {
        i = 0;
        //pthread_mutex_lock(&(philo->last_meal_mtx));
        pthread_mutex_lock(&(philo->data->print));
        while (i < philo->data->num_philo)
        {
            if (get_timestamp() - philo[i].last_meal > philo->data->time_to_die)
            {
                printf("%zu %d died\n", (get_timestamp() - philo[i].data->start_time) , philo[i].id);  //inserire una variabile dead=1
                exit(1);
            }
            i++;
        }
        //pthread_mutex_unlock(&(philo->last_meal_mtx));
        pthread_mutex_unlock(&(philo->data->print));
        usleep(1000);
    }
    return NULL;
}

int main(int argc, char *argv[]) {

    if (argc != 5 && argc != 6)
    {
        printf("%s <num_philo> <time_to_die> <time_to_eat> <time_to_sleep>\n", argv[0]);
        return 0;
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

    //monitor_thread_id
    pthread_t monitor_thread_id;


    data.num_philo = atoi(argv[1]);
    data.time_to_die = atoi(argv[2]);
    data.time_to_eat = atoi(argv[3]);
    data.time_to_sleep = atoi(argv[4]);
    data.must_eat = -1;
    data.finished_eat = 0;
    if (argc == 6)
        {
            //data.must_eat_provided = 1;
            data.must_eat = atoi(argv[5]);
        }
    data.start_time = get_timestamp();
    //data.is_dead = 0;

    // Inizializzazione delle forks
    for (int i = 0; i < num_philo; i++)
    {
        pthread_mutex_init(&(forks[i].used), NULL);
        usleep(10);
    }


    // Creazione dei philo
    for (int i = 0; i < num_philo; i++)
    {
        philo[i].data = &data;
        philo[i].id = i + 1;
        philo[i].l_fork = &forks[i];
        philo[i].r_fork = &forks[(i + 1) % num_philo];
        philo[i].last_meal = get_timestamp();
        philo[i].num_of_eat = 0;
        pthread_create(&thread_id[i], NULL, routine, &philo[i]);
    }

    pthread_create(&monitor_thread_id, NULL, monitor_thread_is_dead, philo);

    // Attendi la terminazione dei philo
    for (int i = 0; i < num_philo; i++)
    {
        pthread_join(thread_id[i], NULL);
    }

    // Wait for the monitor thread to finish
    pthread_join(monitor_thread_id, NULL);


    // Distruggi i mutex delle forks  ft_exit
    for (int i = 0; i < num_philo; i++)
    {
        pthread_mutex_destroy(&(forks[i].used));
    }

    return 0;
}
