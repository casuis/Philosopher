/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimon <asimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 20:43:34 by asimon            #+#    #+#             */
/*   Updated: 2022/02/15 13:50:50 by asimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	create_thread(t_philo *philo)
{
	t_philo		*buff;

	buff = philo;
	while (buff->balise != 1)
	{
		pthread_create(&(buff->thread), NULL, &routine, buff);
		buff = buff->next;
	}
}

static t_philo	*check_value(t_philo *philo)
{
	int		time;

	time = 0;
	if (philo->balise != 1 && *(philo->shared->is_dead) != 1)
		pthread_mutex_lock(&(philo->count_protect));
	while (philo->balise != 1 && *(philo->shared->is_dead) != 1
		&& philo->count != philo->shared->arg.need_eat)
	{
		pthread_mutex_unlock(&(philo->count_protect));
		pthread_mutex_lock(philo->shared->dead);
		time = get_timestamp(philo->tmstp);
		if ((time - philo->last_meal) > (philo->shared->arg.t_dead + 1))
		{
			*(philo->shared->is_dead) = 1;
			printf("%d Philo %d died\n", get_timestamp(philo->tmstp),
				philo->index);
		}
		pthread_mutex_unlock(philo->shared->dead);
		philo = philo->next;
		if (philo->balise != 1 && *(philo->shared->is_dead) != 1)
			pthread_mutex_lock(&(philo->count_protect));
	}
	if (philo->balise != 1 && *(philo->shared->is_dead) != 1)
		pthread_mutex_unlock(&(philo->count_protect));
	return (philo);
}

static void	monitoring(t_philo *philo)
{
	pthread_mutex_lock(&(philo->count_protect));
	while (*(philo->shared->is_dead) != 1
		&& philo->count != philo->shared->arg.need_eat)
	{
		pthread_mutex_unlock(&(philo->count_protect));
		philo = check_value(philo);
		if (philo->balise == 1)
			philo = philo->next;
		pthread_mutex_lock(&(philo->count_protect));
	}
	pthread_mutex_unlock(&(philo->count_protect));
	if (philo->count == philo->shared->arg.need_eat
		&& *(philo->shared->is_dead) != 1)
	{
		memset(philo->shared->eat_enough, 1, 1);
			philo->index);
	}
}

static void	exit_thread(t_philo *philo)
{
	t_philo		*buff;

	buff = philo;
	while (buff->balise != 1)
	{
		if (!(buff->index == 1 && buff->next->balise == 1))
			pthread_join(buff->thread, NULL);
		buff = buff->next;
	}
	pthread_mutex_destroy(philo->shared->write_protect);
	pthread_mutex_destroy(philo->shared->dead);
	free(philo->shared->dead);
	free(philo->shared->write_protect);
	free(philo->shared->is_dead);
	free(philo->shared->eat_enough);
	free(philo->shared);
	while (philo->balise != 1)
	{
		buff = philo->next;
		pthread_mutex_destroy(&(philo->fork));
		pthread_mutex_destroy(&(philo->count_protect));
		free(philo);
		philo = buff;
	}
	free(philo);
}

void	philosopher(t_arg arg)
{
	t_philo			*philo;
	t_philo			*buff;
	t_shared		*shared;

	if (arg.nb_philo <= 0 || arg.t_dead <= 0
		|| arg.t_eat <= 0 || arg.t_sleep <= 0)
		return ;
	shared = set_shared(arg);
	philo = set_list(arg.nb_philo, shared);
	if (philo == NULL)
		return ;
	buff = philo;
	if (arg.nb_philo > 1)
		create_thread(buff);
	monitoring(buff);
	exit_thread(philo);
}
