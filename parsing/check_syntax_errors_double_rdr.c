/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_errors_double_rdr.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydahni <ydahni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:39:57 by ydahni            #+#    #+#             */
/*   Updated: 2022/06/19 21:43:30 by ydahni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*double_rdr_error_norm(t_lexer *lexer, t_norm *l)
{
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

t_lexer	*double_rdr_error(t_lexer *lexer, t_norm *l)
{
	if (lexer->str[lexer->i] == ' ' && l->p[lexer->i] == '0')
		skip_whitespace(lexer);
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
	if (lexer->str[lexer->i] == '<'
		&& lexer->str[lexer->i + 1] == '>' && l->p[lexer->i] == '0')
	{
		printf_error(lexer, 1);
		return (NULL);
	}
	lexer = double_rdr_error_norm(lexer, l);
	if (lexer == NULL)
		return (NULL);
	return (lexer);
}

int	calcul_rdr(t_lexer *lexer, int c)
{
	int	i;
	int	j;

	j = 0;
	i = lexer->i;
	while (lexer->str[i])
	{
		if (lexer->str[i] == c)
			j++;
		i++;
	}
	return (j);
}

void	printf_error_norm(int i, int c)
{
	if (c == '<')
	{
		if (i == 1)
			printf("syntax error near unexpected token `<'\n");
		else if (i == 2)
			printf("syntax error near unexpected token `<<'\n");
		else if (i >= 3)
			printf("syntax error near unexpected token `<<<'\n");
	}
}

void	printf_error(t_lexer *lexer, int c)
{
	int	i;

	g_global.flag_exit = 258;
	i = calcul_rdr(lexer, c);
	if (c == '>')
	{
		if (i == 1)
			printf("syntax error near unexpected token `>'\n");
		else if (i >= 2)
			printf("syntax error near unexpected token `>>'\n");
	}
	printf_error_norm(i, c);
	if (c == 0)
		printf("syntax error near unexpected token `newline'\n");
	else if (c == 1)
		printf("syntax error near unexpected token `<>'\n");
	else if (c == 2)
		printf("syntax error near unexpected token `|'\n");
}
