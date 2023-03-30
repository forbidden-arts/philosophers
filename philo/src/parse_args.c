/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:46:38 by dpalmer           #+#    #+#             */
/*   Updated: 2023/03/30 11:42:30 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	arg_error(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		print_error("./philo requires 4 or 5 args.");
	if (check_args(argc, argv) == -1)
		print_error("Only digits are accepted.");
	if (ft_atoi(argv[1]) == 0 || ft_atoi(argv[2]) == 0
		|| ft_atoi(argv[3]) == 0 || ft_atoi(argv[4]) == 0)
		print_error("Negative numbers not allowed.");
}

void	parse_args(int argc, char **argv, t_argv *arg)
{
	arg->nb_philo = ft_atoi(argv[1]);
	arg->time_to_die = ft_atoi(argv[2]);
	arg->time_to_eat = ft_atoi(argv[3]);
	arg->time_to_slp = ft_atoi(argv[4]);
	if (argc == 6)
		arg->all_done = ft_atoi(argv[5]);
	else
		arg->all_done = -1;
	if (init(arg) == 1)
		print_error("Init failed");
}
