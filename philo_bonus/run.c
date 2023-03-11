/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:38:40 by ael-maar          #+#    #+#             */
/*   Updated: 2023/03/11 13:36:45 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char *argv[])
{
	t_philo			*philo;
	t_shared_data	*data;

	if (argc > 4 && argc <= 6)
	{
		if (check_args(argv) == FAILURE)
			return (FAILURE);
		data = init_shared_data(argv);
		if (data)
		{
			philo = malloc(ft_atoi(argv[1]) * sizeof(t_philo));
			if (philo == NULL)
			{
				free_all(data, philo);
				return (FAILURE);
			}
			if (init_processes_and_coordinate(philo, data) == 0)
				return (FAILURE);
		}
	}
	return (SUCCESS);
}
