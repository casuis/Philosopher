/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimon <asimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 20:43:34 by asimon            #+#    #+#             */
/*   Updated: 2022/01/27 20:43:35 by asimon           ###   ########.fr       */
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
	while (philo->balise != 1 && *(philo->shared->is_dead) != 1
		&& philo->count != philo->shared->arg.need_eat)
	{
		pthread_mutex_lock(philo->shared->dead);
		time = get_timestamp(philo->tmstp);
		if ((time - philo->last_meal) > (philo->shared->arg.t_dead + 2))
		{
			memset(philo->shared->is_dead, 1, 1);
			usleep(1000);
			protect_write(philo, "%d Philo %d is dead\n");
		}
		pthread_mutex_unlock(philo->shared->dead);
		philo = philo->next;
	}
}

static void	monitoring(t_philo *philo)
{
	while (*(philo->shared->is_dead) != 1
		&& philo->count != philo->shared->arg.need_eat)
	{
		philo = check_value(philo);
		if (philo->balise == 1)
			philo = philo->next;
	}
	if (philo->count == philo->shared->arg.need_eat
		&& *(philo->shared->is_dead) != 1)
	{
		memset(philo->shared->eat_enough, 1, 1);
		protect_write(philo, "%d Philo %d as eat enough\n");
	}
}

static void	exit_thread(t_philo *philo)
{
	t_philo		*buff;

	buff = philo;
	while (buff->balise != 1)
	{
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
