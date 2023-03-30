/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:34:21 by dpalmer           #+#    #+#             */
/*   Updated: 2023/03/30 10:08:22 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	t_argv	*arg;

	arg = philo->p_arg;
	pthread_mutex_lock(&(arg->forks[philo->l_fork]));
	pthread_mutex_lock(&(arg->eating));
	print_action(arg, philo->nb, "has taken a fork");
	pthread_mutex_unlock(&(arg->eating));
	pthread_mutex_lock(&(arg->forks[philo->r_fork]));
	pthread_mutex_lock(&(arg->eating));
	print_action(arg, philo->nb, "has taken a fork");
	print_action(arg, philo->nb, "is eating");
	philo->last_eat = get_time();
	pthread_mutex_unlock(&(arg->eating));
	sleep_time(arg->time_te, arg);
	pthread_mutex_lock(&(arg->eating));
	(philo->nb_ate)++;
	pthread_mutex_unlock(&(arg->eating));
	pthread_mutex_unlock(&(arg->forks[philo->r_fork]));
	pthread_mutex_unlock(&(arg->forks[philo->l_fork]));
}

void	sleep_time(long long time, t_argv *arg)
{
	long long	i;

	i = get_time();
	pthread_mutex_lock(&(arg->eating));
	while ((!((get_time() - i) >= time)) && !(arg->is_dead))
	{
		pthread_mutex_unlock(&(arg->eating));
		usleep(50);
		pthread_mutex_lock(&(arg->eating));
	}
	pthread_mutex_unlock(&(arg->eating));
}
