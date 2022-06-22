/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_qoutes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydahni <ydahni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 19:49:54 by ydahni            #+#    #+#             */
/*   Updated: 2022/06/19 21:43:30 by ydahni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*skip_double_qoutes_2(t_node *line, t_env **ev, char *str_quote)
{
	char	*str;

	str = NULL;
	if (line->data[line->i] == '$' && (ft_isalpha(line->data[line->i + 1])
			|| line->data[line->i + 1] == '_'))
	{	
		str = env(line, ev);
		str_quote = ft_strjoin(str_quote, str);
		free(str);
	}
	else if ((line->data[line->i] == '$'
			&& (!ft_isalpha(line->data[line->i + 1])))
		|| line->data[line->i + 1] == '\0')
	{
		str_quote = ft_charjoin(str_quote, line->data[line->i]);
		line->i++;
	}
	else if (line->data[line->i] != '$' && line->data[line->i] != '\0')
		str_quote = ft_charjoin(str_quote, line->data[line->i++]);
	return (str_quote);
}

char	*skip_double_qoutes(t_node *line, t_env **ev, char *str_quote)
{
	char	*itoa;

	itoa = NULL;
	if (line->data[line->i] == '$')
		line->i++;
	line->i++;
	while (line->data[line->i] != 34 && line->data[line->i])
	{
		if (line->data[line->i] == '$' && line->data[line->i + 1] == '?')
		{	
			line->i = line->i + 2;
			check_exit_status();
			itoa = ft_itoa(g_global.exit_status);
			str_quote = ft_strjoin(str_quote, itoa);
			free(itoa);
			return (str_quote);
		}
		str_quote = skip_double_qoutes_2(line, ev, str_quote);
	}
	if (line->data[line->i] != '\0')
		line->i++;
	return (str_quote);
}

char	*skip_single_qoutes(t_node *line, char *str_quote)
{
	if (line->data[line->i] == '$')
		line->i++;
	line->i++;
	while (line->data[line->i] != 39 && line->data[line->i])
	{
		str_quote = ft_charjoin(str_quote, line->data[line->i]);
		line->i++;
	}
	line->i++;
	return (str_quote);
}

char	*quote(t_node *line, t_env **ev)
{
	char	*str_quote;

	str_quote = malloc(1);
	str_quote[0] = '\0';
	while (line->data[line->i])
	{
		if (line->data[line->i] == 34
			|| (line->data[line->i] == '$' && line->data[line->i + 1] == 34))
			str_quote = skip_double_qoutes(line, ev, str_quote);
		if (line->data[line->i] == 39 || (line->data[line->i] == '$'
				&& line->data[line->i + 1] == 39))
			str_quote = skip_single_qoutes(line, str_quote);
		if (line->data[line->i] != 34
			&& line->data[line->i] != 39 && line->data[line->i] != '\0')
			str_quote = define_string(line, ev, str_quote);
	}
	return (str_quote);
}

t_node	*check_qoute(t_node *tmp, t_env **ev)
{
	char	*str;
	t_node	*lexer;

	lexer = tmp;
	while (lexer)
	{
		lexer->i = 0;
		str = quote(lexer, ev);
		lexer->data = str;
		lexer = lexer->next;
	}
	return (tmp);
}
