/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbourge <anbourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 13:01:22 by anbourge          #+#    #+#             */
/*   Updated: 2022/04/02 13:30:05 by anbourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init(t_arg *data, int argc, char **argv)
{
	data->death_end = 0;
	data->eat_end = 0;
	data->p_max = ft_atoi(argv[1], 0);
	data->t_die = (unsigned long long)ft_atoi(argv[2], 0);
	data->t_eat = (unsigned long long)ft_atoi(argv[3], 0);
	data->t_sleep = (unsigned long long)ft_atoi(argv[4], 0);
	if (argc == 6)
	{
		data->e_max = ft_atoi(argv[5], 0);
		if (data->e_max <= 0)
			return (1);
	}
	else
		data->e_max = -1;
	if (data->p_max < 1 || data->p_max > 210)
		return (1);
	if (ft_init_mutex(data))
		return (2);
	data->philo = malloc(sizeof(t_philo) * data->p_max);
	if (!data->philo)
		return (1);
	ft_init_philos(data);
	return (0);
}

void	ft_init_philos(t_arg *data)
{
	int	i;

	i = 0;
	while (i < data->p_max)
	{
		data->philo[i].p_id = i;
		data->philo[i].e_nbr = 0;
		data->philo[i].e_last = 0;
		data->philo[i].left_fork = i;
		data->philo[i].right_fork = (i + 1) % data->p_max;
		data->philo[i].data = data;
		i++;
	}
	return ;
}

int	ft_init_mutex(t_arg *data)
{
	int	i;

	i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->p_max);
	if (!data->fork)
		return (1);
	while (i < data->p_max)
	{
		if (pthread_mutex_init(&(data->fork[i]), NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&(data->write), NULL))
		return (1);
	if (pthread_mutex_init(&(data->lock_state), NULL))
		return (1);
	if (pthread_mutex_init(&(data->lock_eat), NULL))
		return (1);
	return (0);
}
