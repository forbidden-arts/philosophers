/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:26:40 by dpalmer           #+#    #+#             */
/*   Updated: 2023/02/17 15:24:19 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_action(t_game *game, int id, char *str)
{
	pthread_mutex_lock(&(game->output));
	if (!game->dead)
		printf("[%lu ms] Philosopher %i %s.\n", get_time() - game->start,
			id + 1, str);
	pthread_mutex_unlock(&(game->output));
}

int	eat(t_philo *philo)
{
	int	i;

	i = 0;
	go_fork_yourself(philo);
	pthread_mutex_lock(&(philo->game->fork[philo->fork_one]));
	do_action(philo->game, philo->id, "has taken a fork");
	pthread_mutex_lock(&(philo->game->fork[philo->fork_two]));
	do_action(philo->game, philo->id, "has taken a fork");
	pthread_mutex_lock(&(philo->game->eating));
	do_action(philo->game, philo->id, "is eating");
	philo->last_meal = get_time();
	pthread_mutex_unlock(&(philo->game->eating));
	smart_sleep(philo->game->time_to_eat);
	pthread_mutex_unlock(&(philo->game->fork[philo->fork_two]));
	philo->times_eaten += 1;
	i++;
	pthread_mutex_unlock(&(philo->game->fork[philo->fork_one]));
	return (i);
}

/*
* Fork order selection. Conflicts are purposely created to avoid a deadlock
* situation where every philosopher has a single fork and they all die.
*/
void	go_fork_yourself(t_philo *philo)
{
	if (philo->id == 0 || philo->id == philo->game->philo_count -1)
	{
		philo->fork_one = 0;
		philo->fork_two = philo->game->philo_count - 1;
	}
	else if (philo->id % 2)
	{
		philo->fork_one = philo->id;
		philo->fork_two = philo->id + 1;
	}
	else
	{
		philo->fork_one = philo->id + 1;
		philo->fork_two = philo->id;
	}
}
