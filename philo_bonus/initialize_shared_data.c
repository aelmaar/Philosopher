/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_shared_data.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:37:49 by ael-maar          #+#    #+#             */
/*   Updated: 2023/02/28 15:25:58 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include "stdio.h"

t_shared_data   *initialize_philo_data(char *argv[])
{
    t_shared_data   *data;

    data = malloc(sizeof(t_shared_data));
    if (data)
    {
        sem_unlink("/forks");
        sem_unlink("/printf");
        data->forks = sem_open("/forks", O_CREAT, 0644, atoi(argv[1]));
        data->printf_guard = sem_open("/printf", O_CREAT, 0644, 1);
        data->asreal = malloc(atoi(argv[1]) * sizeof(time_t));
        data->time_to_die = atoi(argv[2]);
        data->time_to_eat = atoi(argv[3]);
        data->time_to_sleep = atoi(argv[4]);
        data->philo_len = atoi(argv[1]);
        data->is_philo_died = 0;
        // data->running_time = timestamp_in_ms();
    }
    return (data);
}