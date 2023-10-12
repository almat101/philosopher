/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatta <amatta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:10:05 by amatta            #+#    #+#             */
/*   Updated: 2023/10/12 16:37:41 by amatta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_argc(int argc)
{
	if (argc != 5 && argc != 6)
	{
		write(2, "Error invalid args\n", 20);
		return (0);
	}
	return (1);
}

int	init_data(int argc, char **argv, t_data *data)
{
	data->num_philos = ft_atolplus(argv[1]);
	data->time_to_die =ft_atolplus(argv[2]);
	data->time_to_eat = ft_atolplus(argv[3]);
	data->time_to_sleep = ft_atolplus(argv[4]);
	data->num_meals = 0;
	data->must_eat = -1;
	data->died = 0;
	data->start_time = get_timestamp();
	if (data->num_philos == 1)
	{
		printf("000 1 has taken a fork\n");
		printf("%d 1 died\n", data->time_to_die + 1);
		return (0);
	}
	if (argc == 6)
		data->must_eat = ft_atolplus(argv[5]);
	if (data->num_philos < 1 || data->time_to_die < 1 || data->time_to_eat < 1 \
	 || data->time_to_sleep < 1 || (argc == 6 && data->must_eat < 1))
	{
		write(2, "Error invalid args\n", 20);
		return (0);
	}
	pthread_mutex_init(&data->mutex_print, NULL);
	pthread_mutex_init(&data->mutex_died, NULL);
	return (1);
}

void	init_philo(t_philo *philo, t_data *data, t_fork **fork, int i)
{
	philo->id = i + 1;
	philo->data = data;
	philo->meals = 0;
	philo->last_meal = 0;
	philo->l_fork = &((*fork)[i]);
	philo->r_fork = &((*fork)[(i + 1) % data->num_philos]);
	pthread_mutex_init(&(philo->l_fork->used), NULL);
	pthread_mutex_init(&(philo->r_fork->used), NULL);
	pthread_mutex_init(&(philo->last_meal_mtx), NULL);
}

int	start_philos( t_philo **philo, t_data *data, t_fork **fork)
{
	int	i;

	*philo = (t_philo *)malloc(sizeof(t_philo) * data->num_philos);
	if (!(*philo))
		return (1);
	*fork = (t_fork *)malloc(sizeof(t_philo) * data->num_philos);
	if (!(*fork))
		{
			free(philo);
			return (0);
		}
	i = 0;
	while (i < data->num_philos)
	{
		init_philo(&(*philo)[i], data, fork, i);
		i++;
	}
	return (1);
}

