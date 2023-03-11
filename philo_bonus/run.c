/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:38:40 by ael-maar          #+#    #+#             */
/*   Updated: 2023/03/11 17:49:12 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	unlink_prev_philo_semaphores(t_philo *philo, t_shared_data *data, \
									int last_semaphore)
{
	int	i;

	i = 0;
	while (i < last_semaphore)
		sem_close(philo[i++].data_guard);
	i = 0;
	while (i < last_semaphore)
		sem_unlink(data->data_guard[i++]);
}

static int	open_philo_semaphores(t_philo *philo, t_shared_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_len)
		sem_unlink(data->data_guard[i++]);
	i = 0;
	while (i < data->philo_len)
	{
		philo[i].data_guard = sem_open(data->data_guard[i], O_CREAT, 0644, 1);
		if (philo[i].data_guard == SEM_FAILED)
		{
			unlink_prev_philo_semaphores(philo, data, i);
			unlink_shared_semaphores_and_free(data, philo);
			return (FAILURE);
		}
		++i;
	}
	return (SUCCESS);
}

static int	run(char *argv[])
{
	t_philo			*philo;
	t_shared_data	*data;

	data = init_shared_data(argv);
	if (data)
	{
		philo = malloc(ft_atoi(argv[1]) * sizeof(t_philo));
		if (philo == NULL)
		{
			unlink_shared_semaphores_and_free(data, philo);
			return (FAILURE);
		}
		if (open_philo_semaphores(philo, data) == FAILURE)
			return (FAILURE);
		if (init_processes_and_coordinate(philo, data) == FAILURE)
			return (FAILURE);
		free_all(data, philo);
		return (SUCCESS);
	}
	return (FAILURE);
}

int	main(int argc, char *argv[])
{
	if (argc > 4 && argc <= 6)
	{
		if (check_args(argv) == FAILURE)
			return (FAILURE);
		if (run(argv) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
