/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimon <asimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:44:11 by asimon            #+#    #+#             */
/*   Updated: 2022/01/27 17:44:17 by asimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
 
void    create_thread(t_philo *philo)
{
    t_philo         *buff;

    buff = philo;
    while(buff->balise != 1)
    {
        pthread_create(&(buff->thread), NULL, &routine, buff);
        buff = buff->next;
    }
}

void    monitoring(t_philo *philo)
{
    int     time;

    time = 0;
    while (*(philo->shared->is_dead) != 1 && philo->count != philo->shared->arg.need_eat)
    {
        while (philo->balise != 1 && *(philo->shared->is_dead) != 1 && philo->count != philo->shared->arg.need_eat)
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
        if (philo->balise == 1)
            philo = philo->next;
    }
    if (philo->count == philo->shared->arg.need_eat && *(philo->shared->is_dead) != 1)
    {
        memset(philo->shared->eat_enough, 1, 1);
        protect_write(philo, "%d Philo %d as eat enough\n");
    }
}

void    exit_thread(t_philo *philo)
{
    t_philo     *buff;

    buff = philo;
    while (buff->balise != 1)
    {
        pthread_join(buff->thread, NULL);
        buff = buff->next;
    }
    free(philo->shared->is_dead);
    pthread_mutex_destroy(philo->shared->write_protect);
    pthread_mutex_destroy(philo->shared->dead);
    free(philo->shared->dead);
    free(philo->shared->write_protect);
    while (philo->balise != 1)
    {
        buff = philo->next;
        pthread_mutex_destroy(&(philo->fork));
        free(philo);
        philo = buff;
    }
    free(philo);
}

void    philosopher(t_arg arg)
{
    t_philo         *philo;
    t_philo         *buff;
    t_shared        *shared;

    shared = set_shared(arg);
    philo = set_list(arg.nb_philo, shared);
    if (philo == NULL)
        return ;
    buff = philo;
    create_thread(buff);
    monitoring(buff);
    exit_thread(philo);
}

int main(int argc, char const *argv[])
{
    t_arg       arg;

    if (argc == 5)
        arg.need_eat = -1;
    else if (argc >= 6)
        arg.need_eat = ft_atoi((char *)argv[5]);
    if (argc >= 5)
    {
        arg.nb_philo = ft_atoi((char *)argv[1]);
        arg.t_dead = ft_atoi((char *)argv[2]);
        arg.t_eat = ft_atoi((char *)argv[3]);
        arg.t_sleep = ft_atoi((char *)argv[4]);
        philosopher(arg);
    }
    return 0;
}
