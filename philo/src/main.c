/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:34:31 by dpalmer           #+#    #+#             */
/*   Updated: 2023/03/30 11:46:15 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_argv	arg;

	check_args(argc, argv);
	parse_args(argc, argv, &arg);
	start(&arg);
	return (0);
}

void	*alive(void *alive)
{
	t_philo		*philo;
	t_argv		*argv;
	int			i;

	i = 0;
	philo = (t_philo *)alive;
	argv = philo->p_arg;
	if (philo->nb % 2 == 0)
		usleep(1500);
	pthread_mutex_lock(&(argv->eat));
	while (!(argv->is_dead) && !(argv->all_ate))
	{
		pthread_mutex_unlock(&(argv->eat));
		eat(philo);
		pthread_mutex_lock(&(argv->eat));
		print_action(argv, philo->nb, "is sleeping");
		pthread_mutex_unlock(&(argv->eat));
		smart_sleep(argv->time_to_slp, argv);
		pthread_mutex_lock(&(argv->eat));
		print_action(argv, philo->nb, "is thinking");
		i++;
	}
	pthread_mutex_unlock(&(argv->eat));
	return (NULL);
}

void	start(t_argv *arg)
{
	int		i;
	t_philo	*ph;

	i = 0;
	ph = arg->philosophers;
	arg->start_time = get_time();
	while (i < arg->nb_philo)
	{
		if (pthread_create(&(ph[i].thread_nb), NULL, alive, &(ph[i])))
			print_error("Unable to create a thread");
		pthread_mutex_lock(&(arg->eat));
		ph[i].last_eat = get_time();
		pthread_mutex_unlock(&(arg->eat));
		i++;
	}
	is_dead(arg, ph);
	exit_launcher(arg);
}
