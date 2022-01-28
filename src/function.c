/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:18:43 by arthur            #+#    #+#             */
/*   Updated: 2022/01/22 17:18:44 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	get_timestamp(struct timeval start)
{
	int				timestamp;
	struct timeval	end;

	gettimeofday(&end, NULL);
	timestamp = ((end.tv_sec - start.tv_sec)
			+ 1e-6 * (end.tv_usec - start.tv_usec)) * 1000;
	return (timestamp);
}

int	ft_atoi(char *str)
{
	int		i;
	int		ret;
	int		neg;

	i = 0;
	ret = 0;
	neg = 1;
	while (str[i] && (str[i] == '+' || str[i] == '-'))
		if (str[i++] == '-')
			neg = -1;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		ret = (ret * 10) + (str[i] - 48);
		i++;
	}
	return (ret * neg);
}
