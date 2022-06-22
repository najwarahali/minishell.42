/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_rdr_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydahni <ydahni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 15:40:50 by ydahni            #+#    #+#             */
/*   Updated: 2022/06/19 21:17:42 by ydahni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	calcul_squote(t_lexer *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line->str[i])
	{
		if (line->str[i] == 34)
			j++;
		i++;
	}
	i = 0;
	while (line->str[i])
	{
		if (line->str[i] == 39)
			j++;
		i++;
	}
	return (j);
}

int	calcul_dquote(t_lexer *line)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (line->str[i])
	{
		if (line->str[i] == '<' && line->str[i + 1] != '<')
			j++;
		i++;
	}
	i = 0;
	while (line->str[i])
	{
		if (line->str[i] == '>' && line->str[i + 1] != '>')
			j++;
		i++;
	}
	return (j);
}

int	calcul_quote1(t_lexer *line, int j)
{
	int	i;

	i = 0;
	while (line->str[i])
	{
		if (line->str[i] == 34)
			j++;
		i++;
	}
	i = 0;
	while (line->str[i])
	{
		if (line->str[i] == 39)
			j++;
		i++;
	}
	return (j);
}

int	calcul_q(t_lexer *line)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (line->str[i])
	{
		if (line->str[i] == '<' && line->str[i + 1] != '<')
			j++;
		i++;
	}
	i = 0;
	while (line->str[i])
	{
		if (line->str[i] == '>' && line->str[i + 1] != '>')
			j++;
		i++;
	}
	i = 0;
	j = calcul_quote1(line, j);
	return (j);
}

int	calcul_c(t_lexer *lexer, int c)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (lexer->str[i])
	{
		if (lexer->str[i] == c)
			j++;
		i++;
	}
	return (j);
}
