/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 13:57:52 by arthur            #+#    #+#             */
/*   Updated: 2022/02/15 14:40:44 by asimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	protect_write(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->shared->write_protect);
	printf(str, get_timestamp(philo->tmstp), philo->index);
	pthread_mutex_unlock(philo->shared->write_protect);
}

void	lock2(t_philo *philo)
{
	if (philo->index % 2 == 0)
		pthread_mutex_lock(&(philo->fork));
	else if (philo->index % 2 != 0 && philo->balise != 1)
		pthread_mutex_lock(&(philo->next->fork));
	else
		pthread_mutex_lock(&(philo->next->next->fork));
	if (protect_check(philo) != 1)
		protect_write(philo, "%d Philo %d has taken a fork\n");
}

void	lock(t_philo *philo)
{
	if (philo->index % 2 == 0 && philo->next->balise != 1)
		pthread_mutex_lock(&(philo->next->fork));
	else if (philo->index % 2 == 0 && philo->next->balise == 1)
		pthread_mutex_lock(&(philo->next->next->fork));
	else
		pthread_mutex_lock(&(philo->fork));
	if (protect_check(philo) != 1)
		protect_write(philo, "%d Philo %d has taken a fork\n");
	lock2(philo);
}

void	unlock(t_philo *philo)
{
	if (philo->index % 2 == 0 && philo->next->balise != 1)
	{
		pthread_mutex_unlock(&(philo->fork));
		pthread_mutex_unlock(&(philo->next->fork));
	}
	else if (philo->index % 2 != 0 && philo->next->balise != 1)
	{
		pthread_mutex_unlock(&(philo->next->fork));
		pthread_mutex_unlock(&(philo->fork));
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

int	protect_check(t_philo *philo)
{
	int		value;

	value = 0;
	pthread_mutex_lock(philo->shared->dead);
	if (*(philo->shared->is_dead) == 1)
		value = 1;
	pthread_mutex_unlock(philo->shared->dead);
	return (value);
}
