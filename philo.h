/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatta <amatta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 17:11:00 by amatta            #+#    #+#             */
/*   Updated: 2023/10/16 14:47:43 by amatta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <stdint.h>
# include <string.h>

typedef struct s_data
{
	int				died;
	int				num_philos;
	int				finished;
	int				finished_all;
	long			start_time;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_died;
	pthread_t		death;
}	t_data;

typedef struct s_fork
{
	pthread_mutex_t	used;
}	t_fork;

typedef struct s_philo
{
	struct s_data	*data;
	int				id;
	int				meals;
	long			last_meal;
	t_fork			*l_fork;
	t_fork			*r_fork;
	pthread_t		life;
	pthread_mutex_t	last_meal_mtx;
}	t_philo;

int		check_argc(int argc);
int		init_data( char **argv, t_data *data);
int		init_data2(int argc, char **argv, t_data *data);
int		ft_is_space(char c);
long	ft_atolplus(const char *str);
long	get_timestamp(void);
void	ft_usleep(long int ms);
int		start_philos(t_philo **philo, t_fork **fork, t_data *data);
void	init_philos(t_philo *philo, t_fork **fork, t_data *data, int i);
int		create_threads(t_philo **philo, t_data *data);
int		wait_threads(t_philo **philo, t_data *data);
void	has_taken_a_fork(t_philo *philo);
void	release_fork(t_philo *philo);
void	is_eating(t_philo *philo);
void	is_sleeping(t_philo *philo);
void	is_thinking(t_philo *philo);
void	printf_philo(t_philo *philo, char *msg);
void	*routine(void *arg);
void	*routine_death(void *arg);
int		ft_free(t_philo *philo, t_fork *fork, int return_code);
int		check_one_death(t_philo *philo, long time);
int		is_dead(t_philo *philo);
int		stop_threads(t_philo *philo);
void	check_eated(t_philo *philo);

#endif
