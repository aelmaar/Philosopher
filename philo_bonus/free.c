/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:40:51 by ael-maar          #+#    #+#             */
/*   Updated: 2023/03/11 17:49:31 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_data_guards(t_shared_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_len)
		free(data->data_guard[i++]);
	free(data->data_guard);
}

void	unlink_philo_semaphores(t_philo *philo, t_shared_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_len)
		sem_close(philo[i++].data_guard);
	i = 0;
	while (i < data->philo_len)
		sem_unlink(data->data_guard[i++]);
}

void	unlink_shared_semaphores_and_free(t_shared_data *data, t_philo *philo)
{
	free_data_guards(data);
	sem_close(data->forks);
	sem_close(data->printf_guard);
	sem_close(data->max_eaten);
	sem_unlink("/forks");
	sem_unlink("/printf_guard");
	sem_unlink("/eat_times");
	free(data);
	free(philo);
}

void	free_all(t_shared_data *data, t_philo *philo)
{
	unlink_philo_semaphores(philo, data);
	unlink_shared_semaphores_and_free(data, philo);
}
