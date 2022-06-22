/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_qoutes_complete.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydahni <ydahni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 02:23:58 by ydahni            #+#    #+#             */
/*   Updated: 2022/06/21 23:30:36 by ydahni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*add_exit_code(t_node *line, char *str_quote)
{
	char	*itoa;

	itoa = NULL;
	line->i = line->i + 2;
	check_exit_status();
	itoa = ft_itoa(g_global.exit_status);
	str_quote = ft_strjoin(str_quote, itoa);
	free(itoa);
	return (str_quote);
}

char	*add_env_sting(t_node *line, t_env **ev, char *str_quote)
{
	char	*str;

	str = NULL;
	str = env(line, ev);
	str_quote = ft_strjoin(str_quote, str);
	free(str);
	return (str_quote);
}

char	*define_string(t_node *line, t_env **ev, char *str_quote)
{
	if (line->data[line->i] == '$' && line->data[line->i + 1] != '\0'
		&& (ft_isalpha(line->data[line->i + 1])
			|| line->data[line->i + 1] == '_'))
	{
		str_quote = add_env_sting(line, ev, str_quote);
		return (str_quote);
	}
	else if (line->data[line->i] != '$'
		&& line->data[line->i] != '\0')
		str_quote = ft_charjoin(str_quote, line->data[line->i++]);
	else if ((line->data[line->i] == '$'
			&& (!ft_isalpha(line->data[line->i + 1])))
		|| line->data[line->i + 1] == '\0')
	{
		if (line->data[line->i] == '$' && line->data[line->i + 1] == '?')
		{
			str_quote = add_exit_code(line, str_quote);
			return (str_quote);
		}	
		str_quote = ft_charjoin(str_quote, line->data[line->i++]);
	}
	return (str_quote);
}
