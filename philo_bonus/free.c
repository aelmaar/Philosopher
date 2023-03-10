/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:40:51 by ael-maar          #+#    #+#             */
/*   Updated: 2023/03/10 15:01:29 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_all(t_shared_data *data, t_philo *philo)
{
	sem_close(data->forks);
	sem_close(data->printf_guard);
	sem_close(data->max_eaten);
	free(data);
	free(philo);
}
