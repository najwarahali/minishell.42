/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydahni <ydahni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 23:17:16 by ydahni            #+#    #+#             */
/*   Updated: 2022/06/19 21:18:37 by ydahni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int					i;
	unsigned char		*s3;
	unsigned char		*s4;

	if (!s1 || !s2)
		return (0);
	s3 = (unsigned char *)s1;
	s4 = (unsigned char *)s2;
	i = 0;
	while (s3[i] != '\0' && (s3[i] == s4[i]))
		i++;
	return (s3[i] - s4[i]);
}

char	*ft_charjoin(char *s1, char c)
{
	int		i;
	int		lens1;
	char	*str;

	lens1 = ft_strlen(s1);
	str = malloc (lens1 + 2);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = '\0';
	free(s1);
	return (str);
}

void	skip_whitespace(t_lexer *lexer)
{
	while (lexer->str[lexer->i] == ' ')
	{
		lexer->i++;
	}
}
