/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 23:09:19 by ale               #+#    #+#             */
/*   Updated: 2023/10/10 23:52:43 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_philo **philo, t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_timestamp();
	while (i < data->num_philos)
	{
		if (pthread_create(&((*philo)[i].th_life), NULL, routine, &((*philo)[i])))
			return (1);
		i++;
	}
	return (0);
}

int	wait_threads(t_philo **philo, t_data *data)
{
	int	i;
	int	return_code;

	i = 0;
	return_code = 0;
	while (i < data->num_philos)
	{
		if (pthread_join((*philo)[i].th_life, NULL))
			return_code = 1;
		i++;
	}
	return (return_code);
}
