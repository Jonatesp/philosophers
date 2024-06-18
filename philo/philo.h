/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbourge <anbourge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 15:13:30 by anbourge          #+#    #+#             */
/*   Updated: 2022/01/04 15:28:40 by anbourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

struct	s_arg;

typedef struct s_philo
{
	int					p_id;
	unsigned long long	e_last;
	int					e_nbr;
	int					left_fork;
	int					right_fork;
	pthread_t			thread;
	struct s_arg		*data;
}				t_philo;

typedef struct s_arg
{
	unsigned long long	t_start;
	int					e_max;
	int					p_max;
	unsigned long long	t_die;
	unsigned long long	t_eat;
	unsigned long long	t_sleep;
	int					death_end;
	int					eat_end;
	pthread_mutex_t		write;
	pthread_mutex_t		lock_eat;
	pthread_mutex_t		lock_state;
	pthread_mutex_t		*fork;
	t_philo				*philo;
}				t_arg;

void				*ft_philo(void *p_data);
void				ft_end(t_arg d);

int					ft_init(t_arg *data, int argc, char **argv);
void				ft_init_philos(t_arg *data);
int					ft_init_mutex(t_arg *data);

void				ft_eating(t_philo *philo, t_arg *data);
void				ft_death_check(t_arg *data);

long long			ft_atoi(const char *nptr, int j);
void				ft_printer(t_arg *data, int id, char *action);
unsigned long long	ft_time(void);
void				ft_sleep(unsigned long long time, t_arg *data);

#endif