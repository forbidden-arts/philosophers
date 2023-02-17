/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:49:11 by dpalmer           #+#    #+#             */
/*   Updated: 2023/02/17 14:23:25 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Inits individual philos. Has no return. */
static void	philo_init(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->philo_count)
	{
		game->philo[i].id = i;
		game->philo[i].fork_one = i;
		game->philo[i].fork_two = (i + 1) % game->philo_count;
		game->philo[i].times_eaten = 0;
		game->philo[i].last_meal = get_time();
		game->philo[i].game = game;
		i++;
	}
}

/* Creates MutExes for forks, writing output, and eating. */
static int	mutex_init(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->philo_count)
		if (pthread_mutex_init(&(game->fork[i++]), NULL))
			return (0);
	if (pthread_mutex_init(&(game->eating), NULL))
		return (0);
	if (pthread_mutex_init(&(game->output), NULL))
		return (0);
	return (1);
}

/* Takes the game as a pointer and assigns value. On success, returns 1	*/
int	game_init(t_game *game, char **argv)
{
	game->philo_count = ft_atoi(argv[1]);
	game->time_to_die = ft_atoi(argv[2]);
	game->time_to_eat = ft_atoi(argv[3]);
	game->time_to_slp = ft_atoi(argv[4]);
	game->dead = 0;
	game->all_done = 0;
	if (game->philo_count < 1 || game->time_to_die < 0 || game->time_to_eat < 0
		|| game->time_to_slp < 0 || game->philo_count > 250)
		return (0);
	if (argv[5])
		game->m_c = ft_atoi(argv[5]);
	if (game->m_c < 0)
		return (0);
	if (!mutex_init(game))
		return (0);
	philo_init(game);
	return (1);
}
