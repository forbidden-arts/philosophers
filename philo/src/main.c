/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 12:13:24 by dpalmer           #+#    #+#             */
/*   Updated: 2023/02/17 12:46:49 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_dm	dm;

	if (argc < 5 || argc > 6)
		return (print_error("Usage: <# of philo> <die> <eat> <sleep> [count]"));
	if (parse_args(&dm, argv))
		return (print_error("Invalid values."));
	return (0);
}
