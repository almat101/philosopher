/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amatta <amatta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 22:34:21 by ale               #+#    #+#             */
/*   Updated: 2023/10/16 12:43:32 by amatta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_space(char c)
{
	if (c == ' ' || c == '\f' || c == '\n' || c == '\r'
		|| c == '\t' || c == '\v')
		return (1);
	return (0);
}

long	ft_atolplus(const char *str)
{
	long	res;

	res = 0;
	while (ft_is_space(*str))
		str++;
	if (*str == '-')
		return (-1);
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
	}
	if (res > 2147483647)
		return (-1);
	return (res);
}

long	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long int ms)
{
	long int	start_time;

	start_time = 0;
	start_time = get_timestamp();
	while ((get_timestamp() - start_time) < ms)
		usleep(100);
}
