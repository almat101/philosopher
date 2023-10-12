/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatta <amatta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 23:09:19 by ale               #+#    #+#             */
/*   Updated: 2023/10/12 12:40:40 by amatta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_philo **philo, t_data *data)
{
	int	i;

	data->start_time = get_timestamp();
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&((*philo)[i].life), NULL, routine,
				&((*philo)[i])))
			return (0);
		i++;
	}
	if (pthread_create(&(data->death), NULL, routine_death, philo))
		return (0);
	return (1);
}

int	wait_threads(t_philo **philo, t_data *data)
{
	int	i;
	int	return_code;

	i = 0;
	return_code = 1;
	while (i < data->num_philos)
	{
		if (pthread_join((*philo)[i].life, NULL))
			return_code = 0;
		i++;
	}
	if (pthread_detach((*philo)->data->death))
		return_code = 0;
	return (return_code);
}

int	stop_threads(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->mutex_died));
	philo->data->died = 1;
	pthread_mutex_unlock(&(philo->data->mutex_died));
	return (EXIT_FAILURE);
}
