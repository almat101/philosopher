/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatta <amatta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 17:11:00 by amatta            #+#    #+#             */
/*   Updated: 2023/10/10 15:48:06 by amatta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <stdint.h>

typedef struct s_data
{
	int				died;
	int				num_philos;
	int				must_eat;
	int				finished_eat;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long			start_time;
	pthread_mutex_t print;
	pthread_mutex_t mutex_died;
}	t_data;

typedef struct s_fork
{
	pthread_mutex_t used;
}	t_fork;

typedef struct s_philo
{
	struct s_data	*data;
	int				id;
	int				meal_count;
	long			last_meal;
	t_fork			*l_fork;
	t_fork			*r_fork;
}	t_philo;

int		check_argc(int argc);
int		init_data(int argc, char **argv, t_data *data);
int		ft_is_space(char c);
long	ft_atolplus(const char *str);
long	get_timestamp(void);
void	ft_usleep(long int ms);
int		start_philos(t_data *data, t_philo **philo, t_fork **forks);
void	init_philos(t_data *data, t_philo *philo, t_fork **forks, int i);
// void	has_taken_a_fork(t_philo *philo);
// void	release_fork(t_philo *philo);
// void	is_eating(t_philo *philo);
// void	is_sleeping(t_philo *philo);
// void	is_thinking(t_philo *philo);
// void	*routine(void *arg);
// void    *monitor_life (void *arg);

#endif

