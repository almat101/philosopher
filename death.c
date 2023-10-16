/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatta <amatta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:24:53 by amatta            #+#    #+#             */
/*   Updated: 2023/10/16 14:51:52 by amatta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_one_death(t_philo *philo, long time)
{
	int		dead;
	long	last_meal_time;

	dead = 0;
	pthread_mutex_lock(&(philo->last_meal_mtx));
	last_meal_time = time - philo->last_meal;
	pthread_mutex_unlock(&(philo->last_meal_mtx));
	if (last_meal_time > philo->data->time_to_die)
	{
		pthread_mutex_lock(&(philo->data->mutex_died));
		philo->data->died = 1;
		pthread_mutex_unlock(&(philo->data->mutex_died));
		dead = 1;
		pthread_mutex_lock(&(philo->data->mutex_print));
		printf("%03ld %d died\n", time, philo->id);
		pthread_mutex_unlock(&(philo->data->mutex_print));
	}
	return (dead);
}

void	*routine_death(void *arg)
{
	t_philo		**philo;
	t_data		*data;
	long		timestamp;
	int			i;

	philo = (t_philo **)arg;
	data = philo[0]->data;
	while (1)
	{
		i = 0;
		timestamp = get_timestamp() - data->start_time;
		while (i < data->num_philos)
		{
			if (check_one_death(&(*philo)[i], timestamp))
				return (NULL);
			i++;
		}
	}
	return (NULL);
}

void	check_eated(t_philo *philo)
{
	if (philo->data->must_eat > 0 && ++philo->meals == philo->data->must_eat)
	{
		if (++philo->data->finished_all == philo->data->num_philos)
		{
			pthread_mutex_lock(&(philo->data->mutex_died));
			philo->data->died = 1;
			pthread_mutex_unlock(&(philo->data->mutex_died));
		}
	}
}

int	is_dead(t_philo *philo)
{
	int	died;

	pthread_mutex_lock(&(philo->data->mutex_died));
	died = philo->data->died;
	pthread_mutex_unlock(&(philo->data->mutex_died));
	return (died);
}
