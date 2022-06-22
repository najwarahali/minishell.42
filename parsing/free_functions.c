/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydahni <ydahni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 23:51:54 by ydahni            #+#    #+#             */
/*   Updated: 2022/06/19 21:18:21 by ydahni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fnc_free_spc(char *str, t_norm *l)
{
	if (str != NULL)
		free(str);
	free(l->p);
	free(l);
}

void	free_spc(t_norm *l)
{
	free(l->p);
	free(l);
}

void	free_fnc(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_fnc_arg(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	ft_free_it(char	**cmd, int i)
{
	while (cmd[i] != '\0')
	{
		free (cmd[i]);
		i++;
	}
	free (cmd);
}
