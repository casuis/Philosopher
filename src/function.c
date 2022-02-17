/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:18:43 by arthur            #+#    #+#             */
/*   Updated: 2022/02/17 14:33:29 by asimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_strlen(char *str)
{
	int		i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}

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

void	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
}

int	check_main(t_arg arg, int argc, char **argv)
{
	if (ft_strlen(argv[1]) > 10 || ft_strlen(argv[2]) > 10
		|| ft_strlen(argv[3]) > 10)
		return (0);
	if (argc >= 5)
		if (ft_strlen(argv[4]) > 10)
			return (0);
	if (arg.need_eat > 2147483647 || arg.need_eat <= -2147483648)
		return (0);
	else if (arg.nb_philo > 2147483647 || arg.nb_philo <= -2147483648)
		return (0);
	else if (arg.t_dead > 2147483647 || arg.t_dead <= -2147483648)
		return (0);
	else if (arg.t_eat > 2147483647 || arg.t_eat <= -2147483648)
		return (0);
	else if (arg.t_sleep > 2147483647 || arg.t_sleep <= -2147483648)
		return (0);
	else
		return (1);
	return (0);
}
