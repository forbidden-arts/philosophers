/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:20:31 by dpalmer           #+#    #+#             */
/*   Updated: 2023/03/23 13:04:30 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_philo
{
	int				id;
	int				times_eaten;
	int				fork_one;
	int				fork_two;
	unsigned long	last_meal;
	pthread_t		thread_id;
}	t_philo;

typedef struct s_game
{
	int				count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_slp;
	int				max_eat;
	int				dead;
	unsigned long	start;
	t_philo			philo[250];
	pthread_mutex_t	fork[250];
	pthread_mutex_t	output;
	pthread_mutex_t	death;
}	t_game;

/*				MATH				*/
int				ft_atoi(const char *str);

/*				TIME				*/
unsigned long	get_time(void);
int				time_diff(unsigned long last, unsigned long now);
void			smart_sleep(unsigned long time);

/*				ERROR HANDLING		*/
int				exit_error(char *str);



#endif
