/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimon <asimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:41:24 by asimon            #+#    #+#             */
/*   Updated: 2022/02/16 20:36:42 by asimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_arg
{
	int		nb_philo;
	int		t_dead;
	int		t_eat;
	int		t_sleep;
	int		need_eat;
}	t_arg;

typedef struct s_shared
{
	t_arg				arg;
	int					*is_dead;
	pthread_mutex_t		*dead;
	pthread_mutex_t		*write_protect;
}	t_shared;

typedef struct s_philo
{
	int					balise;
	int					index;
	int					count;
	int					last_meal;
	t_shared			*shared;
	pthread_t			thread;
	struct timeval		tmstp;
	pthread_mutex_t		fork;
	pthread_mutex_t		count_protect;
	struct s_philo		*next;
}	t_philo;

void		philosopher(t_arg arg);
t_philo		*set_list(int size, t_shared *shared);
t_shared	*set_shared(t_arg arg);
void		*routine(void *philo);
int			get_timestamp(struct timeval start);
void		unlock(t_philo *philo);
void		lock(t_philo *philo);
void		protect_write(t_philo *philo, char *str);
int			protect_check(t_philo *philo);
int			ft_atoi(char *str);
void		monitoring(t_philo *philo);
void		ft_error(char *str);
int			check_main(t_arg arg, int argc, char **argv);

#endif
