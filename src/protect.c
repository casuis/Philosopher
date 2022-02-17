/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 13:57:52 by arthur            #+#    #+#             */
/*   Updated: 2022/02/17 17:30:06 by asimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	protect_write(t_philo *philo, char *str)
{
	if (protect_check(philo))
	{
		pthread_mutex_lock(philo->shared->write_protect);
		printf(str, get_timestamp(philo->tmstp), philo->index, philo->count);
		pthread_mutex_unlock(philo->shared->write_protect);
	}
}

int	protect_check(t_philo *philo)
{
	int		value;

	value = 1;
	pthread_mutex_lock(philo->shared->dead);
	if (*(philo->shared->is_dead) == 1)
		value = 0;
	pthread_mutex_unlock(philo->shared->dead);
	return (value);
}

void	lock(t_philo *philo)
{
	if (philo->index % 2 != 0)
	{
		if (philo->next->balise != 1)
			pthread_mutex_lock(&(philo->next->fork));
		else
			pthread_mutex_lock(&(philo->next->next->fork));
		protect_write(philo, "%d Philos %d as taken a fork\n");
		pthread_mutex_lock(&(philo->fork));
		protect_write(philo, "%d Philos %d as taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(&(philo->fork));
		protect_write(philo, "%d Philos %d as taken a fork\n");
		if (philo->next->balise != 1)
			pthread_mutex_lock(&(philo->next->fork));
		else
			pthread_mutex_lock(&(philo->next->next->fork));
		protect_write(philo, "%d Philos %d as taken a fork\n");
	}
}

void	unlock(t_philo *philo)
{
	if (philo->index % 2 == 0 && philo->next->balise != 1)
	{
		pthread_mutex_unlock(&(philo->next->fork));
		pthread_mutex_unlock(&(philo->fork));
	}
	else if (philo->index % 2 != 0 && philo->next->balise != 1)
	{
		pthread_mutex_unlock(&(philo->fork));
		pthread_mutex_unlock(&(philo->next->fork));
	}
	else if (philo->next->balise == 1 && philo->index % 2 != 0)
	{
		pthread_mutex_unlock(&(philo->next->next->fork));
		pthread_mutex_unlock(&(philo->fork));
	}
	else if (philo->next->balise == 1 && philo->index % 2 == 0)
	{
		pthread_mutex_unlock(&(philo->fork));
		pthread_mutex_unlock(&(philo->next->next->fork));
	}
}
