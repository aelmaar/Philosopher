/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:44:22 by ael-maar          #+#    #+#             */
/*   Updated: 2023/03/11 18:22:51 by ael-maar         ###   ########.fr       */
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

# define FAILURE 0
# define SUCCESS 1

typedef struct s_shared_data
{
	sem_t	*forks;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		is_philo_died;
	int		philo_len;
	int		philo_max_eaten;
	time_t	running_time;
	sem_t	*printf_guard;
	sem_t	*max_eaten;
	char	**data_guard;
}	t_shared_data;

typedef struct s_philo
{
	int				philo_num;
	pid_t			pid;
	time_t			last_meal;
	pthread_t		watch_dead;
	pthread_t		watch_eating;
	int				is_enough_eat;
	t_shared_data	*data;
	sem_t			*data_guard;
}	t_philo;

/**
 * @brief Initialize the shared data between all philosophers.
 * @param argv The argument vector.
 * @return The shared data struct object.
*/
t_shared_data	*init_shared_data(char *argv[]);

/**
 * @brief Initialize processes and start coordinating their activities.
 * @param philo The philosopher object
 * @param data The shared data between all philosophers
 * @return return 0 if something failed, otherwise return 1 for success
*/
int				init_processes_and_coordinate(t_philo *philo, \
					t_shared_data *data);

/**
 * @brief get system time in milliseconds.
 * 
 * @return time since 1970 in milliseconds.
*/
time_t			timestamp_in_ms(void);

/**
 * @brief Free all the data that is shared between all philosophers 
 * and the philosopher objects.
 * @param data The data that is shared between philosophers.
 * @param philo The philosopher object
*/
void			free_all(t_shared_data *data, t_philo *philo);

/**
 * @brief Print the message log with a sleep time.
 * @param message The log message.
 * @param sleeptime The sleep time.
 * @param philo The philosopher object.
*/
void			log_sleep(char *message, int sleeptime, t_philo *philo);

/**
 * @brief Kill all the child processes.
 * @param philo The philosopher object
 * @param last_process The last created process in case one failed in creation.
*/
void			kill_processes(t_philo *philo, int last_process);

/**
 * @brief Check the arguments if they are valid or not.
 * @param argv The argument vector.
 * @return return 0 if something failed, otherwise return 1 for success.
*/
int				check_args(char *argv[]);

/**
 * @brief convert ascii string to integer, it is an updated atoi 
 * function for the philosopher project.
 * @param str a string to be converted to integer.
 * @return the int representation.
*/
int				ft_atoi(const char *str);

/**
 * @brief write string to a fd.
*/
void			ft_putstr_fd(char *s, int fd);

/**
 * @brief write number to a fd.
*/
void			ft_putnbr_fd(int n, int fd);

char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_itoa(int n);

void			unlink_shared_semaphores_and_free(t_shared_data *data, \
										t_philo *philo);

#endif