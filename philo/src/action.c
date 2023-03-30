/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:34:21 by dpalmer           #+#    #+#             */
/*   Updated: 2023/03/30 11:17:39 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	t_argv	*arg;

	arg = philo->p_arg;
	pthread_mutex_lock(&(arg->forks[philo->l_fork]));
	pthread_mutex_lock(&(arg->eat));
	print_action(arg, philo->nb, "has taken a fork");
	pthread_mutex_unlock(&(arg->eat));
	pthread_mutex_lock(&(arg->forks[philo->r_fork]));
	pthread_mutex_lock(&(arg->eat));
	print_action(arg, philo->nb, "has taken a fork");
	print_action(arg, philo->nb, "is eating");
	philo->last_eat = get_time();
	pthread_mutex_unlock(&(arg->eat));
	smart_sleep(arg->time_te, arg);
	pthread_mutex_lock(&(arg->eat));
	(philo->nb_ate)++;
	pthread_mutex_unlock(&(arg->eat));
	pthread_mutex_unlock(&(arg->forks[philo->r_fork]));
	pthread_mutex_unlock(&(arg->forks[philo->l_fork]));
}

void	smart_sleep(long long time, t_argv *arg)
{
	long long	start;
	long long	stop;

	start = get_time();
	stop = start + time;
	pthread_mutex_lock(&(arg->eat));
	while ((start < stop) && !(arg->is_dead))
	{
		pthread_mutex_unlock(&(arg->eat));
		usleep((stop - start) * 1000 / 2);
		start = get_time();
		pthread_mutex_lock(&(arg->eat));
	}
	pthread_mutex_unlock(&(arg->eat));
}
