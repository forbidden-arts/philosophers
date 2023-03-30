/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 09:34:31 by dpalmer           #+#    #+#             */
/*   Updated: 2023/03/30 19:06:34 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_rules	rules;

	check_args(argc, argv);
	parse_args(argc, argv, &rules);
	if (rules.all_done)
		start(&rules);
	return (0);
}

void	*alive(void *alive)
{
	t_philo		*philo;
	t_rules		*rules;
	int			i;

	i = 0;
	philo = (t_philo *)alive;
	rules = philo->p_rules;
	if (philo->id % 2 == 0)
		usleep(1500);
	pthread_mutex_lock(&(rules->eat));
	while (!(rules->is_dead) && !(rules->all_ate))
	{
		pthread_mutex_unlock(&(rules->eat));
		eat(philo);
		pthread_mutex_lock(&(rules->eat));
		print_action(rules, philo->id, "is sleeping");
		pthread_mutex_unlock(&(rules->eat));
		smart_sleep(rules->time_to_slp, rules);
		pthread_mutex_lock(&(rules->eat));
		print_action(rules, philo->id, "is thinking");
		i++;
	}
	pthread_mutex_unlock(&(rules->eat));
	return (NULL);
}

void	start(t_rules *rules)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = rules->philosophers;
	rules->start_time = get_time();
	while (i < rules->id_philo)
	{
		if (pthread_create(&(philo[i].thread_id), NULL, alive, &(philo[i])))
			print_error("Thread error.");
		pthread_mutex_lock(&(rules->eat));
		philo[i].last_eat = get_time();
		pthread_mutex_unlock(&(rules->eat));
		i++;
	}
	is_dead(rules, philo);
	exit_launcher(rules);
}
