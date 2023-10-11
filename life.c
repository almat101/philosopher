/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatta <amatta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 22:36:07 by ale               #+#    #+#             */
/*   Updated: 2023/10/11 11:27:39 by amatta           ###   ########.fr       */
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
		printf_philo(philo, "has taken a fork\n");
		pthread_mutex_lock(&(philo->r_fork->used));
		printf_philo(philo, "has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(&(philo->r_fork->used));
		printf_philo(philo, "has taken a fork\n");
		pthread_mutex_lock(&(philo->l_fork->used));
		printf_philo(philo, "has taken a fork\n");
	}
}

void	release_fork(t_philo *philo)
{
	if (philo->id %2 == 0)
	{
	pthread_mutex_unlock(&(philo->l_fork->used));
	pthread_mutex_unlock(&(philo->r_fork->used));
	}
	else
	{
	pthread_mutex_unlock(&(philo->r_fork->used));
	pthread_mutex_unlock(&(philo->l_fork->used));
	}
}

void is_eating(t_philo *philo)
{
	printf_philo(philo, "is eating\n");
	ft_usleep(philo->data->time_to_eat);
	philo->last_meal = get_timestamp() - philo->data->start_time;
}

void is_sleeping(t_philo *philo)
{
	printf_philo(philo, "is sleeping\n");
	ft_usleep(philo->data->time_to_sleep);
}

void is_thinking(t_philo *philo)
{
	printf_philo(philo, "is thinking\n");
}
