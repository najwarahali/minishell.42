/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_add_number.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydahni <ydahni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 17:56:34 by ydahni            #+#    #+#             */
/*   Updated: 2022/06/19 21:18:40 by ydahni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_norm	*add_number_double_qoutes(t_norm *l, char *s)
{
	if (s[l->i] == 39)
	{
		l->p[l->j++] = '1';
		l->i++;
		while (s[l->i] != 39 && s[l->i] != '\0')
		{
			l->p[l->j] = '1';
			l->i++;
			l->j++;
		}
		if (s[l->i] == 39)
		{
			l->p[l->j] = '1';
			l->j++;
			l->i++;
		}
	}
	return (l);
}

t_norm	*add_number_single_qoutes(t_norm *l, char *s)
{
	if (s[l->i] == 34)
	{
		l->p[l->j++] = '1';
		l->i++;
		while (s[l->i] != 34 && s[l->i] != '\0')
		{
			l->p[l->j] = '1';
			l->i++;
			l->j++;
		}
		if (s[l->i] == 34)
		{
			l->p[l->j] = '1';
			l->j++;
			l->i++;
		}
	}
	return (l);
}

t_norm	*add_number(char *s)
{
	t_norm	*l;

	l = malloc(sizeof(t_norm));
	l->p = malloc(ft_strlen(s) + 1);
	l->j = 0;
	l->i = 0;
	while (s[l->i])
	{
		if (s[l->i] == 39)
			l = add_number_double_qoutes(l, s);
		if (s[l->i] == 34)
			l = add_number_single_qoutes(l, s);
		if (s[l->i] != '\0' && s[l->i] != 39 && s[l->i] != 34)
		{
			l->p[l->j] = '0';
			l->j++;
			l->i++;
		}
	}
	l->p[l->j] = '\0';
	return (l);
}
