/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 17:11:00 by amatta            #+#    #+#             */
/*   Updated: 2023/09/30 23:20:33 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>
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
    int             died;
    pthread_mutex_t mutex_end;
	size_t			last_meal;
    t_fork			*l_fork;
    t_fork			*r_fork;
}	t_philo;

typedef struct s_data
{

	int				num_philo;
    int             must_eat;
    int             finished_eat;
    size_t			time_to_die;
    size_t			time_to_eat;
    size_t			time_to_sleep;
    size_t			start_time;
    pthread_mutex_t print;
}	t_data;

size_t	get_timestamp(void);
void	ft_usleep(useconds_t time);
void	has_taken_a_fork(t_philo *philo);
void	release_fork(t_philo *philo);
void	is_eating(t_philo *philo);
void	is_sleeping(t_philo *philo);
void	is_thinking(t_philo *philo);
void	*routine(void *arg);
void    *monitor_life (void *arg);

#endif

