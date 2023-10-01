/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 22:34:21 by ale               #+#    #+#             */
/*   Updated: 2023/10/01 00:27:46 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		if (philo->died)
			exit(1);
	}
	return NULL;
}

void	stop_thread(t_philo *philo)
{
	int result = pthread_mutex_lock(&philo->mutex_end);

	if (result != 0)
	{
		fprintf(stderr, " mutex end fail %d\n", result);
	}
    philo->died = 1;
	ft_usleep(2000);
    result = pthread_mutex_unlock(&philo->mutex_end);
	if (result != 0)
	{
		fprintf(stderr, " error unlocking mutex endddddd %d\n", result);
	}
}

void *monitor_life(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	int i;

	while (1)
	{
		i = 0;
		pthread_mutex_lock(&(philo->data->print));
		while (i < philo->data->num_philo)
		{
			if (get_timestamp() - philo[i].last_meal > philo->data->time_to_die)
			{
				printf("%zu %d died\n", (get_timestamp() - philo[i].data->start_time), philo[i].id); // inserire una variabile dead=1
				philo[i].died = 1;
			}
			i++;
		}
		pthread_mutex_unlock(&(philo->data->print));
		usleep(1000);
	}
	return NULL;
}

size_t get_timestamp(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + (time.tv_usec / 1000));
}

void ft_usleep(useconds_t time)
{
	size_t t;

	t = get_timestamp();
	while (get_timestamp() - t < time)
		usleep(1);
}
