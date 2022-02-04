/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimon <asimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 17:19:54 by asimon            #+#    #+#             */
/*   Updated: 2022/01/22 17:19:55 by asimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	set_philo(t_philo *philo, int index, struct timeval time, t_shared *s)
{
	philo->balise = 0;
	philo->index = index;
	philo->count = 0;
	philo->last_meal = 0;
	philo->shared = s;
	philo->tmstp = time;
	pthread_mutex_init(&(philo->fork), NULL);
	pthread_mutex_init(&(philo->count_protect), NULL);
}

void	balised(t_philo *balise, t_philo *start)
{
	balise->balise = 1;
	balise->next = start;
	balise->count = -1;
	balise->shared = NULL;
	balise->index = -1;
}

t_shared	*set_shared(t_arg arg)
{
	t_shared	*ret;

	ret = malloc(sizeof(t_shared));
	ret->dead = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	ret->write_protect = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	ret->is_dead = malloc(sizeof(int));
	ret->eat_enough = malloc(sizeof(int));
	ret->arg = arg;
	*(ret->is_dead) = 0;
	*(ret->eat_enough) = 0;
	pthread_mutex_init(ret->dead, NULL);
	pthread_mutex_init(ret->write_protect, NULL);
	return (ret);
}

t_philo	*set_list(int size, t_shared *shared)
{
	t_philo			*philo;
	t_philo			*buff[2];
	struct timeval	time;
	int				i;

	i = 1;
	if (size <= 0)
		return (NULL);
	philo = malloc(sizeof(t_philo));
	buff[0] = philo;
	buff[1] = philo;
	gettimeofday(&time, NULL);
	set_philo(philo, i, time, shared);
	while (i <= size)
	{
		philo = malloc(sizeof(t_philo));
		buff[1]->next = philo;
		buff[1] = philo;
		set_philo(buff[1], ++i, time, shared);
	}
	balised(philo, buff[0]);
	return (buff[0]);
}
