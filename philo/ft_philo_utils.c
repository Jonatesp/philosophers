/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbourge <anbourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 13:28:08 by anbourge          #+#    #+#             */
/*   Updated: 2022/01/04 15:27:03 by anbourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_atoi(const char *nptr, int j)
{
	long long	res;
	long long	n;
	int			i;

	n = 1;
	res = 0;
	i = j;
	while (nptr[i] && (nptr[i] == ' ' || nptr[i] == '\n' || nptr[i] == '\t'
			|| nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r'))
		i++;
	if (nptr[i] == '-')
		n = -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - 48);
		i++;
	}
	return (res * n);
}

unsigned long long	ft_time(void)
{
	struct timeval		time;
	unsigned long long	ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (ms);
}

void	ft_printer(t_arg *data, int id, char *action)
{
	pthread_mutex_lock(&data->write);
	if (data->death_end == 0)
		printf("%llu %d %s\n", ft_time() - data->t_start, id + 1, action);
	pthread_mutex_unlock(&data->write);
}

void	ft_sleep(unsigned long long time, t_arg *data)
{
	unsigned long long	start;

	start = ft_time();
	while (data->death_end == 0)
	{
		if (ft_time() - start >= time)
			break ;
		usleep(50);
	}
}
