/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrahali <nrahali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 04:08:28 by ydahni            #+#    #+#             */
/*   Updated: 2022/06/20 02:53:57 by nrahali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_counterword(char const *s, char c)
{
	int	i;
	int	x;

	x = 0;
	i = 0;
	if (s[i] != c)
		x++;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			x++;
		i++;
	}
	return (x);
}

int	ft_counterchar(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
	{
		i++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	new = malloc(sizeof(char *) * (ft_counterword(s, c) + 1));
	if (!new)
		return (NULL);
	while (s[i])
	{
		while (j < ft_counterword(s, c))
		{
			while (s[i] == c && s[i])
				i++;
			new[j++] = ft_substr(s, i, ft_counterchar(s + i, c));
			i += ft_counterchar(s + i, c);
		}
		if (s[i])
			i++;
	}
	new[j] = NULL;
	return (new);
}
