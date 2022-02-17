/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimon <asimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 13:55:33 by asimon            #+#    #+#             */
/*   Updated: 2022/02/17 18:20:11 by asimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	eating(t_philo *philo)
{
	lock(philo);
	pthread_mutex_lock(philo->shared->dead);
	philo->last_meal = get_timestamp(philo->tmstp);
	pthread_mutex_unlock(philo->shared->dead);
	protect_write(philo, "%d Philo %d is eating | repas: %d\n");
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
	if (philo->index % 2 != 0 && philo->shared->arg.t_eat >= philo->shared->arg.t_sleep)
		usleep((philo->shared->arg.t_eat - philo->shared->arg.t_sleep + 1)* 1000);
}

void	*routine(void *philo)
{
	t_philo		*buff;

	buff = (t_philo *)philo;
	if (buff->index % 2 == 0)
		usleep(buff->shared->arg.t_eat * 100);
	while (protect_check(buff))
	{
		if (protect_check(philo))
			eating(buff);
		if (protect_check(philo))
		sleeping(buff);
		if (protect_check(philo))
			thinking(buff);
	}
	return (philo);
}
