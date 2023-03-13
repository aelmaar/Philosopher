/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:21:21 by ael-maar          #+#    #+#             */
/*   Updated: 2023/03/13 13:55:28 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*death_or_done(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->data_guard);
		if ((timestamp_in_ms() - philo->last_meal) >= philo->data->time_to_die)
		{
			sem_wait(philo->data->printf_guard);
			printf("%ld %d %s\n", timestamp_in_ms() - philo->data->running_time, \
			philo->philo_num, "died");
			sem_post(philo->data_guard);
			exit(0);
		}
		if (philo->data->philo_max_eaten != -1 && \
		philo->is_enough_eat >= philo->data->philo_max_eaten)
		{
			sem_post(philo->data->max_eaten);
			sem_post(philo->data_guard);
			break ;
		}
		sem_post(philo->data_guard);
	}
	return (NULL);
}

static void	take_forks(t_philo *philo)
{
	sem_wait(philo->data->forks);
	log_sleep("has taken a fork", 0, philo);
	sem_wait(philo->data->forks);
	log_sleep("has taken a fork", 0, philo);
}

static void	philo_eating(t_philo *philo)
{
	sem_wait(philo->data_guard);
	philo->last_meal = timestamp_in_ms();
	sem_post(philo->data_guard);
	log_sleep("is eating", philo->data->time_to_eat, philo);
	sem_wait(philo->data_guard);
	philo->is_enough_eat++;
	sem_post(philo->data_guard);
}

static void	return_forks(t_philo *philo)
{
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	run_actions(t_philo *philo)
{
	if (philo->philo_num % 2)
		usleep(500);
	philo->last_meal = timestamp_in_ms();
	if (pthread_create(&(philo->watch_dead), NULL, \
	death_or_done, (void *)philo) != 0)
	{
		ft_putstr_fd("Error creating the thread in the process: ", 2);
		ft_putnbr_fd(philo->philo_num, 2);
		ft_putstr_fd("\n", 2);
		exit(1);
	}
	while (1)
	{
		log_sleep("is thinking", 0, philo);
		take_forks(philo);
		philo_eating(philo);
		return_forks(philo);
		log_sleep("is sleeping", philo->data->time_to_sleep, philo);
	}
}
