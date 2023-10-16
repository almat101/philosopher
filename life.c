/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatta <amatta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 22:36:07 by ale               #+#    #+#             */
/*   Updated: 2023/10/16 14:45:36 by amatta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		ft_usleep(philo->data->time_to_eat);
	while (!is_dead(philo))
	{
		has_taken_a_fork(philo);
		is_eating(philo);
		release_fork(philo);
		is_sleeping(philo);
		is_thinking(philo);
	}
	return (NULL);
}

void	has_taken_a_fork(t_philo *philo)
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
	pthread_mutex_unlock(&(philo->r_fork->used));
	pthread_mutex_unlock(&(philo->l_fork->used));
	check_eated(philo);
}

void	is_eating(t_philo *philo)
{
	printf_philo(philo, "is eating\n");
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_lock(&(philo->last_meal_mtx));
	philo->last_meal = get_timestamp() - philo->data->start_time;
	pthread_mutex_unlock(&(philo->last_meal_mtx));
}

void	is_sleeping(t_philo *philo)
{
	printf_philo(philo, "is sleeping\n");
	ft_usleep(philo->data->time_to_sleep);
}
