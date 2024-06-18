/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbourge <anbourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 15:14:39 by anbourge          #+#    #+#             */
/*   Updated: 2022/04/02 13:35:03 by anbourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_philo(void *p_data)
{
	t_philo	*philo;
	t_arg	*data;

	philo = (t_philo *)p_data;
	data = philo->data;
	if (philo->p_id % 2)
		usleep(15000);
	while (data->death_end == 0)
	{
		if (data->e_max == data->philo[philo->p_id].e_nbr)
			break ;
		ft_eating(philo, data);
		if (data->eat_end == 1)
			break ;
		if (data->p_max == 1)
			usleep(1000);
		ft_printer(data, philo->p_id, "is sleeping");
		ft_sleep(data->t_sleep, data);
		ft_printer(data, philo->p_id, "is thinking");
	}
	return (NULL);
}

int	ft_error(int error, t_arg data)
{
	if (error == 1)
	{
		printf("Error in arguments\n");
		return (0);
	}
	else if (error == 2)
	{
		printf("Error in mutex initialisation\n");
		if (data.fork)
			free(data.fork);
		return (0);
	}
	else if (error == 3)
	{
		printf("Error in thread creation\n");
		free(data.philo);
		free(data.fork);
	}
	return (0);
}

int	args_error(void)
{
	printf("Correct usage is : ./philo  number_of_philosophers  ");
	printf("time_to_die  time_to_eat  time_to_sleep  ");
	printf("[number_of_times_each_philosopher_must_eat]\n");
	return (0);
}

int	main(int argc, char **argv)
{
	t_arg	d;
	int		i;
	int		ret;

	if (argc < 5 || argc > 6)
		return (args_error());
	ret = ft_init(&d, argc, argv);
	if (ret)
		return (ft_error(ret, d));
	i = 0;
	d.t_start = ft_time();
	while (i < d.p_max)
	{
		if (pthread_create(&d.philo[i].thread, NULL, ft_philo, &d.philo[i]))
			return (ft_error(3, d));
		d.philo[i].e_last = ft_time();
		i++;
	}
	ft_death_check(&d);
	ft_end(d);
	free(d.philo);
	free(d.fork);
	return (0);
}

void	ft_end(t_arg d)
{
	int	i;

	i = -1;
	while (++i < d.p_max)
		pthread_join(d.philo[i].thread, NULL);
	i = -1;
	while (++i < d.p_max)
		pthread_mutex_destroy(&d.fork[i]);
	pthread_mutex_destroy(&d.write);
	pthread_mutex_destroy(&d.lock_eat);
	pthread_mutex_destroy(&d.lock_state);
}
