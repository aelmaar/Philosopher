/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:41:08 by ael-maar          #+#    #+#             */
/*   Updated: 2023/03/11 17:51:57 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		n *= (-1);
		ft_putchar_fd('-', fd);
	}
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
	}
	ft_putchar_fd((n % 10) + 48, fd);
}

int	ft_atoi(const char *str)
{
	long	nb;

	if (str == NULL)
		return (FAILURE);
	nb = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	while (*str >= 48 && *str <= 57)
	{
		nb = (nb * 10) + (*str - 48);
		str++;
	}
	return (nb);
}

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*new_str;
// 	size_t	i;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	new_str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
// 	if (new_str)
// 	{
// 		i = 0;
// 		while (*s1)
// 			new_str[i++] = *(s1++);
// 		while (*s2)
// 			new_str[i++] = *(s2++);
// 		new_str[i] = '\0';
// 	}
// 	free(s2);
// 	return (new_str);
// }
