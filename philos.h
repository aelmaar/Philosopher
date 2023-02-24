/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:42:27 by ael-maar          #+#    #+#             */
/*   Updated: 2023/02/24 11:08:14 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

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
	int							g_eat_times;
	int							is_all_eaten;
	int							philo_died;
	pthread_mutex_t				state_guard;
	pthread_mutex_t				printf_guard;
}	t_info;

typedef struct s_philos
{
	t_info			*info_philos;
	pthread_mutex_t	data_guard;
	pthread_t		thread;
	int				eat_times;
	int				philo_num;
}	t_philos;

// Initialize the struct
t_info		*generate_info_struct(int argc, char *argv[]);
time_t		timestamp_in_ms(void);

#endif