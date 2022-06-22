/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydahni <ydahni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:39:02 by ydahni            #+#    #+#             */
/*   Updated: 2022/06/19 21:18:18 by ydahni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_norm(t_norm *l)
{
	int	i;

	i = 0;
	while (l->split[i])
	{
		free(l->split[i]);
		i++;
	}
	free(l->split);
}

void	free_fnc_token_complete(t_token *new, t_token *tmp)
{
	while (new)
	{
		tmp = new;
		new = new->next;
		free(tmp);
	}
}

void	free_fnc_token(t_token *new)
{
	t_token	*tmp;
	t_rdr	*tmp3;

	tmp = new;
	while (tmp)
	{
		if (tmp->cmd != NULL)
			free(tmp->cmd);
		if (tmp->arg != NULL)
			free_fnc_arg(tmp->arg);
		if (tmp->opt != NULL)
			free(tmp->opt);
		if (tmp->rdr != NULL)
		{
			while (tmp->rdr)
			{
				free(tmp->rdr->value);
				tmp3 = tmp->rdr;
				tmp->rdr = tmp->rdr->next;
				free(tmp3);
			}
		}
		tmp = tmp->next;
	}
	free_fnc_token_complete(new, tmp);
}

void	free_fnc2(t_node *s)
{
	t_node	*tmp;

	tmp = s;
	while (tmp)
	{
		free(tmp->data);
		tmp = tmp->next;
	}
	while (s)
	{
		tmp = s;
		s = s->next;
		free(tmp);
	}
}
