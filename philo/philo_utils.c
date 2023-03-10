/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 11:52:02 by ael-maar          #+#    #+#             */
/*   Updated: 2023/03/10 15:00:45 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	timestamp_in_ms(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

int	death_or_done(t_philo *philo)
{
	int	is_done;

	is_done = 0;
	if (philo->data->a_philo_died == 1)
		is_done = 1;
	if (philo->data->is_all_eaten == 1)
		is_done = 1;
	return (is_done);
}

void	log_sleep(char *message, int sleeptime, t_philo *philo)
{
	time_t	current_time;

	current_time = timestamp_in_ms() + sleeptime;
	pthread_mutex_lock(&(philo->data->printf_guard));
	if (!death_or_done(philo))
	{
		printf("%ld %d %s\n", timestamp_in_ms() - \
		philo->data->running_time, philo->philo_num, message);
	}
	pthread_mutex_unlock(&(philo->data->printf_guard));
	while (timestamp_in_ms() < current_time)
		usleep(10);
}
