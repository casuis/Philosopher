/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimon <asimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 13:55:33 by asimon            #+#    #+#             */
/*   Updated: 2022/02/16 19:37:03 by asimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	eating(t_philo *philo)
{
	lock(philo);
	pthread_mutex_lock(philo->shared->dead);
	philo->last_meal = get_timestamp(philo->tmstp);
	pthread_mutex_unlock(philo->shared->dead);
	protect_write(philo, "%d Philo %d is eating\n");
	pthread_mutex_lock(&(philo->count_protect));
	philo->count += 1;
	pthread_mutex_unlock(&(philo->count_protect));
	if (protect_check(philo))
		usleep(philo->shared->arg.t_eat * 1000);
	unlock(philo);
}

void	sleeping(t_philo *philo)
{
	protect_write(philo, "%d Philo %d is sleeping\n");
	if (protect_check(philo))
		usleep(philo->shared->arg.t_sleep * 1000);
}

void	thinking(t_philo *philo)
{
	protect_write(philo, "%d Philo %d is thinking\n");
}

void	*routine(void *philo)
{
	t_philo		*buff;

	buff = (t_philo *)philo;
	if (buff->index % 2 == 0)
		usleep(2000);
	while (protect_check(buff))
	{
		eating(buff);
		sleeping(buff);
		thinking(buff);
	}
	return (philo);
}
