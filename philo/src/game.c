/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 07:39:11 by dpalmer           #+#    #+#             */
/*   Updated: 2023/02/17 15:53:30 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

/* Creates a thread for each philo and begins the game. */
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
