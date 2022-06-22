/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydahni <ydahni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 01:53:45 by ydahni            #+#    #+#             */
/*   Updated: 2021/11/21 19:15:14 by ydahni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	int		i;
	char	*p;
	char	*x;

	if (!s || !f)
		return (NULL);
	i = 0;
	x = (char *)s;
	len = ft_strlen(s);
	p = malloc(len + 1);
	if (!p)
		return (NULL);
	while (s[i])
	{
		p[i] = f(i, x[i]);
		i++;
	}
	p[i] = '\0';
	return (p);
}
