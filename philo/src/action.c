/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:26:40 by dpalmer           #+#    #+#             */
/*   Updated: 2023/03/14 17:11:35 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Unified output and action function. Utilizes a MutEx to avoid printing
* errors, and formats the output for standardization purposes. */
void	do_action(t_game *game, int id, char *str)
{
	pthread_mutex_lock(&(game->output));
	if (!game->dead)
		printf("[%5lu ms] Philosopher %i %s.\n", get_time() - game->start,
			id + 1, str);
	pthread_mutex_unlock(&(game->output));
}

/* Driving function for philosopher actions. Forks are assigned via function
* and each philosopher attempts to take two forks and eat. Numerical return
* value is ignored, it is only used as a true/false check. */
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
	pthread_mutex_unlock(&(philo->game->fork[philo->fork_one]));
	philo->times_eaten += 1;
	i++;
	return (i);
}

/*
* Fork order selection. Conflicts are purposely created to avoid a deadlock
* situation where every philosopher has a single fork and they all die.
*/
void	go_fork_yourself(t_philo *philo)
{
	if (philo->id % 2)
	{
		philo->fork_one = philo->id;
		philo->fork_two = (philo->id + 1) % philo->game->philo_count;
	}
	else
	{
		philo->fork_one = (philo->id + 1) % philo->game->philo_count;
		philo->fork_two = philo->id;
	}
}
