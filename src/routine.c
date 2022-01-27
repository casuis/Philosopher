/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimon <asimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 13:55:33 by asimon            #+#    #+#             */
/*   Updated: 2022/01/23 13:55:34 by asimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void    eating(t_philo *philo)
{
    lock(philo);
    if (*(philo->shared->is_dead) != 1 && *(philo->shared->eat_enough) != 1)
    {
        pthread_mutex_lock(philo->shared->dead);
        philo->last_meal = get_timestamp(philo->tmstp);
        philo->count += 1;
        protect_write(philo, "%d Philo %d is eating\n");
        pthread_mutex_unlock(philo->shared->dead);
        usleep(philo->shared->arg.t_eat * 999);
    }
    unlock(philo);
}

void    sleeping(t_philo *philo)
{
    protect_write(philo,"%d Philo %d is sleeping\n");
    usleep(philo->shared->arg.t_sleep * 999);
}

void    thinking(t_philo *philo)
{   
    protect_write(philo, "%d Philo %d is thinking\n");
}

void    *routine(void *philo)
{
    t_philo     *buff;

    buff = (t_philo *)philo;
    if (buff->index % 2 == 0)
        usleep(1000);
    while (*(buff->shared->is_dead) != 1 && *(buff->shared->eat_enough) != 1)
    {
        eating(buff);
        if (*(buff->shared->is_dead) != 1 && *(buff->shared->eat_enough) != 1)
            sleeping(buff);
        if (*(buff->shared->is_dead) != 1 && *(buff->shared->eat_enough) != 1)
            thinking(buff);
    }
    return (philo);
}
