/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:13:17 by ael-maar          #+#    #+#             */
/*   Updated: 2023/03/13 12:06:47 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*free_shared_data(t_shared_data *data)
{
	free(data->forks);
	free(data->asreal);
	free(data);
	return (NULL);
}

void	destroy_shared_mutexes(t_shared_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_len)
		pthread_mutex_destroy(&(data->forks[i++]));
	pthread_mutex_destroy(&(data->printf_guard));
	pthread_mutex_destroy(&(data->shared_guard));
}

void	destroy_philo_mutexes(t_philo *philo, t_shared_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_len)
		pthread_mutex_destroy(&(philo[i++].data_guard));
}

void	free_all_data(t_shared_data *data, t_philo *philo)
{
	if (philo != NULL)
		destroy_philo_mutexes(philo, data);
	destroy_shared_mutexes(data);
	free(data->forks);
	free(data->asreal);
	free(data);
	free(philo);
}
