/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 20:56:09 by ael-maar          #+#    #+#             */
/*   Updated: 2023/03/11 14:11:31 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philo_data(t_philo *philo, t_shared_data *data, char *argv)
{
	int	nbr_of_times_each_philosopher_must_eat;
	int	mutex_return;
	int	i;

	i = 0;
	nbr_of_times_each_philosopher_must_eat = ft_atoi(argv);
	while (i < data->philo_len)
	{
		philo[i].data = data;
		philo[i].philo_num = i;
		philo[i].eat_times = nbr_of_times_each_philosopher_must_eat;
		philo[i].data->asreal[i] = timestamp_in_ms();
		mutex_return = pthread_mutex_init(&(philo[i].data_guard), NULL);
		if (destroy_prev_philo_mutexes(philo, mutex_return, i) == FAILURE)
		{
			destroy_shared_mutexes(data);
			free_shared_data(data);
			free(philo);
			return (FAILURE);
		}
		++i;
	}
	return (SUCCESS);
}

static int	create_threads(t_philo *philo, t_shared_data *data, char *argv)
{
	int	i;
	int	thread_return;

	i = 0;
	if (init_philo_data(philo, data, argv) == FAILURE)
		return (FAILURE);
	while (i < data->philo_len)
	{
		thread_return = pthread_create(&philo[i].thread, NULL, \
						run_actions, (void *)&philo[i]);
		if (thread_return != 0)
		{
			free_all_data(data, philo);
			pthread_error_message(i, "Error creating the thread: ");
			return (FAILURE);
		}
		usleep(100);
		++i;
	}
	return (1);
}

static int	check_if_a_philo_died_or_done(t_shared_data *data, t_philo *philo, \
									int *max_eat_enough)
{
	pthread_mutex_lock(&(data->shared_guard));
	if ((timestamp_in_ms() - data->asreal[philo->philo_num]) \
	>= data->time_to_die)
	{
		data->a_philo_died = 1;
		pthread_mutex_lock(&(data->printf_guard));
		printf("%ld %d died\n", timestamp_in_ms() - \
		data->running_time, philo->philo_num);
		pthread_mutex_unlock(&(data->printf_guard));
		pthread_mutex_unlock(&(data->shared_guard));
		return (FAILURE);
	}
	pthread_mutex_unlock(&(data->shared_guard));
	pthread_mutex_lock(&(philo[philo->philo_num].data_guard));
	if (data->is_all_eaten != -1 && philo[philo->philo_num].eat_times > 0)
		*max_eat_enough = 0;
	pthread_mutex_unlock(&(philo[philo->philo_num].data_guard));
	return (SUCCESS);
}

static void	coordinate_activites_of_threads(t_philo *philo, t_shared_data *data)
{
	int	i;
	int	max_eat_enough;

	while (death_or_done(philo) == 0)
	{
		i = 0;
		max_eat_enough = 1;
		while (i < data->philo_len)
		{
			if (check_if_a_philo_died_or_done(data, &philo[i], \
			&max_eat_enough) == FAILURE)
				break ;
			++i;
		}
		if (data->is_all_eaten != -1 && max_eat_enough == 1)
		{
			pthread_mutex_lock(&(data->shared_guard));
			data->is_all_eaten = 1;
			pthread_mutex_unlock(&(data->shared_guard));
		}
	}
}

int	init_threads_and_coordinate(t_philo *philo, \
									t_shared_data *data, char *argv[])
{
	int	i;

	if (create_threads(philo, data, argv[5]) == 0)
		return (FAILURE);
	coordinate_activites_of_threads(philo, data);
	i = 0;
	while (i < data->philo_len)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
		{
			free_all_data(data, philo);
			pthread_error_message(i, "Failed to join the thread: ");
			return (FAILURE);
		}
		++i;
	}
	return (1);
}
