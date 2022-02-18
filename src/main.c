/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimon <asimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:44:11 by asimon            #+#    #+#             */
/*   Updated: 2022/02/17 18:56:04 by asimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char const *argv[])
{
	t_arg		arg;

	if (argc == 5)
		arg.need_eat = -1;
	else if (argc >= 6)
		arg.need_eat = ft_atoi((char *)argv[5]);
	if (argc >= 5)
	{
		arg.nb_philo = ft_atoi((char *)argv[1]);
		arg.t_dead = ft_atoi((char *)argv[2]);
		arg.t_eat = ft_atoi((char *)argv[3]);
		arg.t_sleep = ft_atoi((char *)argv[4]);
		if (check_main(arg, argc, (char **)argv))
			philosopher(arg);
		else
			ft_error("Error\n");
	}
	return (0);
}
