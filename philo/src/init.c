/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:34:24 by dpalmer           #+#    #+#             */
/*   Updated: 2023/03/30 11:34:57 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init(t_argv *arg)
{
	int	i;

	i = arg->nb_philo;
	arg->is_dead = 0;
	arg->all_ate = 0;
	if (arg->nb_philo > 250)
		print_error("Too many philosophers.");
	if (pthread_mutex_init(&(arg->writing), NULL))
		return (1);
	if (pthread_mutex_init(&(arg->eat), NULL))
		return (1);
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(arg->forks[i]), NULL))
			return (1);
		arg->philosophers[i].nb = i + 1;
		arg->philosophers[i].nb_ate = 0;
		arg->philosophers[i].l_fork = i;
		arg->philosophers[i].r_fork = (i + 1) % arg->nb_philo;
		arg->philosophers[i].last_eat = 0;
		arg->philosophers[i].p_arg = arg;
	}
	return (0);
}

void	print_error(char *str)
{
	printf("Error: %s.", str);
	exit(0);
}

void	exit_launcher(t_argv *arg)
{
	t_philo	*ph;
	int		i;

	i = 0;
	ph = arg->philosophers;
	if (arg->nb_philo == 1)
		pthread_mutex_unlock(&(arg->forks[ph[0].l_fork]));
	while (i < arg->nb_philo)
	{
		pthread_join(ph[i].thread_nb, NULL);
		i++;
	}
	i = 0;
	while (++i < arg->nb_philo)
		pthread_mutex_destroy(&(arg->forks[i]));
	pthread_mutex_destroy(&(arg->writing));
	pthread_mutex_destroy(&(arg->eat));
	exit (0);
}
