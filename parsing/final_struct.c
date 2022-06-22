/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydahni <ydahni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 20:45:15 by ydahni            #+#    #+#             */
/*   Updated: 2022/06/19 21:18:14 by ydahni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	calcul_arg_allocation(t_node *old)
{
	t_node	*tmp;
	int		i;

	i = 0;
	tmp = old;
	while (tmp)
	{
		if (tmp->e_type == TOKEN_PIPE)
			break ;
		if (tmp->e_type == TOKEN_ARG)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

t_token	*final_struct_norm2(t_token *new, t_node *old, t_rdr *tmp)
{
	if (old->e_type == TOKEN_OUTPUT)
	{
		tmp = malloc(sizeof(t_rdr));
		tmp->value = ft_strdup(old->data);
		tmp->type = 1;
		tmp->next = NULL;
		add_node_last_rdr(tmp, &new->rdr);
	}
	else if (old->e_type == TOKEN_APPEND)
	{
		tmp = malloc(sizeof(t_rdr));
		tmp->value = ft_strdup(old->data);
		tmp->type = 2;
		tmp->next = NULL;
		add_node_last_rdr(tmp, &new->rdr);
	}
	else if (old->e_type == TOKEN_HEREDOC)
	{
		tmp = malloc(sizeof(t_rdr));
		tmp->value = ft_strdup(old->data);
		tmp->type = 3;
		tmp->next = NULL;
		add_node_last_rdr(tmp, &new->rdr);
	}
	return (new);
}

t_token	*final_struct_norm(t_token *new, t_node *old, t_norm *l)
{
	t_rdr	*tmp;

	tmp = NULL;
	if (old->e_type == TOKEN_CMD)
		new->cmd = ft_strdup(old->data);
	else if (old->e_type == TOKEN_OPTION)
		new->opt = ft_strdup(old->data);
	else if (old->e_type == TOKEN_ARG)
	{
		new->arg[l->i] = ft_strdup(old->data);
		l->i++;
	}
	else if (old->e_type == TOKEN_INPUT)
	{
		tmp = malloc(sizeof(t_rdr));
		tmp->value = ft_strdup(old->data);
		tmp->type = 0;
		tmp->next = NULL;
		add_node_last_rdr(tmp, &new->rdr);
	}
	new = final_struct_norm2(new, old, tmp);
	return (new);
}

t_token	*final_struct(t_node *old)
{
	t_token	*tmp;
	t_token	*new;
	t_norm	l;

	tmp = NULL;
	while (old)
	{
		l.i = 0;
		new = init_token_f(new);
		new->arg = malloc(sizeof(char *) * (calcul_arg_allocation(old) + 1));
		while (old)
		{
			if (old->e_type == TOKEN_PIPE)
				break ;
			new = final_struct_norm(new, old, &l);
			old = old->next;
		}
		new->arg[l.i] = NULL;
		new->next = NULL;
		add_node_last_token_f(new, &tmp);
		if (old != NULL)
			old = old->next;
	}
	return (tmp);
}
