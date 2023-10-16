/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatta <amatta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:19:11 by amatta            #+#    #+#             */
/*   Updated: 2023/10/16 12:44:02 by amatta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_thinking(t_philo *philo)
{
	printf_philo(philo, "is thinking\n");
}

int	check_argc(int argc)
{
	if (argc != 5 && argc != 6)
	{
		write(2, "Error invalid args\n", 20);
		return (0);
	}
	return (1);
}

void	printf_philo(t_philo *philo, char *msg)
{
	long	time;

	time = get_timestamp() - philo->data->start_time;
	pthread_mutex_lock(&(philo->data->mutex_print));
	if (!is_dead(philo))
		printf("%03ld %d %s", time, philo->id, msg);
	pthread_mutex_unlock(&(philo->data->mutex_print));
}

int	ft_free(t_philo *philo, t_data *data, t_fork *fork, int return_code)
{
	free(philo);
	free(fork);
	free(data->fork_status);
	return (return_code);
}
