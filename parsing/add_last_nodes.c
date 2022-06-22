/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_last_nodes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydahni <ydahni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 20:17:03 by ydahni            #+#    #+#             */
/*   Updated: 2022/06/19 21:17:31 by ydahni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_node_last_rdr(t_rdr *temp, t_rdr **head)
{
	t_rdr	*last;

	if ((*head) == NULL)
	{
		(*head) = temp;
	}
	else
	{
		last = (*head);
		while (last->next != NULL)
		{
			last = last->next;
		}
		last->next = temp;
	}
}

void	add_node_last_token_f(t_token *temp, t_token **head)
{
	t_token	*last;

	if ((*head) == NULL)
	{
		(*head) = temp;
	}
	else
	{
		last = (*head);
		while (last->next != NULL)
		{
			last = last->next;
		}
		last->next = temp;
	}
}

void	add_node_last_env(t_env *temp, t_env **head)
{
	t_env	*last;

	if ((*head) == NULL)
	{
		(*head) = temp;
	}
	else
	{
		last = (*head);
		while (last->next != NULL)
		{
			last = last->next;
		}
		last->next = temp;
	}
}

void	add_node_last(t_node *temp, t_node **head)
{
	t_node	*last;

	if ((*head) == NULL)
	{
		(*head) = temp;
	}
	else
	{
		last = (*head);
		while (last->next != NULL)
		{
			last = last->next;
		}
		last->next = temp;
	}
}
