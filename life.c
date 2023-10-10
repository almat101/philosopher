/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 22:36:07 by ale               #+#    #+#             */
/*   Updated: 2023/10/10 23:42:07 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		has_taken_a_fork(philo);
		is_eating(philo);
		release_fork(philo);
		is_sleeping(philo);
		is_thinking(philo);
	}
	return (NULL);
}


void has_taken_a_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&(philo->l_fork->used));
		printf("%lu %d has taken a fork\n", (get_timestamp() - philo->data->start_time), philo->id);
		pthread_mutex_lock(&(philo->r_fork->used));
		printf("%lu %d has taken a fork\n", (get_timestamp() - philo->data->start_time), philo->id);
	}
	else
	{
		pthread_mutex_lock(&(philo->r_fork->used));
		printf("%lu %d has taken a fork\n", (get_timestamp() - philo->data->start_time), philo->id);
		pthread_mutex_lock(&(philo->l_fork->used));
		printf("%lu %d has taken a fork\n", (get_timestamp() - philo->data->start_time), philo->id);
	}
}

void release_fork(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->l_fork->used));
	pthread_mutex_unlock(&(philo->r_fork->used));
}

void is_eating(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->print));
	printf("%lu %d is eating\n", (get_timestamp() - philo->data->start_time), philo->id);
	philo->last_meal = get_timestamp();
	pthread_mutex_unlock(&(philo->data->print));
	ft_usleep(philo->data->time_to_eat);
}

void is_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->print));
	printf("%lu %d is sleeping\n", (get_timestamp() - philo->data->start_time), philo->id);
	pthread_mutex_unlock(&(philo->data->print));
	ft_usleep(philo->data->time_to_sleep);
}

void is_thinking(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->print));
	printf("%lu %d is thinking\n", (get_timestamp() - philo->data->start_time), philo->id);
	pthread_mutex_unlock(&(philo->data->print));
}
