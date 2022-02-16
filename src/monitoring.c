/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimon <asimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 16:33:23 by asimon            #+#    #+#             */
/*   Updated: 2022/02/16 20:02:31 by asimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static t_philo	*check_value(t_philo *philo)
{
	int		time;

	time = 0;
	while (philo->balise != 1 && protect_check(philo))
	{
		pthread_mutex_lock(philo->shared->dead);
		time = get_timestamp(philo->tmstp);
		if ((time - philo->last_meal) > (philo->shared->arg.t_dead + 1))
		{
			*(philo->shared->is_dead) = 1;
			pthread_mutex_lock(philo->shared->write_protect);
			printf("%d Philo %d died\n", get_timestamp(philo->tmstp),
				philo->index);
			pthread_mutex_unlock(philo->shared->write_protect);
		}
		pthread_mutex_unlock(philo->shared->dead);
		philo = philo->next;
	}
	return (philo);
}

static int	monitoring_eat(t_philo *philo)
{
	if (philo->shared->arg.need_eat < 0)
		return (0);
	while (philo->balise != 1)
	{
		if (philo->count < philo->shared->arg.need_eat)
			return (0);
		philo = philo->next;
	}
	return (1);
}

void	monitoring(t_philo *philo)
{
	t_philo	*start;

	start = philo;
	while (protect_check(philo))
	{
		if (monitoring_eat(start))
		{
			pthread_mutex_lock(&(philo->count_protect));
			*(start->shared->is_dead) = 1;
			pthread_mutex_unlock(&(philo->count_protect));
			pthread_mutex_lock(philo->shared->write_protect);
			printf("END\n");
			pthread_mutex_unlock(philo->shared->write_protect);
			break ;
		}
		philo = check_value(philo);
		if (philo->balise == 1)
			philo = philo->next;
	}
}
