/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation_nodes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydahni <ydahni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 15:22:22 by ydahni            #+#    #+#             */
/*   Updated: 2022/06/19 21:18:06 by ydahni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*creation_nodes(char *value, int type)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	new_node->data = value;
	new_node->e_type = type;
	new_node->next = NULL;
	return (new_node);
}

t_env	*creation_nodes_env(char *values)
{
	t_env	*new_node;
	char	*type;
	char	*value;
	char	*arg;

	type = env_type(values);
	value = env_value(values);
	arg = env_arg(values);
	new_node = malloc(sizeof(t_env));
	new_node->data = values;
	new_node->type = type;
	new_node->value = value;
	new_node->arg = arg;
	new_node->env = NULL;
	new_node->next = NULL;
	return (new_node);
}

t_env	*creation_nodes_export(char *values)
{
	t_env	*new_node;
	char	*type;
	char	*value;
	char	*arg;

	type = env_type(values);
	value = env_value(values);
	arg = env_arg(values);
	new_node = malloc(sizeof(t_env));
	new_node->data = ft_strdup(values);
	new_node->type = type;
	new_node->value = value;
	new_node->arg = arg;
	new_node->env = NULL;
	new_node->next = NULL;
	return (new_node);
}

t_token	*init_token_f(t_token *new)
{
	new = malloc(sizeof(t_token));
	new->arg = NULL;
	new->cmd = NULL;
	new->opt = NULL;
	new->rdr = NULL;
	return (new);
}

t_lexer	*init_lexer(char *src)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	lexer->str = src;
	lexer->i = 0;
	return (lexer);
}
