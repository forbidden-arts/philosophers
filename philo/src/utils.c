/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 09:34:37 by dpalmer           #+#    #+#             */
/*   Updated: 2023/03/30 19:06:57 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	num;
	int	i;

	i = 0;
	num = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num);
}

int	check_args(int argc, char **argv)
{
	int	i;
	int	u;

	u = 0;
	i = 1;
	while (i < argc)
	{
		while (argv[i][u])
		{
			if (argv[i][u] < '0' || argv[i][u] > '9')
				return (-1);
			u++;
		}
		u = 0;
		i++;
	}
	return (0);
}

long long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}
