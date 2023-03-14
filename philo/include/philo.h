/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:15:37 by dpalmer           #+#    #+#             */
/*   Updated: 2023/03/14 12:34:44 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

/*
* Due to the limitations of pthread_create only taking a single argument,
* we are going to create a circular reference in Philo so that we can pass
* rules of the game when we invoke threads. Looking for better solution.
*/
typedef struct s_philo
{
	int				id;
	int				times_eaten;
	int				fork_one;
	int				fork_two;
	unsigned long	last_meal;
	pthread_t		thread_id;
	struct s_game	*game;
}					t_philo;

typedef struct s_game
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_slp;
	int				m_c;
	int				dead;
	int				all_done;
	unsigned long	start;
	pthread_mutex_t	fork[250];
	pthread_mutex_t	output;
	pthread_mutex_t	eating;
	t_philo			philo[250];
}					t_game;

/*		Prototypes			*/

/*		Math Utils			*/
int				ft_atoi(const char *str);

/*		Time				*/
unsigned long	get_time(void);
int				time_diff(unsigned long last, unsigned long now);
void			smart_sleep(unsigned long time);

/*		Error Handling		*/
int				exit_error(char *str);

/*		Init				*/
int				game_init(t_game *game, char **argv);

/*		Action				*/
void			do_action(t_game *game, int id, char *str);
int				eat(t_philo *philo);
void			go_fork_yourself(t_philo *philo);

/*		Game				*/
int				start_game(t_game *game);

#endif
