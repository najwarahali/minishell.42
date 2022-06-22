/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_errors_rdr.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydahni <ydahni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:00:50 by ydahni            #+#    #+#             */
/*   Updated: 2022/06/19 21:18:00 by ydahni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*rdr_norm(t_lexer *lexer, t_norm *l, t_env **ev)
{
	if (lexer->str[lexer->i] == '>' && l->p[lexer->i] == '0')
	{
		lexer->i++;
		lexer = rdr_norm1(lexer, l, ev);
		if (lexer == NULL)
			return (NULL);
	}
	if (lexer->str[lexer->i] == '<' && l->p[lexer->i] == '0')
	{
		lexer->i++;
		if (lexer->str[lexer->i] == '<')
		{
			lexer->i++;
			if (double_rdr_error(lexer, l) == NULL)
				return (NULL);
		}
		else
		{
			if (error_redirect(lexer, l, ev) == NULL)
				return (NULL);
			if (singl_rdr_error(lexer, l) == NULL)
				return (NULL);
		}
	}
	return (lexer);
}

t_lexer	*rdr_norm1(t_lexer *lexer, t_norm *l, t_env **ev)
{
	if (lexer->str[lexer->i] == '>')
	{
		lexer->i++;
		if (error_redirect(lexer, l, ev) == NULL)
			return (NULL);
		if (double_rdr_error(lexer, l) == NULL)
			return (NULL);
	}
	else
	{
		if (error_redirect(lexer, l, ev) == NULL)
			return (NULL);
		if (singl_rdr_error(lexer, l) == NULL)
			return (NULL);
	}
	return (lexer);
}

t_lexer	*rdr(t_lexer *tmp, t_env **ev)
{
	t_norm	*l;
	t_lexer	*lexer;

	lexer = tmp;
	l = add_number(lexer->str);
	lexer->i = 0;
	while (lexer->str[lexer->i])
	{
		if (lexer->str[lexer->i] == ' ' && l->p[lexer->i] == '0')
			skip_whitespace(lexer);
		lexer = rdr_norm(lexer, l, ev);
		if (lexer == NULL)
		{
			free_spc(l);
			return (NULL);
		}
		if (lexer->str[lexer->i] != '\0')
			lexer->i++;
	}
	free_spc(l);
	return (lexer);
}
