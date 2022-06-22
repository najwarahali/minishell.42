/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_redirect_erros.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydahni <ydahni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 02:40:43 by ydahni            #+#    #+#             */
/*   Updated: 2022/06/19 21:47:31 by ydahni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_new_1(char *str)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(1);
	new[0] = '\0';
	while (str[i])
	{
		if (str[i] == '$')
			i++;
		new = ft_charjoin(new, str[i]);
		i++;
	}
	new = ft_charjoin(new, '=');
	return (new);
}

char	*get_env_new(char *str, t_env **ev)
{
	t_env	*tmp;
	char	*env;
	char	*new;

	env = malloc(1);
	env[0] = '\0';
	new = get_env_new_1(str);
	tmp = *ev;
	if (str != NULL)
	{
		while (tmp)
		{
			if (ft_strncmp(tmp->type, new, ft_strlen(new)) == 0)
				env = ft_strjoin(env, tmp->value);
			tmp = tmp->next;
		}
	}
	free(new);
	return (env);
}

char	*error_redirect_norm(t_lexer *lexer, t_norm *l)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(1);
	str[0] = '\0';
	if (lexer->str[lexer->i] == ' ')
		skip_whitespace(lexer);
	if (lexer->str[lexer->i] == '$' && l->p[lexer->i] == '0')
	{
		i = lexer->i;
		while (lexer->str[i])
		{
			if (lexer->str[i] == ' ')
				break ;
			str = ft_charjoin(str, lexer->str[i++]);
		}
	}
	return (str);
}

t_lexer	*print_error_redirect(char *str, char *env)
{
	g_global.flag_exit = 1;
	printf("minishell: %s: ambiguous redirect\n", str);
	free(str);
	free(env);
	return (NULL);
}

t_lexer	*error_redirect(t_lexer *lexer, t_norm *l, t_env **ev)
{
	char	*str;
	char	*env;
	int		i;

	i = 0;
	str = NULL;
	str = error_redirect_norm(lexer, l);
	if (str[0] == '\0')
	{
		free(str);
		return (lexer);
	}
	env = get_env_new(str, ev);
	if (env[0] == '\0')
		return (print_error_redirect(str, env));
	else
	{
		free(env);
		free(str);
		return (lexer);
	}
	free(env);
	free(str);
	return (lexer);
}
