/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:13:17 by ael-maar          #+#    #+#             */
/*   Updated: 2023/03/06 13:46:26 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*free_shared_data(t_info *data)
{
	free(data->forks);
	free(data->asreal);
	free(data);
	return (NULL);
}

void	destroy_shared_mutexes(t_info *data)
{
	int	i;

	i = 0;
	while (i < data->philo_len)
		pthread_mutex_destroy(&(data->forks[i++]));
	pthread_mutex_destroy(&(data->printf_guard));
}

void	free_all_data(t_info *data, t_philos *philo)
{
	destroy_shared_mutexes(data);
	free(data->forks);
	free(data->asreal);
	free(data);
	free(philo);
}
