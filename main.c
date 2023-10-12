/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatta <amatta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 17:10:55 by amatta            #+#    #+#             */
/*   Updated: 2023/10/12 15:53:57 by amatta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char *argv[])
{
	t_data	data;
	t_philo	*philo;
	t_fork	*fork;
	int		return_code;

	return_code = EXIT_SUCCESS;

	if (!check_argc(argc) || !init_data(argc, argv, &data))
		return (EXIT_FAILURE);
	if (!start_philos(&philo, &data, &fork))
		return (EXIT_FAILURE);
	if (!create_threads(&philo, &data))
		return (stop_threads(&philo[0]));
	if (!wait_threads(&philo, &data))
		return (ft_free(philo, fork, EXIT_FAILURE));

	// int i = 0;

	// while (i < data.num_philos)
	// {
	// 	printf("philo id %d", philo[i].id);
	// 	printf(" philo start time %lu\n", philo[i].data->start_time);
	// 	i++;
	// }
	return (return_code);
}
