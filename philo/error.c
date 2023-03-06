/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:12:30 by ael-maar          #+#    #+#             */
/*   Updated: 2023/03/06 13:51:02 by ael-maar         ###   ########.fr       */
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
}

int	destroy_prev_shared_mutexes(pthread_mutex_t *mutexes, \
						int mutex_error, int last_mutex)
{
	int	i;

	if (mutex_error != 0)
	{
		i = 0;
		while (i <= last_mutex)
		{
			pthread_mutex_destroy(mutexes + i);
			++i;
		}
		// pthread_error_message(mutex_error, "Error initializing a mutex");
		return (0);
	}
	return (1);
}
