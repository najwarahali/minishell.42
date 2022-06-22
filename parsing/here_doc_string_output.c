/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_string_output.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydahni <ydahni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 23:32:24 by ydahni            #+#    #+#             */
/*   Updated: 2022/06/22 00:16:06 by ydahni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*string_here_doc_new(t_node *line, t_env **ev)
{
	char	*str_quote;

	str_quote = malloc(1);
	str_quote[0] = '\0';
	while (line->data[line->i])
	{
		if (line->data[line->i] != '\0')
			str_quote = define_string(line, ev, str_quote);
	}
	return (str_quote);
}

char	*new_string_of_here_doc_output(char	*tmp, t_env **ev)
{
	char	*str;
	t_node	*lexer;

	if (tmp == NULL)
		return (NULL);
	lexer = malloc(sizeof(t_node));
	lexer->i = 0;
	lexer->data = ft_strdup(tmp);
	str = string_here_doc_new(lexer, ev);
	free(lexer->data);
	free(lexer);
	return (str);
}
