/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:12:30 by ael-maar          #+#    #+#             */
/*   Updated: 2023/03/10 18:36:11 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pthread_error_message(int pthread_num, char *error_message)
{
	ft_putstr_fd(error_message, 2);
	if (pthread_num >= 0)
	{
		ft_putnbr_fd(pthread_num, 2);
	}
	ft_putstr_fd("\n", 2);
}

int	destroy_prev_shared_mutexes(pthread_mutex_t *mutexes, \
						int mutex_error, int last_mutex)
{
	int	i;

	if (mutex_error != 0)
	{
		i = 0;
		while (i < last_mutex)
		{
			pthread_mutex_destroy(mutexes + i);
			++i;
		}
		return (FAILURE);
	}
	return (SUCCESS);
}

int	destroy_prev_philo_mutexes(t_philo *philo, int mutex_error, int last_mutex)
{
	int	i;

	if (mutex_error != 0)
	{
		i = 0;
		while (i < last_mutex)
		{
			pthread_mutex_destroy(&(philo[i].data_guard));
			++i;
		}
		return (FAILURE);
	}
	return (SUCCESS);
}
