/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_errors_pipe.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydahni <ydahni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 22:53:05 by ydahni            #+#    #+#             */
/*   Updated: 2022/06/19 21:43:30 by ydahni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*error_pipe_norm(t_lexer *lexer, t_norm *l)
{
	if (lexer->str[lexer->i] == '|' && lexer->str[lexer->i + 1] == '|'
		&& l->p[lexer->i] == '0')
	{
		g_global.flag_exit = 258;
		printf("syntax error near unexpected token `||' \n");
		return (NULL);
	}
	else if (lexer->str[lexer->i] == '|' && l->p[lexer->i] == '0')
	{
		g_global.flag_exit = 258;
		printf("syntax error near unexpected token `|' \n");
		return (NULL);
	}
	return (lexer);
}

t_lexer	*error_pipe_complete(t_lexer *lexer, t_norm *l)
{
	lexer = error_pipe_norm_1(lexer, l);
	if (lexer == NULL)
	{
		free_spc(l);
		return (NULL);
	}
	while (lexer->str[lexer->i])
	{
		lexer = error_pipe_norm_2(lexer, l);
		if (lexer == NULL)
		{
			free_spc(l);
			return (NULL);
		}
		lexer = error_pipe_norm_3(lexer, l);
		if (lexer == NULL)
		{
			free_spc(l);
			return (NULL);
		}
		if (lexer->str[lexer->i] != '\0')
			lexer->i++;
	}
	return (lexer);
}

t_lexer	*error_pipe(t_lexer *tmp)
{
	t_norm	*l;
	t_lexer	*lexer;

	lexer = tmp;
	l = add_number(lexer->str);
	lexer->i = 0;
	lexer = error_pipe_norm(lexer, l);
	if (lexer == NULL)
	{	
		free_spc(l);
		return (NULL);
	}
	lexer = error_pipe_complete(lexer, l);
	if (lexer == NULL)
	{
		free_spc(l);
		return (NULL);
	}
	free_spc(l);
	return (lexer);
}
