/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:34:37 by dpalmer           #+#    #+#             */
/*   Updated: 2023/03/30 10:13:55 by dpalmer          ###   ########.fr       */
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

void	print_action(t_argv *arg, int nb, char *msg)
{
	pthread_mutex_lock(&(arg->writing));
	if (!(arg->is_dead))
		printf("[%5lld ms] Philosopher %i %s.\n",
			get_time() - arg->first_time, nb, msg);
	pthread_mutex_unlock(&(arg->writing));
}

long long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}
