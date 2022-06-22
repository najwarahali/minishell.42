/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_env_utl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrahali <nrahali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 17:59:53 by ydahni            #+#    #+#             */
/*   Updated: 2022/06/20 03:14:56 by nrahali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**table2d(char **env)
{
	char	**new;
	int		i;

	i = 0;
	while (env[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		new[i] = ft_strdup(env[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

char	*env_type(char *env)
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
		str_quote = ft_charjoin(str_quote, '=');
	}
	return (str_quote);
}

char	*env_arg(char *env)
{
	char	*str_arg;
	int		i;

	str_arg = malloc(1);
	str_arg[0] = '\0';
	i = 0;
	if (ft_strchr_arg(env, '=') == 0)
	{
		while (env[i])
		{
			str_arg = ft_charjoin(str_arg, env[i]);
			i++;
		}
	}
	return (str_arg);
}

t_env	*get_double_env(t_env *ev)
{
	int		i;
	t_env	*tmp;

	tmp = ev;
	i = 0;
	while (tmp)
	{
		if (tmp->data != NULL)
			i++;
		tmp = tmp->next;
	}
	ev->env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	tmp = ev;
	while (tmp)
	{
		ev->env[i] = tmp->data;
		i++;
		tmp = tmp->next;
	}
	ev->env[i] = NULL;
	return (ev);
}

int	ft_strchr_arg(char *n, int c)
{
	int		i;

	i = 0;
	while (n[i])
	{
		if (n[i] == c)
			return (1);
		i++;
	}
	return (0);
}
