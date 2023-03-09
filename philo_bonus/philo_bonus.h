/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:44:22 by ael-maar          #+#    #+#             */
/*   Updated: 2023/03/09 16:25:07 by ael-maar         ###   ########.fr       */
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
# include "stdio.h"
# include "limits.h"

// struct containing the data that is shared between philosphers
typedef struct s_shared_data
{
    sem_t   *forks;
    int     time_to_die;
    int     time_to_eat;
    int     time_to_sleep;
    int     is_philo_died;
    int     philo_len;
    int		philo_max_eaten;
    time_t  running_time;
    sem_t   *printf_guard;
    sem_t   *max_eaten;
}   t_shared_data;

// struct containing the data of every philospher
typedef struct s_philo
{
    int             philo_num;
    pid_t           pid;
    time_t          last_meal;
    pthread_t       watch_dead;
    pthread_t       watch_eating;
	int				is_enough_eat;
    t_shared_data   *data;
}   t_philo;

t_shared_data	*initialize_philo_data(char *argv[]);
int    			init_processes_and_coordinate(t_philo *philo, t_shared_data *data);
time_t			timestamp_in_ms(void);
void			free_all(t_shared_data *data, t_philo *philo);
void			log_sleep(char *message, int sleeptime, t_philo *philo);
void    		kill_processes(t_philo *philo, int last_process);
int				check_args(char *argv[]);

int	            ft_atoi(const char *str);
void	        ft_putstr_fd(char *s, int fd);
void	        ft_putnbr_fd(int n, int fd);

#endif