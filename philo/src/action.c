/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:34:21 by dpalmer           #+#    #+#             */
/*   Updated: 2023/03/30 11:59:10 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_rules *rules, int id, char *msg)
{
	pthread_mutex_lock(&(rules->writing));
	if (!(rules->is_dead))
		printf("[%5lld ms] Philosopher %i %s.\n",
			get_time() - rules->start_time, id, msg);
	pthread_mutex_unlock(&(rules->writing));
}

void	eat(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->p_rules;
	pthread_mutex_lock(&(rules->forks[philo->l_fork]));
	pthread_mutex_lock(&(rules->eat));
	print_action(rules, philo->id, "has taken a fork");
	pthread_mutex_unlock(&(rules->eat));
	pthread_mutex_lock(&(rules->forks[philo->r_fork]));
	pthread_mutex_lock(&(rules->eat));
	print_action(rules, philo->id, "has taken a fork");
	print_action(rules, philo->id, "is eating");
	philo->last_eat = get_time();
	pthread_mutex_unlock(&(rules->eat));
	smart_sleep(rules->time_to_eat, rules);
	pthread_mutex_lock(&(rules->eat));
	(philo->id_ate)++;
	pthread_mutex_unlock(&(rules->eat));
	pthread_mutex_unlock(&(rules->forks[philo->r_fork]));
	pthread_mutex_unlock(&(rules->forks[philo->l_fork]));
}

void	smart_sleep(long long time, t_rules *rules)
{
	long long	start;
	long long	stop;

	start = get_time();
	stop = start + time;
	pthread_mutex_lock(&(rules->eat));
	while ((start < stop) && !(rules->is_dead))
	{
		pthread_mutex_unlock(&(rules->eat));
		usleep((stop - start) * 1000 / 2);
		start = get_time();
		pthread_mutex_lock(&(rules->eat));
	}
	pthread_mutex_unlock(&(rules->eat));
}
