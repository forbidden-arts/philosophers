/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:45:41 by dpalmer           #+#    #+#             */
/*   Updated: 2023/03/30 12:03:48 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_eat_death(int i, t_rules *rules, t_philo *ph)
{
	while (++i < rules->id_philo && !(rules->is_dead))
	{
		pthread_mutex_lock(&(rules->eat));
		if ((get_time() - ph[i].last_eat) > rules->time_to_die)
			print_action(rules, i + 1, "\033[0;31mdied\033[m");
		if ((get_time() - ph[i].last_eat) > rules->time_to_die)
			rules->is_dead = 1;
		pthread_mutex_unlock(&(rules->eat));
		usleep(50);
	}
}

void	is_dead(t_rules *rules, t_philo *ph)
{
	int	i;

	while (!(rules->all_ate))
	{
		i = -1;
		check_eat_death(i, rules, ph);
		if (rules->is_dead)
			break ;
		i = 0;
		pthread_mutex_lock(&(rules->eat));
		while (rules->all_done != -1 && i < rules->id_philo
			&& ph[i].id_ate >= rules->all_done)
			i++;
		if (i == rules->id_philo)
			rules->all_ate = 1;
		pthread_mutex_unlock(&(rules->eat));
	}
}
