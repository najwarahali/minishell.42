/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydahni <ydahni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 15:17:20 by ydahni            #+#    #+#             */
/*   Updated: 2022/06/19 21:43:30 by ydahni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quote_error(t_lexer *lexer, int c)
{
	while (lexer->str[lexer->i])
	{
		if (lexer->str[lexer->i] == c)
		{
			lexer->i++;
			return (1);
		}
		lexer->i++;
	}
	return (0);
}

t_lexer	*double_qoutes_errors(t_lexer *lexer)
{
	if (lexer->str[lexer->i] == 34)
	{
		lexer->i++;
		if (quote_error(lexer, 34) == 0)
		{
			g_global.flag_exit = 1;
			printf ("ERROR DOUBLE QUOTE\n");
			return (NULL);
		}
	}
	return (lexer);
}

t_lexer	*single_qoutes_errors(t_lexer *lexer)
{
	if (lexer->str[lexer->i] == 39)
	{
		lexer->i++;
		if (quote_error(lexer, 39) == 0)
		{
			g_global.flag_exit = 1;
			printf ("ERROR SINGLE QUOTE\n");
			return (NULL);
		}
	}
	return (lexer);
}

int	check_error_quote(t_lexer *tmp)
{
	t_lexer	*lexer;

	lexer = tmp;
	lexer->i = 0;
	while (lexer->str[lexer->i])
	{
		lexer = double_qoutes_errors(lexer);
		if (lexer == NULL)
			return (0);
		lexer = single_qoutes_errors(lexer);
		if (lexer == NULL)
			return (0);
		if (lexer->str[lexer->i] != 34 && lexer->str[lexer->i] != 39
			&& lexer->str[lexer->i] != '\0')
			lexer->i++;
	}
	return (1);
}
