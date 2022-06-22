/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydahni <ydahni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 16:56:49 by ydahni            #+#    #+#             */
/*   Updated: 2021/11/21 01:50:18 by ydahni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		len = 0;
	while (i < len && s[i + start])
		i++;
	new = malloc(i + 1);
	if (!new)
		return (NULL);
	while (j < i)
	{
		new[j++] = s[start++];
	}
	new[i] = '\0';
	return (new);
}
