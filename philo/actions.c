/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:07:15 by ael-maar          #+#    #+#             */
/*   Updated: 2023/03/13 13:53:36 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->forks[philo->philo_num]));
	log_sleep("has taken a fork", 0, philo);
	if (philo->data->philo_len == 1)
	{
		pthread_mutex_unlock(&(philo->data->forks[philo->philo_num]));
		return ;
	}
	pthread_mutex_lock(&(philo->data->forks[(philo->philo_num + 1) \
	% philo->data->philo_len]));
	log_sleep("has taken a fork", 0, philo);
}

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->shared_guard));
	philo->data->asreal[philo->philo_num] = timestamp_in_ms();
	pthread_mutex_unlock(&(philo->data->shared_guard));
	log_sleep("is eating", philo->data->time_to_eat, philo);
	pthread_mutex_lock(&(philo->data_guard));
	philo->eat_times--;
	pthread_mutex_unlock(&(philo->data_guard));
}

static void	return_forks(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->data->forks[philo->philo_num]));
	pthread_mutex_unlock(&(philo->data->forks[(philo->philo_num + 1) \
	% philo->data->philo_len]));
}

void	*run_actions(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_num % 2)
		usleep(1000);
	while (death_or_done(philo) == 0)
	{
		log_sleep("is thinking", 0, philo);
		take_forks(philo);
		if (philo->data->philo_len == 1)
			break ;
		philo_eat(philo);
		return_forks(philo);
		log_sleep("is sleeping", philo->data->time_to_sleep, philo);
	}
	return (NULL);
}
