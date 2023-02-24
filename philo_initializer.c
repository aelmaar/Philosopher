/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_initializer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:21:27 by ael-maar          #+#    #+#             */
/*   Updated: 2023/02/24 13:30:15 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	initialize(t_info *info)
{
	int	i;
	// initialize mutexes
	i = 0;
	while (i < info->philo_len)
	{
		pthread_mutex_init(&(info->forks[i++]), NULL);
	}
	pthread_mutex_init(&(info->printf_guard), NULL);
	pthread_mutex_init(&(info->state_guard), NULL);
}

t_info	*generate_info_struct(int argc, char *argv[])
{
	t_info	*info;
	int		i;

	info = malloc(sizeof(t_info));
	if (info)
	{
		info->forks = malloc(atoi(argv[1]) * sizeof(pthread_mutex_t));
		info->asreal = malloc(atoi(argv[1]) * sizeof(long long));
		info->philo_len = atoi(argv[1]);
		info->time_to_die = atoi(argv[2]);
		info->time_to_eat = atoi(argv[3]);
		info->time_to_sleep = atoi(argv[4]);
		if (argv[5] == NULL)
		{
			info->g_eat_times = 0;
			info->is_all_eaten = -1;
		}
		else if (atoi(argv[5]) >= 0)
		{
			info->g_eat_times = atoi(argv[5]);
			info->is_all_eaten = 0;
		}
		info->running_time = timestamp_in_ms();
		info->a_philo_died = 0;
		initialize(info);
		i = 0;
	}
	return (info);
}
