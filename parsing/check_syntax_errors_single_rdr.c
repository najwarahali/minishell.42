/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_errors_single_rdr.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydahni <ydahni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 03:16:27 by ydahni            #+#    #+#             */
/*   Updated: 2022/06/19 21:18:03 by ydahni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*singl_rdr_error(t_lexer *lexer, t_norm *l)
{
	if (lexer->str[lexer->i] == '>' && l->p[lexer->i] == '0')
	{
		lexer->i++;
		if (lexer->str[lexer->i] == ' ')
			skip_whitespace(lexer);
		if (lexer->str[lexer->i] != '>' && lexer->str[lexer->i] != '<'
			&& lexer->str[lexer->i] != '\0' && l->p[lexer->i] == '0')
		{
			printf_error(lexer, 1);
			return (NULL);
		}
	}
	if (lexer->str[lexer->i] == ' ' && l->p[lexer->i] == '0')
		skip_whitespace(lexer);
	lexer = singl_rdr_error_norm(lexer, l);
	if (lexer == NULL)
		return (NULL);
	lexer = singl_rdr_error_norm1(lexer, l);
	if (lexer == NULL)
		return (NULL);
	return (lexer);
}

t_lexer	*singl_rdr_error_norm(t_lexer *lexer, t_norm *l)
{
	if (lexer->str[lexer->i] == '\0')
	{
		printf_error(lexer, 0);
		return (NULL);
	}
	if (lexer->str[lexer->i] == '|' && l->p[lexer->i] == '0')
	{
		printf_error(lexer, 2);
		return (NULL);
	}
	return (lexer);
}

t_lexer	*singl_rdr_error_norm1(t_lexer *lexer, t_norm *l)
{
	if (lexer->str[lexer->i] == '<'
		&& lexer->str[lexer->i + 1] == '>' && l->p[lexer->i] == '0')
	{
		printf_error(lexer, 1);
		return (NULL);
	}
	if (lexer->str[lexer->i] == '>' && l->p[lexer->i] == '0')
	{
		printf_error(lexer, '>');
		return (NULL);
	}
	if (lexer->str[lexer->i] == '<' && l->p[lexer->i] == '0')
	{
		printf_error(lexer, '<');
		return (NULL);
	}
	if (lexer->str[lexer->i] == '|' && l->p[lexer->i] == '0')
	{
		error_pipe(lexer);
		return (NULL);
	}
	return (lexer);
}
