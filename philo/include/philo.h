/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:09:23 by dpalmer           #+#    #+#             */
/*   Updated: 2023/03/30 12:02:22 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

struct			s_rules;

typedef struct s_philo
{
	int				id;
	int				id_ate;
	int				l_fork;
	int				r_fork;
	long long		last_eat;
	pthread_t		thread_id;
	struct s_rules	*p_rules;
}			t_philo;

typedef struct s_rules
{
	int				is_dead;
	int				id_philo;
	int				all_ate;
	int				all_done;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_slp;
	long long		start_time;
	pthread_mutex_t	eat;
	pthread_mutex_t	writing;
	pthread_mutex_t	forks[250];
	t_philo			philosophers[250];
}			t_rules;

void			arg_error(int argc, char **argv);
void			print_error(char *str);
void			start(t_rules *rules);
int				init(t_rules *rules);
void			eat(t_philo *philo);
void			exit_launcher(t_rules *rules);
long long		get_time(void);
void			*alive(void *alive);
void			is_dead(t_rules *rules, t_philo *ph);
void			smart_sleep(long long time, t_rules *rules);
void			print_action(t_rules *rules, int id, char *msg);
int				ft_atoi(char *str);
int				check_args(int argc, char **argv);
void			parse_args(int argc, char **argv, t_rules *rules);

#endif
