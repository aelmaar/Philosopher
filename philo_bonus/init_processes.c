/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:51:58 by ael-maar          #+#    #+#             */
/*   Updated: 2023/03/13 11:29:15 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*watch_eating(void *arg)
{
	t_philo	*philo;
	int		philos_eat;
	int		i;

	philos_eat = 0;
	philo = (t_philo *)arg;
	if (philo->data->philo_max_eaten != -1)
	{
		while (1)
		{
			sem_wait(philo->data->max_eaten);
			philos_eat++;
			if (philos_eat >= philo->data->philo_len)
			{
				i = 0;
				while (i < philo->data->philo_len)
					kill(philo[i++].pid, SIGKILL);
				break ;
			}
		}
	}
	return (NULL);
}

static int	init_processes(t_philo *philo, t_shared_data *data)
{
	int	i;

	i = 0;
	data->running_time = timestamp_in_ms();
	while (i < data->philo_len)
	{
		philo[i].philo_num = i;
		philo[i].data = data;
		philo[i].pid = fork();
		if (philo[i].pid == 0)
			run_actions(&(philo[i]));
		else if (philo[i].pid > 0)
			i++;
		else
		{
			kill_processes(philo, i);
			free_all(data, philo);
			ft_putstr_fd("Error creating the process: ", 2);
			ft_putnbr_fd(philo->philo_num, 2);
			ft_putstr_fd("\n", 2);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

int	init_processes_and_coordinate(t_philo *philo, t_shared_data *data)
{
	pthread_t	thread_watch_eat;

	if (init_processes(philo, data) == 0)
		return (FAILURE);
	if (pthread_create(&(thread_watch_eat), NULL, \
	watch_eating, (void *)philo) != 0)
	{
		ft_putstr_fd("Error creating the thread in the main process\n", 2);
		kill_processes(philo, data->philo_len);
		free_all(data, philo);
		return (FAILURE);
	}
	waitpid(-1, NULL, 0);
	kill_processes(philo, data->philo_len);
	return (SUCCESS);
}
