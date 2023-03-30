/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:09:23 by dpalmer           #+#    #+#             */
/*   Updated: 2023/03/30 11:17:35 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

struct			s_argv;

typedef struct s_philo
{
	int				nb;
	int				nb_ate;
	int				l_fork;
	int				r_fork;
	long long		last_eat;
	pthread_t		thread_nb;
	struct s_argv	*p_arg;
}			t_philo;

typedef struct s_argv
{
	int				is_dead;
	int				nb_philo;
	int				all_ate;
	int				time_de;
	long int		time_td;
	long int		time_te;
	long int		time_ts;
	long long		first_time;
	pthread_mutex_t	eat;
	pthread_mutex_t	forks[250];
	pthread_mutex_t	writing;
	t_philo			philosophers[250];
}			t_argv;

void			checkargs(int argc, char **argv);
void			showerror(char *str);
void			starter(t_argv *arg);
int				init(t_argv *argv);
void			eat(t_philo *philo);
void			exit_launcher(t_argv *arg);
long long		get_time(void);
void			*life(void *life);
void			is_dead(t_argv *arg, t_philo *ph);
void			smart_sleep(long long time, t_argv *arg);
void			print_action(t_argv *arg, int nb, char *msg);
int				ft_atoi(char *str);
int				check_args(int argc, char **argv);
void			parse_args(int argc, char **argv, t_argv *arg);

#endif
