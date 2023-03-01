/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:44:22 by ael-maar          #+#    #+#             */
/*   Updated: 2023/02/28 15:26:06 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include "unistd.h"
# include "semaphore.h"
# include "stdlib.h"
# include "fcntl.h"
# include "sys/time.h"
# include "sys/wait.h"
# include "signal.h"
# include "pthread.h"

// struct containing the data that is shared between philosphers
typedef struct s_shared_data
{
    sem_t   *forks;
    int     time_to_die;
    int     time_to_eat;
    int     time_to_sleep;
    int     is_philo_died;
    int     philo_len;
    time_t  *asreal;
    sem_t   *printf_guard;
}   t_shared_data;

// struct containing the data of every philospher
typedef struct s_philo
{
    int             philo_num;
    pid_t           pid;
    time_t          last_meal;
    pthread_t       watch_dead;
    time_t          running_time;
    t_shared_data   *data;
}   t_philo;


t_shared_data   *initialize_philo_data(char *argv[]);
time_t	timestamp_in_ms(void);

#endif