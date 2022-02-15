/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimon <asimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 13:55:33 by asimon            #+#    #+#             */
/*   Updated: 2022/02/15 11:39:16 by asimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	eating(t_philo *philo)
{
	lock(philo);
	if (protect_check(philo) != 1 && *(philo->shared->eat_enough) != 1)
	{
		pthread_mutex_lock(philo->shared->dead);
		philo->last_meal = get_timestamp(philo->tmstp);
		pthread_mutex_lock(&(philo->count_protect));
		philo->count += 1;
		pthread_mutex_unlock(&(philo->count_protect));
		protect_write(philo, "%d Philo %d is eating\n");
		pthread_mutex_unlock(philo->shared->dead);
		usleep(philo->shared->arg.t_eat * 999);
	}
	unlock(philo);
}

void	sleeping(t_philo *philo)
{
	if (protect_check(philo) != 1)
	{
		protect_write(philo, "%d Philo %d is sleeping\n");
		usleep(philo->shared->arg.t_sleep * 999);
	}
}

void	thinking(t_philo *philo)
{
	if (protect_check(philo) != 1)
		protect_write(philo, "%d Philo %d is thinking\n");
}

void	*routine(void *philo)
{
	t_philo		*buff;

	buff = (t_philo *)philo;
	if (buff->index % 2 == 0)
		usleep(2000);
	while (protect_check(buff) != 1 && *(buff->shared->eat_enough) != 1)
	{
		eating(buff);
		sleeping(buff);
		thinking(buff);
	}
	return (philo);
}
