/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_errors_pipe_complete.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrahali <nrahali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 03:27:06 by ydahni            #+#    #+#             */
/*   Updated: 2022/06/20 02:53:41 by nrahali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*error_pipe_norm_3(t_lexer *lexer, t_norm *l)
{
	if (lexer->str[lexer->i] == '|' && l->p[lexer->i] == '0')
	{
		lexer->i++;
		if (lexer->str[lexer->i] == ' ' && l->p[lexer->i] == '0')
			skip_whitespace(lexer);
		if (lexer->str[lexer->i] == '\0'
			|| (lexer->str[lexer->i] == '|' && l->p[lexer->i] == '0'))
		{
			g_global.flag_exit = 258;
			printf("syntax error near unexpected token `|' \n");
			return (NULL);
		}
	}
	if (lexer->str[lexer->i] == '|'
		&& lexer->str[lexer->i + 1] == '|' && l->p[lexer->i] == '0')
	{
		g_global.flag_exit = 258;
		printf("syntax error near unexpected token `||' \n");
		return (NULL);
	}
	return (lexer);
}

t_lexer	*error_pipe_norm_2(t_lexer *lexer, t_norm *l)
{
	if (lexer->str[lexer->i] == ' ' && l->p[lexer->i] == '0')
	{
		skip_whitespace(lexer);
		if (lexer->str[lexer->i] == '|'
			&& lexer->str[lexer->i + 1] == '|' && l->p[lexer->i] == '0')
		{
			g_global.flag_exit = 258;
			printf("syntax error near unexpected token `||' \n");
			return (NULL);
		}
	}
	if (lexer->str[lexer->i] == '|' && lexer->str[lexer->i + 1] == '\0')
	{
		g_global.flag_exit = 258;
		printf("syntax error near unexpected token `|' \n");
		return (NULL);
	}
	return (lexer);
}

t_lexer	*error_pipe_norm_1(t_lexer *lexer, t_norm *l)
{
	if (lexer->str[lexer->i] == ' ' && l->p[lexer->i] == '0')
	{
		skip_whitespace(lexer);
		if (lexer->str[lexer->i] == '|'
			&& lexer->str[lexer->i + 1] == '|' && l->p[lexer->i] == '0')
		{
			g_global.flag_exit = 258;
			printf("syntax error near unexpected token `||' \n");
			return (NULL);
		}
		if ((lexer->str[lexer->i] == '|'
				&& lexer->str[lexer->i + 1] == '\0')
			|| lexer->str[lexer->i] == '|')
		{
			g_global.flag_exit = 258;
			printf("syntax error near unexpected token `|' \n");
			return (NULL);
		}
	}
	return (lexer);
}
