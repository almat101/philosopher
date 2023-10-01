/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale <ale@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 17:10:55 by amatta            #+#    #+#             */
/*   Updated: 2023/09/30 23:24:47 by ale              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char *argv[])
{

	if (argc != 5 && argc != 6)
	{
		printf("%s <num_philo> <time_to_die> <time_to_eat> <time_to_sleep>\n", argv[0]);
		return 0;
	}

	int num_philo = atoi(argv[1]);
	if (num_philo <= 0)
	{
		printf("Inserisci un numero valido di philo.\n");
		return 1;
	}

	pthread_t thread_id[num_philo];
	t_philo philo[num_philo];
	t_fork forks[num_philo];
	t_data data;

	// monitor_thread_id
	pthread_t monitor_thread_id;

	data.num_philo = atoi(argv[1]);
	data.time_to_die = atoi(argv[2]);
	data.time_to_eat = atoi(argv[3]);
	data.time_to_sleep = atoi(argv[4]);
	data.must_eat = -1;
	data.finished_eat = 0;
	pthread_mutex_init(&data.print, NULL);
	if (argc == 6)
	{
		// data.must_eat_provided = 1;
		data.must_eat = atoi(argv[5]);
	}
	data.start_time = get_timestamp();
	// data.is_dead = 0;

	// Inizializzazione delle forks
	for (int i = 0; i < num_philo; i++)
	{
		pthread_mutex_init(&(forks[i].used), NULL);
		usleep(10);
	}

	// Creazione dei philo
	for (int i = 0; i < num_philo; i++)
	{
		philo[i].data = &data;
		philo[i].id = i + 1;
		philo[i].l_fork = &forks[i];
		philo[i].r_fork = &forks[(i + 1) % num_philo];
		philo[i].last_meal = get_timestamp();
		philo[i].num_of_eat = 0;
		philo[i].died = 0;
		pthread_mutex_init(&philo[i].mutex_end, NULL);
		pthread_create(&thread_id[i], NULL, routine, &philo[i]);
	}

	pthread_create(&monitor_thread_id, NULL, monitor_life, philo);

	// Attendi la terminazione dei philo
	for (int i = 0; i < num_philo; i++)
	{
		pthread_join(thread_id[i], NULL);
	}

	// Wait for the monitor thread to finish
	pthread_join(monitor_thread_id, NULL);

	// Distruggi i mutex delle forks e mtxend = ft_exit
	for (int i = 0; i < num_philo; i++)
	{
		pthread_mutex_destroy(&(forks[i].used));
		pthread_mutex_destroy(&philo[i].mutex_end);
	}

	//distruzione mutex print
	pthread_mutex_destroy(&data.print);
	return 0;
}
