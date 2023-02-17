/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 08:06:57 by dpalmer           #+#    #+#             */
/*   Updated: 2023/02/17 15:44:10 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Returns the current time as unsigned long in milliseconds since the epoch. */
unsigned long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

/* Returns the difference in two get_times as unsigned int. */
int	time_diff(unsigned long last, unsigned long now)
{
	return (now - last);
}

/*
* uSleep tends to be imprecise when dealing with larger integers. As such, we
* are going to sleep half the remaining time and loop until the condition
* is satisfied.
*/
void	smart_sleep(unsigned long time)
{
	unsigned long	start;
	unsigned long	stop;

	start = get_time();
	stop = start + time;
	while (get_time() < stop)
	{
		usleep((stop - start) * 1000 / 2);
		start = get_time();
	}
}
