/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 13:30:15 by ael-maar          #+#    #+#             */
/*   Updated: 2023/03/08 15:43:54 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void    kill_processes(t_philo *philo, int last_process)
{
	int i;

	i = 0;
	while (i < last_process)
		kill(philo[i++].pid, SIGKILL);
}

time_t	timestamp_in_ms(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	log_sleep(char *message, int sleeptime, t_philo *philo)
{
	time_t	current_time;

	current_time = timestamp_in_ms() + sleeptime;
	sem_wait(philo->data->printf_guard);
	printf("%ld %d %s\n", timestamp_in_ms() - philo->data->running_time, \
	philo->philo_num, message);
	sem_post(philo->data->printf_guard);
	while (timestamp_in_ms() < current_time)
		usleep(10);
}
