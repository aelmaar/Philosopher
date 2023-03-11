/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maar <ael-maar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:35:37 by ael-maar          #+#    #+#             */
/*   Updated: 2023/03/11 18:22:35 by ael-maar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static short	calc_size_int(int n)
{
	long	nb;
	short	len;

	nb = n;
	len = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		len++;
		nb *= (-1);
	}
	while (nb > 0)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*res;
	long	nb;
	short	size;

	size = calc_size_int(n);
	res = malloc((size + 1) * sizeof(char));
	nb = n;
	if (res)
	{
		if (nb == 0)
			res[0] = 48;
		res[size--] = '\0';
		if (nb < 0)
		{
			res[0] = '-';
			nb *= (-1);
		}
		while (nb > 0)
		{
			res[size--] = (nb % 10) + 48;
			nb /= 10;
		}
	}
	return (res);
}

static size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	char	*temp_s2;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	new_str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	temp_s2 = (char *)s2;
	if (new_str)
	{
		i = 0;
		while (*s1)
			new_str[i++] = *(s1++);
		while (*temp_s2)
			new_str[i++] = *(temp_s2++);
		new_str[i] = '\0';
	}
	free((void *)s2);
	return (new_str);
}
