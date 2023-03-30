/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:46:38 by dpalmer           #+#    #+#             */
/*   Updated: 2023/03/30 10:04:25 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	checkargs(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		showerror("./philo need at least 5 args and 6 max.");
	if (check_args(argc, argv) == -1)
		showerror("Please enter only digits in arguments");
	if (ft_atoi(argv[1]) == 0 || ft_atoi(argv[2]) == 0
		|| ft_atoi(argv[3]) == 0 || ft_atoi(argv[4]) == 0)
		showerror("A argument must be positive");
}

void	parse_args(int argc, char **argv, t_argv *arg)
{
	arg->nb_philo = ft_atoi(argv[1]);
	arg->time_td = ft_atoi(argv[2]);
	arg->time_te = ft_atoi(argv[3]);
	arg->time_ts = ft_atoi(argv[4]);
	if (argc == 6)
		arg->time_de = ft_atoi(argv[5]);
	else
		arg->time_de = -1;
	if (init(arg) == 1)
		showerror("Initialisation fail");
}
