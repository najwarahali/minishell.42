/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrahali <nrahali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 23:12:32 by ydahni            #+#    #+#             */
/*   Updated: 2022/06/20 22:21:52 by nrahali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*env_new2(char **env)
{
	t_env	*ev;
	t_env	*arg;
	int		i;

	i = 0;
	arg = NULL;
	while (env[i])
	{
		ev = creation_nodes_env(env[i]);
		add_node_last_env(ev, &arg);
		i++;
	}
	return (arg);
}

char	*env_value_norm(char *env, char *str)
{
	int		i;
	size_t	j;

	i = 0;
	j = 0;
	while (j < ft_strlen(env))
	{
		if (env[i] == '=')
		{
			i++;
			while (env[i])
			{
				str = ft_charjoin(str, env[i]);
				i++;
				j++;
			}
		}
		i++;
		j++;
	}
	return (str);
}

char	*env_value(char *env)
{
	char	*str;

	str = malloc(2);
	str[0] = '\0';
	if (ft_strchr_arg(env, '=') == 1)
		str = env_value_norm(env, str);
	return (str);
}

t_env	*get_env_list(t_env *arg)
{
	t_env	*tmp;
	char	*str_type;
	char	*str_value;
	char	*str_arg;

	tmp = arg;
	while (tmp)
	{
		str_arg = env_arg(tmp->data);
		str_type = env_type(tmp->data);
		str_value = env_value(tmp->data);
		tmp->arg = str_arg;
		tmp->type = str_type;
		tmp->value = str_value;
		tmp = tmp->next;
	}
	return (arg);
}

t_env	*get_env2(char **e)
{
	t_env	*env;
	char	**envmine;

	envmine = table2d(e);
	env = env_new2(envmine);
	env = get_double_env(env);
	free(envmine);
	return (env);
}
