/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:42:27 by ael-maar          #+#    #+#             */
/*   Updated: 2023/03/06 15:28:00 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "pthread.h"
# include "stdio.h"
# include "stdlib.h"
# include "sys/time.h"
# include "unistd.h"
# include "limits.h"

// struct containing all the infos about the philosopher project

typedef struct s_info
{
	pthread_mutex_t				*forks;
	time_t						*asreal;
	int							time_to_die;
	int							time_to_eat;
	int							time_to_sleep;
	int							philo_len;
	int							a_philo_died;
	time_t						running_time;
	int							is_all_eaten;
	int							philo_died;
	pthread_mutex_t				printf_guard;
}	t_info;

typedef struct s_philos
{
	t_info			*data;
	pthread_t		thread;
	int				eat_times;
	int				philo_num;
}	t_philos;

// Initialize the struct
t_info		*init_shared_data(char *argv[]);

/**
 * @brief get system time in milliseconds
 * 
 * @return time since 1970 in milliseconds
*/
time_t		timestamp_in_ms(void);

// SOME LIBFT FUNCTIONS
void		ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
int			ft_atoi(const char *str);
int			check_args(char *argv[]);
void		pthread_error_message(int pthread_num, char *error_message);
int			destroy_prev_shared_mutexes(pthread_mutex_t *mutexes, \
						int mutex_error, int last_mutex);
int			death_or_done(t_philos *philo);
int			init_threads_and_coordinate(t_philos *philo, \
									t_info *data, char *argv[]);
void		log_sleep(char *message, int sleeptime, t_philos *philo);
void		destroy_shared_mutexes(t_info *data);
void		free_all_data(t_info *data, t_philos *philo);
void		*free_shared_data(t_info *data);

#endif