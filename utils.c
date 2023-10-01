/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 22:34:21 by ale               #+#    #+#             */
/*   Updated: 2023/10/01 17:16:56 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	
	while (1)
	{
	
		has_taken_a_fork(philo);
		is_eating(philo);
		release_fork(philo);
		is_sleeping(philo);
		is_thinking(philo);
	}
	return NULL;
}

void *monitor_life(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	int i;

	while (philo->died != 1)
	{
		i = 0;
		pthread_mutex_lock(&(philo->data->print));
		while (i < philo->data->num_philo)
		{
			if (get_timestamp() - philo[i].last_meal > philo->data->time_to_die)
			{
				printf("%zu %d died\n", (get_timestamp() - philo[i].data->start_time), philo[i].id);
				//implementa una condizione di uscita quando muore un filo al posto di exit(1) 
				exit(1);
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
