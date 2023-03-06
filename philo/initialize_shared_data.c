/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_shared_data.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:21:27 by ael-maar          #+#    #+#             */
/*   Updated: 2023/03/06 13:50:20 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_mutexes_and_asreal(t_info *shared_data, char *argv)
{
	shared_data->forks = malloc(ft_atoi(argv) * sizeof(pthread_mutex_t));
	if (shared_data->forks == NULL)
	{
		free(shared_data);
		return (0);
	}
	shared_data->asreal = malloc(ft_atoi(argv) * sizeof(time_t));
	if (shared_data->asreal == NULL)
	{
		free(shared_data->forks);
		free(shared_data);
		return (0);
	}
	return (1);
}

int	init_mutexes(t_info *data)
{
	int	i;
	int	mutex_return;

	i = 0;
	while (i < data->philo_len)
	{
		mutex_return = pthread_mutex_init(&(data->forks[i]), NULL);
		if (destroy_prev_shared_mutexes(data->forks, mutex_return, i) == 0)
			return (0);
		++i;
	}
	mutex_return = pthread_mutex_init(&(data->printf_guard), NULL);
	if (destroy_prev_shared_mutexes(&(data->printf_guard), \
		mutex_return, 0) == 0)
	{
		destroy_prev_shared_mutexes(data->forks, mutex_return, \
		data->philo_len - 1);
		return (0);
	}
	return (1);
}

t_info	*init_shared_data(char *argv[])
{
	t_info	*shared_data;

	shared_data = malloc(sizeof(t_info));
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