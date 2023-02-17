/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 11:03:44 by dpalmer           #+#    #+#             */
/*   Updated: 2023/02/17 12:13:12 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*test(void *a)
{
	int	i;

	i = 0;
	while (i++ < 5)
	{
		printf("%i\n", i);
		sleep(3);
	}
	return (a);
}

int	main(void)
{
	pthread_t	t1;
	pthread_t	t2;

	pthread_create(&t1, NULL, &test, NULL);
	pthread_create(&t2, NULL, &test, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return (0);
}
