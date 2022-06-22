/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrahali <nrahali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 04:45:23 by ydahni            #+#    #+#             */
/*   Updated: 2022/06/12 23:21:34 by nrahali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_errors_e_u_norm(char *arg, char *type)
{
	int	i;

	i = 0;
	type = env_type(arg);
	if (ft_isdigit(type[0]) == 1)
	{
		free(type);
		return (1);
	}
	while (type[i])
	{
		if (ft_isalnum_2(type[i]) == 0)
		{
			free(type);
			return (1);
		}
		i++;
	}
	if (type != NULL)
		free(type);
	return (0);
}

int	check_errors_e_u_norm_complete(char *arg)
{
	int	i;

	i = 0;
	if (check_for_equal(arg) == 0)
	{
		if (ft_isdigit(arg[0]) == 1)
			return (1);
		while (arg[i])
		{
			if (ft_isalnum_2(arg[i]) == 0)
				return (1);
			i++;
		}
	}
	return (0);
}

int	check_errors_e_u(char *arg)
{
	int		c;
	char	*type;

	type = NULL;
	if (arg[0] == '\0')
		return (1);
	if (check_for_equal(arg) == 1)
	{
		c = check_errors_e_u_norm(arg, type);
		if (c == 1)
		{
			if (type != NULL)
				free(type);
			return (1);
		}
	}
	c = check_errors_e_u_norm_complete(arg);
	if (c == 1)
		return (1);
	if (type != NULL)
		free(type);
	return (0);
}

char	*env_type_2(char *env)
{
	char	*str_quote;
	int		i;

	i = 0;
	str_quote = malloc(2);
	str_quote[0] = '\0';
	if (ft_strchr_arg(env, '=') == 1)
	{
		while (env[i] != '=')
		{
			str_quote = ft_charjoin(str_quote, env[i]);
			i++;
		}
	}
	return (str_quote);
}

void	del_midd_node(t_env **head, char *arg)
{
	t_env	*temp1;
	t_env	*temp2;

	temp1 = *head;
	while (temp1)
	{
		if (ft_strcmp(temp1->arg, arg) == 0)
		{
			temp2->next = temp1->next;
			free(temp1->arg);
			free(temp1->value);
			free(temp1->type);
			free(temp1->data);
			free(temp1);
			break ;
		}
		temp2 = temp1;
		temp1 = temp1->next;
	}
}
