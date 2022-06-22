/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydahni <ydahni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:06:48 by ydahni            #+#    #+#             */
/*   Updated: 2021/11/21 18:25:24 by ydahni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*new;
	size_t			i;

	new = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		new[i] = c;
		i++;
	}
	return (str);
}
