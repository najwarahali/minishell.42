/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydahni <ydahni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:15:54 by ydahni            #+#    #+#             */
/*   Updated: 2022/06/19 21:18:43 by ydahni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_counterword_a(char *s, char c, char *tmp)
{
	int	i;
	int	x;

	x = 0;
	i = 0;
	if (s[i] != c && tmp[i] == '0')
		x++;
	if (s[i] != c && tmp[i] == '1')
		x++;
	while (s[i])
	{
		if ((s[i] == c && s[i + 1] != c && s[i + 1] != '\0' && tmp[i] == '0'))
			x++;
		i++;
	}
	return (x);
}

int	ft_counterchar_a(char *s, int x, char c, char *tmp)
{
	int	i;

	i = 0;
	if (tmp[x] == '1')
	{
		while (tmp[x] == '1')
		{
			i++;
			x++;
		}
	}
	if (s[x] != c && tmp[x] == '0')
	{
		while (s[x])
		{
			if (s[x] == c && tmp[x] == '0')
				break ;
			i++;
			x++;
		}
	}
	return (i);
}

char	**ft_split_a(char *s, char c)
{
	char	**new;
	t_norm	*l;
	int		i;
	int		j;

	i = 0;
	j = 0;
	l = add_number(s);
	new = malloc(sizeof(char *) * (ft_counterword_a(s, c, l->p) + 1));
	while (s[i])
	{
		while (j < ft_counterword_a(s, c, l->p))
		{
			while (s[i] == c && s[i] && l->p[i] == '0')
				i++;
			new[j++] = ft_substr(s, i, ft_counterchar_a(s, i, c, l->p));
			i += ft_counterchar_a(s, i, c, l->p);
		}
		if (s[i])
			i++;
	}
	new[j] = NULL;
	free(l->p);
	free(l);
	return (new);
}
