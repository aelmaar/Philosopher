/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 20:56:09 by ael-maar          #+#    #+#             */
/*   Updated: 2023/03/10 13:00:22 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*run_actions(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (death_or_done(philo) == 0)
	{
		log_sleep("is thinking", 0, philo);
		pthread_mutex_lock(&(philo->data->forks[philo->philo_num]));
		log_sleep("has taken a fork", 0, philo);
		if (philo->data->philo_len == 1)
		{
			pthread_mutex_unlock(&(philo->data->forks[philo->philo_num]));
			break ;
		}
		pthread_mutex_lock(&(philo->data->forks[(philo->philo_num + 1) \
		% philo->data->philo_len]));
		log_sleep("has taken a fork", 0, philo);
		log_sleep("is eating", philo->data->time_to_eat, philo);
		philo->eat_times--;
		philo->data->asreal[philo->philo_num] = timestamp_in_ms();
		pthread_mutex_unlock(&(philo->data->forks[philo->philo_num]));
		pthread_mutex_unlock(&(philo->data->forks[(philo->philo_num + 1) \
		% philo->data->philo_len]));
		log_sleep("is sleeping", philo->data->time_to_sleep, philo);
	}
	return (NULL);
}

void	init_philo_data(t_philo *philo, t_shared_data *data, char *argv)
{
	int	nbr_of_times_each_philosopher_must_eat;
	int	i;

	i = 0;
	nbr_of_times_each_philosopher_must_eat = ft_atoi(argv);
	while (i < data->philo_len)
	{
		philo[i].data = data;
		philo[i].philo_num = i;
		philo[i].eat_times = nbr_of_times_each_philosopher_must_eat;
		philo[i].data->asreal[i] = timestamp_in_ms();
		++i;
	}
}

int	create_threads(t_philo *philo, t_shared_data *data, char *argv)
{
	int	i;
	int	thread_return;

	i = 0;
	init_philo_data(philo, data, argv);
	while (i < data->philo_len)
	{
		thread_return = pthread_create(&philo[i].thread, NULL, \
						run_actions, (void *)&philo[i]);
		if (thread_return != 0)
		{
			free_all_data(data, philo);
			pthread_error_message(i, "Error creating the thread: ");
			return (0);
		}
		usleep(100);
		++i;
	}
	return (1);
}

void	coordinate_activites_of_threads(t_philo *philo, t_shared_data *data)
{
	int	i;
	int	is_philo_eat_enough;

	while (death_or_done(philo) == 0)
	{
		i = 0;
		is_philo_eat_enough = 1;
		while (i < data->philo_len)
		{
			if ((timestamp_in_ms() - data->asreal[i]) >= data->time_to_die)
			{
				data->a_philo_died = 1;
				pthread_mutex_lock(&(data->printf_guard));
				printf("%ld %d died\n", timestamp_in_ms() - \
				data->running_time, i);
				pthread_mutex_unlock(&(data->printf_guard));
				break ;
			}
			if (data->is_all_eaten != -1 && philo[i].eat_times > 0)
				is_philo_eat_enough = 0;
			++i;
		}
		if (data->is_all_eaten != -1 && is_philo_eat_enough == 1)
			data->is_all_eaten = 1;
	}
}

int	init_threads_and_coordinate(t_philo *philo, \
									t_shared_data *data, char *argv[])
{
	int	i;

	if (create_threads(philo, data, argv[5]) == 0)
		return (0);
	coordinate_activites_of_threads(philo, data);
	i = 0;
	while (i < data->philo_len)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
		{
			free_all_data(data, philo);
			pthread_error_message(i, "Failed to join the thread: ");
			return (0);
		}
		++i;
	}
	return (1);
}
