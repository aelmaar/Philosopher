/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_shared_data.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:37:49 by ael-maar          #+#    #+#             */
/*   Updated: 2023/03/09 16:20:05 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include "stdio.h"

int	open_semaphores(t_shared_data *data, char *arg)
{
	sem_unlink("/forks");
	sem_unlink("/printf");
	sem_unlink("/eat_times");
	data->forks = sem_open("/forks", O_CREAT, 0644, ft_atoi(arg));
	if (data->forks == SEM_FAILED)
	{
		printf("SEM FAILED\n");
		return (0);
	}
	data->printf_guard = sem_open("/printf", O_CREAT, 0644, 1); // understand the permission option
	if (data->printf_guard == SEM_FAILED)
	{
		sem_close(data->forks);
		printf("SEM FAILED\n");
		return (0);
	}
	data->max_eaten = sem_open("/eat_times", O_CREAT, 0644, 0);
	if (data->max_eaten == SEM_FAILED)
	{
		sem_close(data->forks);
		sem_close(data->printf_guard);
		printf("SEM FAILED\n");
		return (0);
	}
	return (1);
}

t_shared_data   *initialize_philo_data(char *argv[])
{
    t_shared_data   *data;

    data = malloc(sizeof(t_shared_data));
    if (data)
    {
		if (open_semaphores(data, argv[1]) == 0)
		{
			free(data);
			return (NULL);
		}
		data->philo_len = ft_atoi(argv[1]);
		data->time_to_die = ft_atoi(argv[2]);
		data->time_to_eat = ft_atoi(argv[3]);
		data->time_to_sleep = ft_atoi(argv[4]);
		data->is_philo_died = 0;
		if (argv[5] == NULL)
			data->philo_max_eaten = -1;
		else
			data->philo_max_eaten = ft_atoi(argv[5]);
    }
    return (data);
}
