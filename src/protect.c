/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthur <arthur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 13:57:52 by arthur            #+#    #+#             */
/*   Updated: 2022/01/23 13:57:53 by arthur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void    protect_write(t_philo *philo, char *str)
{
    pthread_mutex_lock(philo->shared->write_protect);
    printf(str, get_timestamp(philo->tmstp), philo->index);
    pthread_mutex_unlock(philo->shared->write_protect);
}

void    lock(t_philo *philo)
{
    
    pthread_mutex_lock(&(philo->fork));
    if (*(philo->shared->is_dead) != 1 )
        protect_write(philo, "%d Philo %d as taken a fork\n");
    if (philo->next->balise == 1)
    {
        pthread_mutex_lock(&(philo->next->next->fork));
        if (*(philo->shared->is_dead) != 1)
            protect_write(philo, "%d Philo %d as taken a fork\n");
    }
    else
    {
        pthread_mutex_lock(&(philo->next->fork));
        if (*(philo->shared->is_dead) != 1)
            protect_write(philo, "%d Philo %d as taken a fork\n");
    }
}

void    unlock(t_philo *philo)
{
    pthread_mutex_unlock(&(philo->fork));
    if (philo->next->balise == 1)
        pthread_mutex_unlock(&(philo->next->next->fork));
    else
        pthread_mutex_unlock(&(philo->next->fork));
}