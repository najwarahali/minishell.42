/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydahni <ydahni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 23:21:40 by ydahni            #+#    #+#             */
/*   Updated: 2022/06/19 21:18:28 by ydahni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*double_qoutes_her_doc(t_lexer *lexer, char *str)
{
	if (lexer->str[lexer->i] == '$')
		lexer->i++;
	lexer->i++;
	while (lexer->str[lexer->i] != 34 && lexer->str[lexer->i])
	{
		str = ft_charjoin(str, lexer->str[lexer->i++]);
	}
	if (lexer->str[lexer->i] != '\0')
		lexer->i++;
	return (str);
}

char	*single_qoutes_her_doc(t_lexer *lexer, char *str)
{
	if (lexer->str[lexer->i] == '$')
		lexer->i++;
	lexer->i++;
	while (lexer->str[lexer->i] != 39 && lexer->str[lexer->i])
	{
		str = ft_charjoin(str, lexer->str[lexer->i++]);
	}
	if (lexer->str[lexer->i] != '\0')
		lexer->i++;
	return (str);
}

char	*get_str_old(t_lexer *lexer, char *str)
{
	if (lexer->str[lexer->i] == ' ')
		skip_whitespace(lexer);
	while (lexer->str[lexer->i])
	{
		if (lexer->str[lexer->i] == 34
			|| (lexer->str[lexer->i] == '$' && lexer->str[lexer->i + 1] == 34))
			str = double_qoutes_her_doc(lexer, str);
		if (lexer->str[lexer->i] == 39 || (lexer->str[lexer->i] == '$'
				&& lexer->str[lexer->i + 1] == 39))
			str = single_qoutes_her_doc(lexer, str);
		if (lexer->str[lexer->i] != 34 && lexer->str[lexer->i] != 39
			&& lexer->str[lexer->i] != '\0' && lexer->str[lexer->i] != ' ')
			str = ft_charjoin(str, lexer->str[lexer->i++]);
		if (lexer->str[lexer->i] == ' ')
			return (str);
	}
	return (str);
}

char	*here_doc_string_norm(t_lexer *lexer, char *str)
{
	while (lexer->str[lexer->i])
	{
		if (lexer->str[lexer->i] == '<' && lexer->str[lexer->i + 1] == '<')
		{
			lexer->i = lexer->i + 2;
			str = get_str_old(lexer, str);
			break ;
		}
		lexer->i++;
	}
	return (str);
}

t_node	*here_doc_string(t_lexer *tmp, t_node *tmp2)
{
	t_lexer	*lexer;
	t_node	*head;
	char	*str;

	str = malloc(1);
	str[0] = '\0';
	lexer = tmp;
	head = tmp2;
	lexer->i = 0;
	while (head)
	{
		if (head->e_type == TOKEN_HEREDOC)
		{
			str = here_doc_string_norm(lexer, str);
			free(head->data);
			head->data = ft_strdup(str);
			str[0] = '\0';
		}
		head = head->next;
	}
	free(str);
	return (tmp2);
}
