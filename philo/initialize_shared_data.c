/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_shared_data.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:21:27 by ael-maar          #+#    #+#             */
/*   Updated: 2023/03/10 18:21:04 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_mutexes_and_asreal(t_shared_data *shared_data, char *argv)
{
	shared_data->forks = malloc(ft_atoi(argv) * sizeof(pthread_mutex_t));
	if (shared_data->forks == NULL)
	{
		free(shared_data);
		return (FAILURE);
	}
	shared_data->asreal = malloc(ft_atoi(argv) * sizeof(time_t));
	if (shared_data->asreal == NULL)
	{
		free(shared_data->forks);
		free(shared_data);
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	init_other_shared_mutexes(t_shared_data *data)
{
	int	mutex_return;

	mutex_return = pthread_mutex_init(&(data->printf_guard), NULL);
	if (destroy_prev_shared_mutexes(&(data->printf_guard), \
		mutex_return, 1) == FAILURE)
	{
		destroy_prev_shared_mutexes(data->forks, mutex_return, \
		data->philo_len);
		ft_putstr_fd("Error initializing the mutex for printf\n", 2);
		return (FAILURE);
	}
	mutex_return = pthread_mutex_init(&(data->shared_guard), NULL);
	if (destroy_prev_shared_mutexes(&(data->shared_guard), \
		mutex_return, 1) == FAILURE)
	{
		destroy_prev_shared_mutexes(data->forks, mutex_return, \
		data->philo_len);
		pthread_mutex_destroy(&(data->printf_guard));
		ft_putstr_fd("Error initializing the mutex for shared data\n", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	init_mutexes(t_shared_data *data)
{
	int	i;
	int	mutex_return;

	i = 0;
	while (i < data->philo_len)
	{
		mutex_return = pthread_mutex_init(&(data->forks[i]), NULL);
		if (destroy_prev_shared_mutexes(data->forks, mutex_return, i) == 0)
		{
			pthread_error_message(i, "Error initializing the mutex for fork: ");
			return (FAILURE);
		}
		++i;
	}
	if (init_other_shared_mutexes(data) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

t_shared_data	*init_shared_data(char *argv[])
{
	t_shared_data	*shared_data;

	shared_data = malloc(sizeof(t_shared_data));
	if (shared_data)
	{
		shared_data->philo_len = ft_atoi(argv[1]);
		shared_data->time_to_die = ft_atoi(argv[2]);
		shared_data->time_to_eat = ft_atoi(argv[3]);
		shared_data->time_to_sleep = ft_atoi(argv[4]);
		shared_data->running_time = timestamp_in_ms();
		shared_data->a_philo_died = 0;
		if (create_mutexes_and_asreal(shared_data, argv[1]) == 0)
			return (NULL);
		if (init_mutexes(shared_data) == 0)
			return (free_shared_data(shared_data));
		if (argv[5] == NULL)
			shared_data->is_all_eaten = -1;
		else
			shared_data->is_all_eaten = 0;
	}
	return (shared_data);
}
