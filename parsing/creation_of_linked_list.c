/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation_of_linked_list.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydahni <ydahni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 19:02:30 by ydahni            #+#    #+#             */
/*   Updated: 2022/06/21 22:45:35 by ydahni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_option(t_node *new)
{
	t_node	*tmp;

	tmp = new;
	if (tmp != NULL)
	{
		while (tmp)
		{
			if (tmp->e_type == TOKEN_OPTION)
				return (1);
			tmp = tmp->next;
		}
	}
	return (0);
}

t_node	*create_linked_list_norm1(t_norm *l, t_node *new)
{
	if (l->split[l->i][l->j] == '>')
	{
		l->j++;
		if (l->split[l->i][l->j] == '>')
			new = creation_nodes(l->split[l->i + 1], TOKEN_APPEND);
		else
			new = creation_nodes(l->split[l->i + 1], TOKEN_OUTPUT);
		l->i++;
	}
	return (new);
}

t_node	*create_linked_list_norm(t_norm *l, t_node *arg, t_node *new)
{
	if (l->split[l->i][l->j] == '>')
		new = create_linked_list_norm1(l, new);
	else if (l->split[l->i][l->j] == '<')
	{
		l->j++;
		if (l->split[l->i][l->j] == '<')
			new = creation_nodes(l->split[l->i + 1], TOKEN_HEREDOC);
		else
			new = creation_nodes(l->split[l->i + 1], TOKEN_INPUT);
		l->i++;
	}
	else if (!check_cmd(arg) && (l->split[l->i][l->j] == 39
		|| l->split[l->i][l->j] == 34))
		new = creation_nodes(l->split[l->i], TOKEN_CMD);
	else if (!check_cmd(arg) && (l->split[l->i][l->j] != '>'
		&& l->split[l->i][l->j] != '<' && l->split[l->i][l->j] != '|'))
		new = creation_nodes(l->split[l->i], TOKEN_CMD);
	else if (check_cmd(arg) && (l->split[l->i][l->j] != '>'
		&& l->split[l->i][l->j] != '<' && l->split[l->i][l->j] != '|'))
		new = creation_nodes(l->split[l->i], TOKEN_ARG);
	return (new);
}

t_node	*create_linked_list(char *tmp, t_env **ev)
{
	t_node	*arg;
	t_node	*new;
	t_norm	*l;

	l = malloc(sizeof(t_norm));
	l->split = ft_split_a(tmp, ' ');
	new = NULL;
	arg = NULL;
	l->i = 0;
	while (l->split[l->i])
	{
		l->j = 0;
		new = create_linked_list_norm(l, arg, new);
		if (l->split[l->i][l->j] == '-'
			&& (!check_arg(arg)) && (check_cmd(arg)) && (!check_optin(arg)))
			new = creation_nodes(l->split[l->i], TOKEN_OPTION);
		if (l->split[l->i][l->j] == '|')
			new = creation_nodes(l->split[l->i], TOKEN_PIPE);
		add_node_last(new, &arg);
		l->i++;
	}
	arg = check_all(arg, ev);
	free_fnc(l->split);
	free(l);
	return (arg);
}

t_node	*check_all(t_node *arg, t_env **ev)
{
	arg = check_qoute(arg, ev);
	arg = pipe_add(arg);
	arg = check_optin(arg);
	return (arg);
}
