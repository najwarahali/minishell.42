/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydahni <ydahni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 20:17:37 by ydahni            #+#    #+#             */
/*   Updated: 2022/06/19 21:17:38 by ydahni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*add_space_2(char *str, t_lexer *tmp)
{
	int		i;
	int		j;
	char	*save;
	t_norm	*l;

	l = add_number(str);
	j = calcul_q(tmp);
	save = malloc (ft_strlen(str) + j + 1);
	j = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] != '<' && str[i] != '>') && (str[i + 1] == '<'
				|| str[i + 1] == '>') && l->p[i + 1] == '0')
		{
			save[j++] = str[i++];
			save[j++] = ' ';
			while ((str[i] == '<' || str[i] == '>') && str[i] && l->p[i] == '0')
				save[j++] = str[i++];
		}
		save[j++] = str[i++];
	}
	save[j] = '\0';
	fnc_free_spc(str, l);
	return (save);
}

void	add_space_rdr_norm(char *save, char *str, int i, int j)
{
	int		counter;
	t_norm	*l;

	l = add_number(str);
	counter = 0;
	while (str[i])
	{
		while ((str[i] == '<' || str[i] == '>') && str[i] && l->p[i] == '0')
		{
			save[i + j] = str[i];
			counter++;
			i++;
		}
		if (counter != 0)
		{
			save[i + j] = ' ';
			j++;
			counter = 0;
		}
		save[i + j] = str[i];
		i++;
	}
	save[i + j] = '\0';
	free(l->p);
	free(l);
}

char	*add_space_rdr(char *str, t_lexer *tmp)
{
	int		i;
	int		j;
	char	*save;

	i = 0;
	j = calcul_q(tmp);
	save = malloc (ft_strlen(str) + j + 1);
	j = 0;
	add_space_rdr_norm(save, str, i, j);
	return (save);
}

char	*add_space_pipe(char *str, t_lexer *tmp)
{
	int		i;
	int		j;
	char	*save;
	t_norm	*l;

	l = add_number(str);
	j = calcul_c(tmp, '|');
	save = malloc (ft_strlen(str) + (j * 2) + 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '|' && str[i + 1] == '|' && l->p[i + 1] == '0')
		{
			save[j++] = str[i++];
			save[j++] = ' ';
			save[j++] = str[i++];
			save[j++] = ' ';
		}
		save[j++] = str[i++];
	}
	save[j] = '\0';
	fnc_free_spc(str, l);
	return (save);
}

char	*add_space(char *line, t_lexer *tmp)
{
	char	*new;
	t_lexer	*lexer;

	lexer = tmp;
	new = add_space_rdr(line, lexer);
	new = add_space_2(new, lexer);
	new = add_space_pipe(new, lexer);
	return (new);
}
