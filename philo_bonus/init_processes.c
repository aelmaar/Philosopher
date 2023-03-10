/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:51:58 by ael-maar          #+#    #+#             */
/*   Updated: 2023/03/10 15:02:41 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*death_or_done(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if ((timestamp_in_ms() - philo->last_meal) >= philo->data->time_to_die)
		{
			sem_wait(philo->data->printf_guard);
			printf("%ld %d %s\n", timestamp_in_ms() - philo->data->running_time, \
			philo->philo_num, "died");
			exit(0);
		}
		if (philo->data->philo_max_eaten != -1 && \
		philo->is_enough_eat >= philo->data->philo_max_eaten)
		{
			sem_post(philo->data->max_eaten);
			break ;
		}
	}
	return (NULL);
}

// void    *philo_max_eating(void *arg)
// {
// 	t_philo *philo = (t_philo *)arg;

// 	philo->is_enough_eat = 0;
// 	if (philo->data->philo_max_eaten != -1)
// 	{
// 		while (1)
// 		{
// 			if (philo->is_enough_eat >= philo->data->philo_max_eaten)
// 			{
// 				sem_post(philo->data->max_eaten);
// 				break ;
// 			}
// 			usleep(100);
// 		}
// 	}
// 	return (NULL);
// }

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

static void	run_actions(t_philo *philo)
{
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
		sem_wait(philo->data->forks);
		log_sleep("has taken a fork", 0, philo);
		sem_wait(philo->data->forks);
		log_sleep("has taken a fork", 0, philo);
		log_sleep("is eating", philo->data->time_to_eat, philo);
		philo->last_meal = timestamp_in_ms();
		philo->is_enough_eat++;
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
		log_sleep("is sleeping", philo->data->time_to_sleep, philo);
	}
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
			free_all(data, philo);
			kill_processes(philo, i);
			ft_putstr_fd("Error creating the process: ", 2);
			ft_putnbr_fd(philo->philo_num, 2);
			ft_putstr_fd("\n", 2);
			return (0);
		}
	}
	return (1);
}

int	init_processes_and_coordinate(t_philo *philo, t_shared_data *data)
{
	pthread_t	thread_watch_eat;

	if (init_processes(philo, data) == 0)
		return (0);
	if (pthread_create(&(thread_watch_eat), NULL, \
	watch_eating, (void *)philo) != 0)
	{
		free_all(data, philo);
		ft_putstr_fd("Error creating the thread in the main process\n", 2);
		kill_processes(philo, data->philo_len);
		return (0);
	}
	waitpid(-1, NULL, 0);
	kill_processes(philo, data->philo_len);
	return (1);
}
