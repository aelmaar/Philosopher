/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:16:18 by ael-maar          #+#    #+#             */
/*   Updated: 2023/03/06 13:30:37 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_info			*data;
	t_philos		*philo;

	if (argc > 4)
	{
		if (check_args(argv) == 0)
			return (0);
		data = init_shared_data(argv);
		if (data)
		{
			philo = malloc(ft_atoi(argv[1]) * sizeof(t_philos));
			if (philo == NULL)
			{
				free_all_data(data, philo);
				return (0);
			}
			if (init_threads_and_coordinate(philo, data, argv) == 0)
				return (0);
			free_all_data(data, philo);
		}
	}
	return (0);
}
