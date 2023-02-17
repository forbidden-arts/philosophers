/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 12:15:28 by dpalmer           #+#    #+#             */
/*   Updated: 2023/02/17 12:48:03 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Takes argv and assigns assigns the values as integers to the game rules. */
int	parse_args(t_dm *dm, char **argv)
{
	dm->game.philo_count = ft_atoi(argv[1]);
	dm->game.tt_die = ft_atoi(argv[2]);
	dm->game.tt_eat = ft_atoi(argv[3]);
	dm->game.tt_sleep = ft_atoi(argv[4]);
	if (argv[5])
		dm->game.done = ft_atoi(argv[5]);
	else
		dm->game.done = 0;
	if (dm->game.philo_count < 1 || dm->game.tt_die < 0 || dm->game.tt_eat < 0
		|| dm->game.tt_sleep < 0 || dm->game.done < 0)
		return (1);
	return (0);
}
