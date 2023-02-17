/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalmer <dpalmer@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 12:16:39 by dpalmer           #+#    #+#             */
/*   Updated: 2023/02/17 12:16:41 by dpalmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Takes an ASCII string and converts to INT, if possible. */
int	ft_atoi(const char *str)
{
	int			i;
	int			sum;
	int			sign;
	const long	l_max = ((unsigned long) - 1) / 2;

	i = 0;
	sum = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		sign -= 2 * (str[i++] == '-');
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (sum >= l_max / 10 && str[i + 1] > 7 && sign == 1)
			return (-1);
		else if (sum >= l_max / 10 && str[i + 1] > 8 && sign == -1)
			return (0);
		sum = 10 * sum - (str[i++] - '0');
	}
	return ((int)sum * -sign);
}
