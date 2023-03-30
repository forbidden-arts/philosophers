/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:45:41 by dpalmer           #+#    #+#             */
/*   Updated: 2023/03/30 11:18:43 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_eat_death(int i, t_argv *arg, t_philo *ph)
{
	while (++i < arg->nb_philo && !(arg->is_dead))
	{
		pthread_mutex_lock(&(arg->eat));
		if ((get_time() - ph[i].last_eat) > arg->time_td)
			print_action(arg, i + 1, "\033[0;31mdied\033[m");
		if ((get_time() - ph[i].last_eat) > arg->time_td)
			arg->is_dead = 1;
		pthread_mutex_unlock(&(arg->eat));
		usleep(50);
	}
}

void	is_dead(t_argv *arg, t_philo *ph)
{
	int	i;

	while (!(arg->all_ate))
	{
		i = -1;
		check_eat_death(i, arg, ph);
		if (arg->is_dead)
			break ;
		i = 0;
		pthread_mutex_lock(&(arg->eat));
		while (arg->time_de != -1 && i < arg->nb_philo
			&& ph[i].nb_ate >= arg->time_de)
			i++;
		if (i == arg->nb_philo)
			arg->all_ate = 1;
		pthread_mutex_unlock(&(arg->eat));
	}
}
