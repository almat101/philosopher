/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatta <amatta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 17:10:55 by amatta            #+#    #+#             */
/*   Updated: 2023/10/16 12:41:46 by amatta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data	data;
	t_philo	*philo;
	t_fork	*fork;
	int		return_code;

	return_code = EXIT_SUCCESS;
	if (!check_argc(argc))
		return (EXIT_FAILURE);
	if (!init_data(argv, &data) || !init_data2(argc, argv, &data))
		return (EXIT_FAILURE);
	if (!start_philos(&philo, &fork, &data))
		return (EXIT_FAILURE);
	if (!create_threads(&philo, &data))
		return (stop_threads(&philo[0]));
	if (!wait_threads(&philo, &data))
		return (ft_free(philo, &data, fork, EXIT_FAILURE));
	return (ft_free(philo, &data, fork, return_code));
}
