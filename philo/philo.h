/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:42:27 by ael-maar          #+#    #+#             */
/*   Updated: 2023/03/10 14:59:15 by ael-maar         ###   ########.fr       */
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

typedef struct s_shared_data
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
}	t_shared_data;

typedef struct s_philo
{
	t_shared_data			*data;
	pthread_t				thread;
	int						eat_times;
	int						philo_num;
}	t_philo;

/**
 * @brief Initialize the shared data between all philosophers 
 * before creating any threads.
 * @param argv The argument vector.
 * @return return the shared data struct object.
*/
t_shared_data		*init_shared_data(char *argv[]);

/**
 * @brief get system time in milliseconds.
 * 
 * @return time since 1970 in milliseconds.
*/
time_t				timestamp_in_ms(void);

/**
 * @brief write string to a fd.
*/
void				ft_putstr_fd(char *s, int fd);

/**
 * @brief write number to a fd.
*/
void				ft_putnbr_fd(int n, int fd);

/**
 * @brief convert ascii string to integer, it is an updated atoi 
 * function for the philosopher project.
 * @param str a string to be converted to integer.
 * @return the int representation.
*/
int					ft_atoi(const char *str);

/**
 * @brief Check the arguments if they are valid or not.
 * @param argv The argument vector.
 * @return return 0 if something failed, otherwise return 1 for success.
*/
int					check_args(char *argv[]);

/**
 * @brief an error message will be displayed if a pthread function failed.
 * @param pthread_num the number of the pthread in which it failed, 
 * whether threads or mutexes.
 * @param error_message the error message.
*/
void				pthread_error_message(int pthread_num, char *error_message);

/**
 * @brief Destroy the previous mutexes in case someone it's not 
 * initialized properly, and this is specific for forks.
 * @param mutexes The mutex.
 * @param mutex_error the mutex where it failed.
 * @param last_mutex the last mutex where it failed.
 * @return return 0 if something failed, otherwise return 1 for success.
*/
int					destroy_prev_shared_mutexes(pthread_mutex_t *mutexes, \
						int mutex_error, int last_mutex);

/**
 * @brief check whether a philosopher died or that all philosophers done eating.
 * @param philo philosopher object.
 * @return return 0 if a philosopher not died or they still need to eat, 
 * otherwise return 1 in case one has died, or they were all eaten.
*/
int					death_or_done(t_philo *philo);

/**
 * @brief Create threads and start coordinating their activites.
 * @param philo The philosopher object.
 * @param data The shared data between all philosophers.
 * @param argv The argument vector.
 * @return return 0 if something failed, otherwise return 1 for success.
*/
int					init_threads_and_coordinate(t_philo *philo, \
									t_shared_data *data, char *argv[]);

/**
 * @brief Print the message log with a sleep time.
 * @param message The log message.
 * @param sleeptime The sleep time.
 * @param philo The philosopher object.
*/
void				log_sleep(char *message, int sleeptime, t_philo *philo);

/**
 * @brief destroy shared mutexes between all philosophers.
 * @param data The shared data between all philosophers.
*/
void				destroy_shared_mutexes(t_shared_data *data);

/**
 * @brief Destroy all the mutexes and free any memory allocated.
 * @param data The shared data between all philosophers.
 * @param philo The philosopher object.
*/
void				free_all_data(t_shared_data *data, t_philo *philo);

/**
 * @brief Free the shared data between all philosophers.
 * @param data The shared data between all philosophers.
*/
void				*free_shared_data(t_shared_data *data);

#endif