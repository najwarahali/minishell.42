/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_dollar_sign.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydahni <ydahni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:24:45 by ydahni            #+#    #+#             */
/*   Updated: 2022/06/19 21:18:24 by ydahni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*string_after_dollar_sign(char *str_quote, t_node *line)
{
	if (line->data[line->i] == '$')
	{
		line->i++;
		while ((line->data[line->i] != '$' && ft_isalnum(line->data[line->i])
				&& line->data[line->i] != '\0' ) || line->data[line->i] == '_')
		{
			str_quote = ft_charjoin(str_quote, line->data[line->i]);
			line->i++;
		}
	}
	return (str_quote);
}

char	*env(t_node *line, t_env **ev)
{
	char	*str_quote;
	char	*str;

	str = malloc(2);
	str[0] = '\0';
	str_quote = malloc(2);
	str_quote[0] = '\0';
	if (line->data[line->i] == '$')
	{
		str_quote = string_after_dollar_sign(str_quote, line);
		str = get_env(str, str_quote, ev);
	}
	return (str);
}

char	*get_env(char *env, char *str, t_env **ev)
{
	t_env	*tmp;

	tmp = *ev;
	str = ft_charjoin(str, '=');
	change_pwd_env(ev);
	if (str != NULL)
	{
		while (tmp)
		{
			if (ft_strcmp(tmp->type, str) == 0)
				env = ft_strjoin(env, tmp->value);
			tmp = tmp->next;
		}
	}
	free(str);
	return (env);
}
