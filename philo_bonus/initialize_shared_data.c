/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_shared_data.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:37:49 by ael-maar          #+#    #+#             */
/*   Updated: 2023/03/13 12:59:06 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include "stdio.h"

void	free_prev_data_guards(char **data_guard, int last_data)
{
	int	i;

	i = 0;
	while (i < last_data)
		free(data_guard[i++]);
	free(data_guard);
}

int	generate_sem_names_for_philo(t_shared_data *data, char *arg)
{
	int	i;

	data->data_guard = malloc((ft_atoi(arg) + 1) * sizeof(char *));
	if (data->data_guard == NULL)
	{
		free(data);
		return (FAILURE);
	}
	i = 0;
	while (i < data->philo_len)
	{
		data->data_guard[i] = ft_strjoin("/data_", ft_itoa(i));
		if (data->data_guard[i] == NULL)
		{
			free_prev_data_guards(data->data_guard, i);
			free(data);
			return (FAILURE);
		}
		++i;
	}
	data->data_guard[i] = NULL;
	return (SUCCESS);
}

int	open_semaphores(t_shared_data *data, char *arg)
{
	sem_unlink("/forks");
	sem_unlink("/printf");
	sem_unlink("/eat_times");
	data->forks = sem_open("/forks", O_CREAT, 0600, ft_atoi(arg));
	data->printf_guard = sem_open("/printf", O_CREAT, 0600, 1);
	data->max_eaten = sem_open("/eat_times", O_CREAT, 0600, 0);
	if (data->forks == SEM_FAILED || data->printf_guard == SEM_FAILED \
	|| data->max_eaten == SEM_FAILED)
	{
		sem_close(data->forks);
		sem_close(data->printf_guard);
		sem_unlink("/forks");
		sem_unlink("/printf");
		printf("SEM FAILED\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

t_shared_data	*init_shared_data(char *argv[])
{
	t_shared_data	*data;

	data = malloc(sizeof(t_shared_data));
	if (data)
	{
		data->philo_len = ft_atoi(argv[1]);
		data->time_to_die = ft_atoi(argv[2]);
		data->time_to_eat = ft_atoi(argv[3]);
		data->time_to_sleep = ft_atoi(argv[4]);
		data->is_philo_died = 0;
		if (argv[5] == NULL)
			data->philo_max_eaten = -1;
		else
			data->philo_max_eaten = ft_atoi(argv[5]);
		if (generate_sem_names_for_philo(data, argv[1]) == FAILURE)
			return (NULL);
		if (open_semaphores(data, argv[1]) == 0)
		{
			free_prev_data_guards(data->data_guard, data->philo_len);
			free(data);
			return (NULL);
		}
	}
	return (data);
}
