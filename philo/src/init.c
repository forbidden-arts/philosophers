/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:34:24 by dpalmer           #+#    #+#             */
/*   Updated: 2023/03/30 12:05:09 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init(t_rules *rules)
{
	int	i;

	i = rules->id_philo;
	rules->is_dead = 0;
	rules->all_ate = 0;
	if (rules->id_philo > 250)
		print_error("Too many philosophers.");
	if (pthread_mutex_init(&(rules->writing), NULL))
		return (1);
	if (pthread_mutex_init(&(rules->eat), NULL))
		return (1);
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(rules->forks[i]), NULL))
			return (1);
		rules->philosophers[i].id = i + 1;
		rules->philosophers[i].id_ate = 0;
		rules->philosophers[i].l_fork = i;
		rules->philosophers[i].r_fork = (i + 1) % rules->id_philo;
		rules->philosophers[i].last_eat = 0;
		rules->philosophers[i].p_rules = rules;
	}
	return (0);
}

void	print_error(char *str)
{
	printf("Error: %s.", str);
	exit(0);
}

void	exit_launcher(t_rules *rules)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = rules->philosophers;
	if (rules->id_philo == 1)
		pthread_mutex_unlock(&(rules->forks[philo[0].l_fork]));
	while (i < rules->id_philo)
	{
		pthread_join(philo[i].thread_id, NULL);
		i++;
	}
	i = 0;
	while (++i < rules->id_philo)
		pthread_mutex_destroy(&(rules->forks[i]));
	pthread_mutex_destroy(&(rules->writing));
	pthread_mutex_destroy(&(rules->eat));
	exit (0);
}
