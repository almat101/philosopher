/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 22:36:07 by ale               #+#    #+#             */
/*   Updated: 2023/09/30 23:30:21 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void has_taken_a_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		int result = pthread_mutex_lock(&(philo->l_fork->used));
		if (result != 0)
		{
			fprintf(stderr, " error locking mutex %d\n", result);
		}

		printf("%zu %d has taken a fork\n", (get_timestamp() - philo->data->start_time), philo->id);

		result = pthread_mutex_lock(&(philo->r_fork->used));
		if (result != 0)
		{
			fprintf(stderr, " error locking mutex %d\n", result);
		}

		// pthread_mutex_lock(&(philo->r_fork->used));
		printf("%zu %d has taken a fork\n", (get_timestamp() - philo->data->start_time), philo->id);
	}
	else
	{
		pthread_mutex_lock(&(philo->r_fork->used));
		printf("%zu %d has taken a fork\n", (get_timestamp() - philo->data->start_time), philo->id);
		pthread_mutex_lock(&(philo->l_fork->used));
		printf("%zu %d has taken a fork\n", (get_timestamp() - philo->data->start_time), philo->id);
	}
}

void release_fork(t_philo *philo)
{
	int result = pthread_mutex_unlock(&(philo->l_fork->used));
	if (result != 0)
	{
		fprintf(stderr, " error unlocking mutex %d\n", result);
	}

	pthread_mutex_unlock(&(philo->r_fork->used));
}

void is_eating(t_philo *philo)
{
	// ricorda di inizializzare il mutex per printare
	int result = pthread_mutex_lock(&(philo->data->print));

	if (result != 0)
	{
		fprintf(stderr, " error locking mutex %d\n", result);
	}
	printf("%zu %d is eating\n", (get_timestamp() - philo->data->start_time), philo->id);
	// pthread_mutex_lock(&philo->last_meal_mtx);
	philo->last_meal = get_timestamp();
	result = pthread_mutex_unlock(&(philo->data->print));

	if (result != 0)
	{
		fprintf(stderr, " error locking mutex %d\n", result);
	}

	// pthread_mutex_unlock(&(philo->data->print));
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
			philo->died = 1;
		}
	}
	// pthread_mutex_unlock(&philo->last_meal_mtx);
	ft_usleep(philo->data->time_to_eat);
}

void is_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->print));
	printf("%zu %d is sleeping\n", (get_timestamp() - philo->data->start_time), philo->id);
	pthread_mutex_unlock(&(philo->data->print));
	ft_usleep(philo->data->time_to_sleep);
}

void is_thinking(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->print));
	printf("%zu %d is thinking\n", (get_timestamp() - philo->data->start_time), philo->id);
	pthread_mutex_unlock(&(philo->data->print));
}
