/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_cmd_after_pipe.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrahali <nrahali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 16:16:34 by ydahni            #+#    #+#             */
/*   Updated: 2022/06/20 21:11:19 by nrahali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*pipe_add_norm(t_node *arg)
{
	while (arg)
	{
		if (arg->e_type != TOKEN_APPEND && arg->e_type != TOKEN_HEREDOC
			&& arg->e_type != TOKEN_INPUT
			&& arg->e_type != TOKEN_OUTPUT)
			break ;
		arg = arg->next;
	}
	return (arg);
}

t_node	*pipe_add(t_node *tmp)
{
	t_node	*arg;

	arg = tmp;
	while (arg)
	{
		if (arg->e_type == TOKEN_PIPE && (arg->next->e_type == TOKEN_APPEND
				|| arg->next->e_type == TOKEN_HEREDOC
				|| arg->next->e_type == TOKEN_INPUT
				|| arg->next->e_type == TOKEN_OUTPUT)
			&& (arg->next->next != NULL))
		{
			arg = arg->next;
			arg = pipe_add_norm(arg);
			if (arg != NULL && arg->e_type != TOKEN_PIPE)
				arg->e_type = TOKEN_CMD;
			if (arg == NULL)
				return (tmp);
		}
		if (arg->e_type == TOKEN_PIPE && (arg->next->e_type == TOKEN_ARG
				|| arg->next->e_type == TOKEN_OPTION))
			arg->next->e_type = TOKEN_CMD;
		if (arg != NULL)
			arg = arg->next;
	}
	return (tmp);
}

t_node	*check_optin(t_node *tmp)
{
	t_node	*arg;

	arg = tmp;
	while (arg)
	{
		if (arg->e_type == TOKEN_CMD && arg->next != NULL
			&& arg->next->data[0] == '-')
			arg->next->e_type = TOKEN_OPTION;
		arg = arg->next;
	}
	return (tmp);
}

int	check_cmd(t_node *new)
{
	t_node	*tmp;

	tmp = new;
	if (tmp != NULL)
	{
		while (tmp)
		{
			if (tmp->e_type == TOKEN_CMD)
				return (1);
			tmp = tmp->next;
		}
	}
	return (0);
}

int	check_arg(t_node *new)
{
	t_node	*tmp;

	tmp = new;
	if (tmp != NULL)
	{
		while (tmp)
		{
			if (tmp->e_type == TOKEN_ARG)
				return (1);
			tmp = tmp->next;
		}
	}
	return (0);
}
