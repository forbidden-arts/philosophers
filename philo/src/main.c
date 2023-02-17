/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:16:18 by dpalmer           #+#    #+#             */
/*   Updated: 2023/02/17 14:18:43 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc < 5 || argc > 6)
		return (exit_error("Invocation error."));
	if (!game_init(&game, argv))
		return (exit_error("Error initializing arguments."));
	if (!start_game(&game))
		return (exit_error("Error initializing threads"));
	return (0);
}
