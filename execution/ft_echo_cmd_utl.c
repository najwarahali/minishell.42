/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_cmd_utl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrahali <nrahali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:55:53 by nrahali           #+#    #+#             */
/*   Updated: 2022/06/20 02:07:55 by nrahali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_echo(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if ((cmd[i] == 'e' || cmd[i] == 'E') && (cmd[i + 1] == 'c'
				|| cmd[i + 1] == 'C') && (cmd[i + 2] == 'h'
				|| cmd[i + 2] == 'H')
			&& (cmd[i + 3] == 'o' || cmd[i + 3] == 'O') && !cmd[i + 4])
			return (0);
		else
			return (1);
	}
	return (1);
}

int	check_opt(char *opt)
{
	int	i;

	i = 0;
	if (opt == NULL)
		return (0);
	if (opt[i] == '-')
		i++;
	while (opt[i])
	{
		if (opt[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	ft_echo_0_norm(t_token *tmp)
{
	if (tmp->opt[0] == '-' && tmp->opt[1] == '\0')
	{
		printf("%s ", tmp->opt);
		if (tmp->arg == NULL)
			printf("\n");
	}
}
