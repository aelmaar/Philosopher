/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:16:18 by ael-maar          #+#    #+#             */
/*   Updated: 2023/03/13 13:58:55 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_shared_data			*data;
	t_philo					*philo;

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
				free_all_data(data, philo);
				return (FAILURE);
			}
			if (init_threads_and_coordinate(philo, data, argv) == FAILURE)
				return (FAILURE);
			free_all_data(data, philo);
		}
	}
	return (FAILURE);
}
