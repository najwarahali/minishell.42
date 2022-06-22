/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydahni <ydahni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 17:03:14 by ydahni            #+#    #+#             */
/*   Updated: 2022/06/18 22:44:44 by ydahni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	int		l;
	int		a;
	int		b;
	char	*p;

	b = 0;
	a = 0;
	if (!s1 || !s2)
		return (0);
	l = ft_strlen(s1) + ft_strlen(s2);
	p = malloc(sizeof(char) * (l + 1));
	if (!p)
		return (0);
	while (s1[a])
	{
		p[a] = s1[a];
		a++;
	}
	while (s2[b])
	{
		p[a++] = s2[b++];
	}
	p[a] = '\0';
	free(s1);
	return (p);
}
