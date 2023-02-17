/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 09:11:23 by dpalmer           #+#    #+#             */
/*   Updated: 2023/02/17 12:28:14 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

/* Struct definitions. Because pthread can only take a single argument, this
* go around, we're going to create a supervisor structure that contains all
* of the other ones. This supervisor is going to be the DM.*/

typedef struct s_game
{
	int				philo_count;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				dead;
	int				done;
	unsigned long	start;
}	t_game;

typedef struct s_philo
{
	int				id;
	int				x_eaten;
	int				fork_one;
	int				fork_two;
	unsigned long	last_meal;
	pthread_t		thread_id;
}					t_philo;

typedef struct s_dm
{
	t_game			game;
	t_philo			philo[250];
	pthread_mutex_t	fork[250];
	pthread_mutex_t	eating;
	pthread_mutex_t	output;
}	t_dm;

/*			PROTOTYPES				*/

/*			ERROR HANDLING			*/
int	print_error(char *str);

/* 			MATH UTILS				*/
int	ft_atoi(const char *str);

/*			PARSE ARGS				*/
int	parse_args(t_dm *dm, char **argv);

#endif
