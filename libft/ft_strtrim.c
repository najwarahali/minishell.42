/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydahni <ydahni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 03:09:42 by ydahni            #+#    #+#             */
/*   Updated: 2021/11/21 21:31:34 by ydahni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	chercheset(char c, char const *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*s;

	if (!s1 || !set)
		return (NULL);
	s = (char *)s1;
	i = 0;
	j = ft_strlen(s1) - 1;
	while (s[i] && chercheset(s[i], set))
		i++;
	while (j > 0 && chercheset(s[j], set))
		j--;
	return (ft_substr(s, i, j - i + 1));
}
