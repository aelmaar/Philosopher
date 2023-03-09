/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:38:40 by ael-maar          #+#    #+#             */
/*   Updated: 2023/03/09 16:24:22 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int main(int argc, char *argv[])
{
	t_philo			*philo;
	t_shared_data	*data;

	if (argc > 4)
	{
		if (check_args(argv) == 0)
			return (0);
		data = initialize_philo_data(argv);
		if (data)
		{
			philo = malloc(ft_atoi(argv[1]) * sizeof(t_philo));
			if (philo == NULL)
			{
				free_all(data, philo);
				return (0);
			}
			if (init_processes_and_coordinate(philo, data) == 0)
				return (0);
		}
	}
	return (1);
}
