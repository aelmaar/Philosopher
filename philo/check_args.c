/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 11:55:04 by ael-maar          #+#    #+#             */
/*   Updated: 2023/03/10 15:09:15 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdigit(char num)
{
	return (num >= 48 && num <= 57);
}

static int	ft_strlen(char *arg)
{
	int	len;

	len = 0;
	while (arg[len])
		len++;
	return (len);
}

static int	is_valid_arg(char *arg)
{
	long	nb;

	if (ft_strlen(arg) > 10)
		return (FAILURE);
	nb = 0;
	while (ft_isdigit(*arg))
	{
		nb = (nb * 10) + (*arg - 48);
		arg++;
	}
	if (*arg != '\0' && ft_isdigit(*arg) == 0)
		return (FAILURE);
	if (nb > INT_MAX)
		return (FAILURE);
	return (SUCCESS);
}

int	check_args(char *argv[])
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (is_valid_arg(argv[i]) == 0)
		{
			ft_putstr_fd("The arguments are not valid\n", 2);
			return (FAILURE);
		}
		++i;
	}
	if ((argv[5] != NULL && ft_atoi(argv[5]) == 0) || ft_atoi(argv[1]) == 0)
	{
		ft_putstr_fd("Please make sure you specify a positive value for philosophers arg \
and numbers of times each philosopher must eat arg\n", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}
