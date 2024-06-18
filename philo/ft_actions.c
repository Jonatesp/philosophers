/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbourge <anbourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:49:06 by anbourge          #+#    #+#             */
/*   Updated: 2022/03/31 13:37:17 by anbourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eating(t_philo *philo, t_arg *data)
{
	pthread_mutex_lock(&data->fork[philo->left_fork]);
	ft_printer(data, philo->p_id, "has taken a fork");
	if (data->p_max == 1)
	{
		ft_sleep(data->t_die, data);
		pthread_mutex_unlock(&data->fork[philo->left_fork]);
		return ;
	}
	pthread_mutex_lock(&data->fork[philo->right_fork]);
	ft_printer(data, philo->p_id, "has taken a fork");
	pthread_mutex_lock(&data->lock_eat);
	ft_printer(data, philo->p_id, "is eating");
	philo->e_last = ft_time();
	pthread_mutex_unlock(&data->lock_eat);
	ft_sleep(data->t_eat, data);
	philo->e_nbr++;
	pthread_mutex_unlock(&data->fork[philo->left_fork]);
	pthread_mutex_unlock(&data->fork[philo->right_fork]);
}

void	ft_death_check(t_arg *d)
{
	int	i;

	while (d->eat_end == 0)
	{
		i = -1;
		while (++i < d->p_max && d->death_end == 0)
		{
			pthread_mutex_lock(&d->lock_eat);
			if ((ft_time() - d->philo[i].e_last) > d->t_die)
			{
				ft_printer(d, d->philo[i].p_id, "died");
				d->death_end = 1;
			}
			pthread_mutex_unlock(&d->lock_eat);
			usleep(100);
		}
		if (d->death_end == 1)
			break ;
		i = 0;
		while (i < d->p_max && d->philo[i].e_nbr >= (d->e_max - 1)
			&& d->e_max != -1)
			i++;
		if (i == d->p_max)
			d->eat_end = 1;
	}
}
