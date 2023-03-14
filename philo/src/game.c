/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 07:39:11 by dpalmer           #+#    #+#             */
/*   Updated: 2023/03/14 15:21:15 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Unwinds all the threads and MutExes once the game is complete. */
static void	end_game(t_game *game, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < game->philo_count)
	{
		pthread_join(philo[i].thread_id, NULL);
		pthread_mutex_destroy(&(game->fork[i]));
		i++;
	}
	pthread_mutex_destroy(&(game->eating));
	pthread_mutex_destroy(&(game->output));
}

/* Checks the status of all of the philosophers and ends the game if any
* have died, or if they all have eaten the required amount of times. */
static void	check_end(t_game *game)
{
	int	i;

	while (!game->all_done && !game->dead)
	{
		i = 0;
		while (i < game->philo_count && !game->dead)
		{
			pthread_mutex_lock(&(game->eating));
			if (time_diff(game->philo[i].last_meal, get_time())
				> game->time_to_die)
			{
				do_action(game, game->philo->id, "died");
				game->dead = 1;
			}
			pthread_mutex_unlock(&(game->eating));
			usleep(100);
			i++;
		}
		i = 0;
		while (game->m_c && game->philo[i].times_eaten >= game->m_c)
			i++;
		if (i == game->philo_count)
			game->all_done = 1;
	}
}

/* Once a thread is created, the philosopher will attempt to eat and sleep,
* and will think while waiting to do either of those previous two actions. */
static void	*start_thread(void *tmp)
{
	t_philo	*philo;

	philo = (t_philo *)tmp;
	while (!philo->game->dead)
	{
		if (eat(philo))
		{
			if (philo->game->all_done)
				break ;
			do_action(philo->game, philo->id, "is sleeping");
			smart_sleep(philo->game->time_to_slp);
			do_action(philo->game, philo->id, "is thinking");
		}
	}
	return (NULL);
}

/* Creates a thread for each philo and begins the game. In the case of a single
* philosopher (which is a guaranteed death), this function waits the necessary
* time and kills the philosopher, instead of creating threads. */
int	start_game(t_game *game)
{
	int	i;

	i = 0;
	game->start = get_time();
	if (game->philo_count == 1)
	{
		do_action(game, game->philo->id, "has taken a fork");
		smart_sleep(game->time_to_die);
		do_action(game, game->philo->id, "died");
		return (1);
	}
	while (i < game->philo_count)
	{
		if (pthread_create(&(game->philo[i].thread_id), NULL,
				start_thread, &(game->philo[i])))
			return (0);
		i++;
	}
	check_end(game);
	end_game(game, game->philo);
	return (1);
}
