/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydahni <ydahni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 00:56:56 by ydahni            #+#    #+#             */
/*   Updated: 2021/11/21 19:14:27 by ydahni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*x;

	x = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (x[i] == (unsigned char)c)
			return (&x[i]);
		i++;
	}
	return (NULL);
}
