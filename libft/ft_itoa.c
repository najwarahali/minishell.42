/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydahni <ydahni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 01:22:04 by ydahni            #+#    #+#             */
/*   Updated: 2021/11/21 01:44:12 by ydahni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_counter(int n)
{
	unsigned int	i;
	unsigned int	c;
	int				flag;

	i = 1;
	if (n < 0)
	{
		c = -n;
		flag = 1;
		while (c / 10)
		{
			i++;
			c /= 10;
		}
	}
	else
	{
		flag = 0;
		while (n / 10)
		{
			i++;
			n /= 10;
		}
	}
	return (i + flag);
}

char	*ft_itoa2(int n, int size, char *str)
{
	unsigned int	c;

	if (n < 0)
	{
		c = -n;
		while (size > 0)
		{
			str[size] = c % 10 + 48;
			size--;
			c /= 10;
		}
		str[0] = '-';
	}
	else
	{
		c = n;
		while (size >= 0)
		{
				str[size] = c % 10 + 48;
				c /= 10;
				size--;
		}
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				size;

	size = ft_counter(n);
	str = ft_calloc(sizeof(char), (size + 1));
	if (!str)
		return (NULL);
	size--;
	ft_itoa2(n, size, str);
	return (str);
}
