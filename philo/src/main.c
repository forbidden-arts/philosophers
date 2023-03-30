/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:34:31 by dpalmer           #+#    #+#             */
/*   Updated: 2023/03/30 11:17:35 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_argv	arg;

	check_args(argc, argv);
	parse_args(argc, argv, &arg);
	starter(&arg);
	return (0);
}

long int	actual_time(void)
{
	struct timeval		current_time;

	if (gettimeofday(&current_time, NULL) == -1)
		showerror("gettimeofday error\n");
	return (current_time.tv_usec);
}

void	*life(void *life)
{
	t_philo		*ph;
	t_argv		*argv;
	int			i;

	i = 0;
	ph = (t_philo *)life;
	argv = ph->p_arg;
	if (ph->nb % 2 == 0)
		usleep(1500);
	pthread_mutex_lock(&(argv->eat));
	while (!(argv->is_dead) && !(argv->all_ate))
	{
		pthread_mutex_unlock(&(argv->eat));
		eat(ph);
		pthread_mutex_lock(&(argv->eat));
		print_action(argv, ph->nb, "is sleeping");
		pthread_mutex_unlock(&(argv->eat));
		smart_sleep(argv->time_ts, argv);
		pthread_mutex_lock(&(argv->eat));
		print_action(argv, ph->nb, "is thinking");
		i++;
	}
	pthread_mutex_unlock(&(argv->eat));
	return (NULL);
}

void	starter(t_argv *arg)
{
	int		i;
	t_philo	*ph;

	i = 0;
	ph = arg->philosophers;
	arg->first_time = get_time();
	while (i < arg->nb_philo)
	{
		if (pthread_create(&(ph[i].thread_nb), NULL, life, &(ph[i])))
			showerror("Unable to create a thread");
		pthread_mutex_lock(&(arg->eat));
		ph[i].last_eat = get_time();
		pthread_mutex_unlock(&(arg->eat));
		i++;
	}
	is_dead(arg, ph);
	exit_launcher(arg);
}
