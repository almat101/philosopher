#ifndef PHILO_H
#define PHILO_H

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

typedef struct s_philo
{

    struct s_data	*data;
    int				id;
    int             num_of_eat;
	size_t			last_meal;
    pthread_mutex_t last_meal_mtx;
    pthread_mutex_t	forks;
    t_fork			*l_fork;
    t_fork			*r_fork;
}	t_philo;

typedef struct s_data
{
	int				*is_dead;  // int to check if a philo is dead
	int				num_philo;
	pthread_mutex_t	lock;     // mutex for dead
    pthread_mutex_t print;    // mutex for print an action
    size_t			time_to_die;
    size_t			time_to_eat;
    size_t			time_to_sleep;
    size_t			start_time;
    int             must_eat;
    int             finished_eat;
}	t_data;

size_t	get_timestamp(void);
void	ft_usleep(useconds_t time);
void	has_taken_a_fork(t_philo *philo);
void	release_fork(t_philo *philo);
void	is_eating(t_philo *philo);
void	is_sleeping(t_philo *philo);
void	is_thinking(t_philo *philo);
void	*routine(void *arg);
void    *monitor_thread_is_dead (void *arg);

#endif

