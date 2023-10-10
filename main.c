/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatta <amatta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 17:10:55 by amatta            #+#    #+#             */
/*   Updated: 2023/10/10 15:58:11 by amatta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char *argv[])
{
	t_data	data;
	t_philo	*philo;
	t_fork	*forks;
	int		exit;

	exit = 0;

	if (check_argc(argc) || init_data(argc, argv, &data))
		return (1);
	if (start_philos(&data, &philo, &forks))
		return (1);

	printf( "num of philo %d time to eat %d die %d sleep %d, data num eat %d\n", data.num_philos, data.time_to_eat, data.time_to_die, data.time_to_sleep, data.must_eat);
	int i = 0;

	while (i < data.num_philos)
	{
		printf("philo id %d", philo[i].id);
		printf(" philo num of eat %d\n", philo[i].data->time_to_die);

		i++;
	}
	return (exit);
}
