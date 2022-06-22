/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydahni <ydahni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 12:39:15 by ydahni            #+#    #+#             */
/*   Updated: 2021/11/21 22:04:21 by ydahni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	i = 0;
	if (s == d)
		return (d);
	if (d > s)
	{
		while (len--)
		{
			d[len] = s[len];
		}
		return (d);
	}
	while (i < len)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}
